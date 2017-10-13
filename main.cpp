#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cursesapp.h>
#include <cursesm.h>
#include <cursesf.h>
#include <menu.h>

#include "WorldMap.h"

using namespace std;

class Village : public Place {
public:
    Village(int xCoord,int yCoord):Place(xCoord,yCoord) {}
    // Todo width, height

};



class VillageFactory {
public:
    VillageFactory(WorldMap* worldMap, int seed) {
        theMap = worldMap;
        int curSeed = seed >= 0 ? seed : time(NULL); // Use seed if provided, else random
        srand(curSeed);
    }
private:
    WorldMap* theMap;
    public:
    Village * build();
};

Village* VillageFactory::build() {

    return new Village(rand() % (theMap->getWidth()-1), rand() % (theMap->getHeight()-1));
}

class ScanAction : public NCursesMenuItem
{
public:
  ScanAction(const char* s) : NCursesMenuItem(s) {
  }

  bool action() {
    NCursesPanel *mystd = new NCursesPanel();

    NCursesPanel *w = new NCursesPanel(mystd->lines() - 2, mystd->cols() - 2, 1, 1);
    w->box();
    w->bkgd(' '|COLOR_PAIR(1));
    w->refresh();

    NCursesPanel *s = new NCursesPanel(w->lines() - 6, w->cols() - 6, 3, 3);
        s->setpalette(COLOR_GREEN, COLOR_YELLOW);
    s->scrollok(TRUE);
    ::echo(); // Probably temprarily enable printing input chars

    s->printw("Enter decimal integers.  The running total will be shown\n");
    int nvalue = -1;
    int result = 0;
    while (nvalue != 0) {
      nvalue = 0;
      s->scanw("%d", &nvalue);
      if (nvalue != 0) {
        s->printw("%d: ", result += nvalue);
      }
      s->refresh();
              s->setpalette(COLOR_GREEN, COLOR_YELLOW);
    }
    s->printw("\nPress any key to continue...");
    s->getch(); // get input

    delete s;
    delete w;
    delete mystd;
    ::noecho(); // re-enable no echoing
    return FALSE; // dunno why false
  }
};

class UserData
{
private:
  int u;
public:
  UserData(int x) : u(x) {}
  int sleeptime() const { return u; }
};

class PadAction : public NCursesMenuItem
{
public:
  PadAction(const char* s) : NCursesMenuItem(s) {
  }

  bool action() {
    const int GRIDSIZE = 3;
    const int PADSIZE  = 200;
    unsigned gridcount = 0;

    NCursesPanel mystd;
    NCursesPanel P(mystd.lines()-2, mystd.cols()-2, 1, 1);
    NCursesFramedPad FP(P, PADSIZE, PADSIZE);

    for (int i=0; i < PADSIZE; i++) {
      for (int j=0; j < PADSIZE; j++) {
        if (i % GRIDSIZE == 0 && j % GRIDSIZE == 0) {
          if (i==0 || j==0)
            FP.addch('+');
          else
            FP.addch(static_cast<chtype>('A' + (gridcount++ % 26)));
        }
        else if (i % GRIDSIZE == 0)
          FP.addch('-');
        else if (j % GRIDSIZE == 0)
          FP.addch('|');
        else
          FP.addch(' ');
      }
    }

    P.label("Pad Demo", NULL);
    FP();
    P.clear();
    return FALSE;
  }
};

class PassiveItem : public NCursesMenuItem
{
public:
  PassiveItem(const char* text) : NCursesMenuItem(text) {
    options_off(O_SELECTABLE);
  }
};


