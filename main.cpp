#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cursesapp.h>
#include <cursesm.h>
#include <cursesf.h>

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

class UserData
{
private:
  int u;
public:
  UserData(int x) : u(x) {}
  int sleeptime() const { return u; }
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
  #define n_items 2

public:
  MyMenu ()
    : NCursesMenu (n_items+2, 8, (lines()-10)/2, (cols()-10)/2),
      P(0), I(0),
      u(0)
  {
    u = new UserData(1);
    I = new NCursesMenuItem*[1+n_items];
    I[0] = new PassiveItem("One");
    I[1] = new PassiveItem("Two");
//    I[2] = new MyAction<UserData> ("Silly", u);
//    I[3] = new FormAction("Form");
//    I[4] = new PadAction("Pad");
//    I[5] = new ScanAction("Scan");
//    I[6] = new QuitItem();
    I[2] = new NCursesMenuItem(); // Terminating empty item

    InitMenu(I, TRUE, TRUE);

    P = new NCursesPanel(1, n_items, LINES-1, 1);
    boldframe("Demo", "Silly");
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