class MyMenu : public NCursesMenu
{
private:
  NCursesPanel* P;
  NCursesMenuItem** I;
  UserData *u;
  #define n_items 6

public:
  MyMenu ()
    : NCursesMenu (lines() - 1, 16, 0, 0),
      P(0), I(0),
      u(0)
      // TODO Expose constructor!
  {
    u = new UserData(1);
    I = new NCursesMenuItem*[1+n_items];
    I[0] = new PassiveItem("One");
    I[1] = new PassiveItem("Two");
    I[2] = new NCursesMenuItem("Three");
    I[3] = new NCursesMenuItem("Form"); // FormAction
    I[4] = new PadAction("Pad");
    I[5] = new ScanAction("Scan");
//    I[6] = new QuitItem();
    I[n_items] = new NCursesMenuItem(); // Terminating empty item

    InitMenu(I, TRUE, TRUE);

    P = new NCursesPanel(1, n_items, LINES-1, 1);
    boldframe("Menu", "Menu");
    P->show();
  }

  MyMenu& operator=(const MyMenu& rhs)
  {
    if (this != &rhs) {
      *this = rhs;
    }
    return *this;
  }

  MyMenu(const MyMenu& rhs)
    : NCursesMenu(rhs), P(0), I(0), u(0)
  {
  }

  ~MyMenu()
  {
    P->hide();
    delete P;
    delete u;
  }

  virtual void On_Menu_Init()
  {
    NCursesWindow W(::stdscr);
    P->move(0, 0);
    P->clrtoeol();
    for(int i=1; i<=count(); i++)
      P->addch('0' + i);
    P->bkgd(W.getbkgd());
    refresh();
  }

  virtual void On_Menu_Termination()
  {
    P->move(0, 0);
    P->clrtoeol();
    refresh();
  }

  virtual void On_Item_Init(NCursesMenuItem& item)
  {
    P->move(0, item.index());
    P->attron(A_REVERSE);
    P->printw("%1d", 1+item.index());
    P->attroff(A_REVERSE);
    refresh();
  }

  virtual void On_Item_Termination(NCursesMenuItem& item)
  {
    P->move(0, item.index());
    P->attroff(A_REVERSE);
    P->printw("%1d", 1+item.index());
    refresh();
  }
};

class TestApplication : public NCursesApplication
{
protected:
  int titlesize() const { return 1; }
  void title();
  Soft_Label_Key_Set::Label_Layout useSLKs() const {
    return Soft_Label_Key_Set::PC_Style_With_Index;
  }
//  void init_labels(Soft_Label_Key_Set& S) const;

public:
  TestApplication() : NCursesApplication(TRUE) {
  }

  int run();
};

//void TestApplication::init_labels(Soft_Label_Key_Set& S) const
//{
//  for(int i=1; i <= S.labels(); i++) {
//    char buf[8];
//    assert(i < 100);
//    ::_nc_SPRINTF(buf, _nc_SLIMIT(sizeof(buf)) "Key%02d", i);
//    S[i] = buf;                                      // Text
//    S[i] = Soft_Label_Key_Set::Soft_Label_Key::Left; // Justification
//  }
//}

void TestApplication::title()
{
  const char * const titleText = "Romanian Village Simulator";
  const int len = ::strlen(titleText);

  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - len)/2, titleText);
  titleWindow->noutrefresh();
}


int TestApplication::run()
{
//    init_pair(0, COLOR_MAGENTA, COLOR_RED); // Unknown
//    init_pair(1, COLOR_MAGENTA, COLOR_RED); // Unknown
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Selection cursor in Menu
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Unselectable menu items // TODO Color rest of menu??
    init_pair(4, COLOR_WHITE, COLOR_RED); // Soft key labels
    init_pair(5, COLOR_WHITE, COLOR_RED); // Main window
    init_pair(6, COLOR_WHITE, COLOR_BLUE); // Title Bar

  MyMenu M;
  M();
  return 0;
}

//
// -------------------------------------------------------------------------
//
static TestApplication *Demo = new TestApplication();

//int main()
//{
//    cout << "BEGIN PROGRAM" << endl;
//    WorldMap theMap (3600, 3600);
//    VillageFactory villageFactory (&theMap, -1);
//    Village *village = villageFactory.build();
//    cout << village->toString() << endl;
//    //cin >> age;
//    return 0;
//}
