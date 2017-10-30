#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>

#include <cursesapp.h>
#include <cursesm.h>
#include <cursesf.h>
#include <menu.h>

#include "WorldMap.h"

#ifndef __MINGW32__
extern "C" unsigned int sleep(unsigned int); // TODO Make portable??
#endif

using namespace std;

// Can define 256 colors
/*
9 - bright red
10 bright green
11 Br. Yellow
12 Br. Blue
13 Br. Magenta
14 Br. Cyan
15 Br. White
16 blaack
17 - ? blues
*/
const int COLOR_ORANGE = 9;

void doStuff(int key);

class Village : public Place {
public:
    Village(int xCoord,int yCoord):Place(xCoord,yCoord) {}
    // Todo width, height

};

class VillageFactory {
public:
    VillageFactory(WorldMap* worldMap, int seed) {
        theMap = worldMap;
        long curSeed = seed >= 0 ? seed : time(NULL); // Use seed if provided, else random
        srand(static_cast<unsigned int>(curSeed));
    }
private:
    WorldMap* theMap;
    public:
    Village * build();
};

Village* VillageFactory::build() {

    return new Village(rand() % (theMap->getWidth()-1), rand() % (theMap->getHeight()-1));
}

class DayTime : public Actor {
private:
    bool sunIsUp;
public:
    // TODO Set up state.
    void act(Scheduler& scheduler) {
        std:string msg;
        if(!sunIsUp) {
            msg = "The sun rises.";
        } else {
            msg = "The sun sets.";
        }
        sunIsUp = !sunIsUp;
        Event event (msg);
        scheduler.postEvent(event);
        scheduler.add(*this, 60 * 24);
    }
};


/*
FRONT END
*/

//class ScanAction : public NCursesMenuItem
//{
//public:
//  ScanAction(const char* s) : NCursesMenuItem(s) {
//  }
//
//  bool action() {
//    NCursesPanel *mystd = new NCursesPanel();
//
//    NCursesPanel *w = new NCursesPanel(mystd->lines() - 2, mystd->cols() - 2, 1, 1);
//    w->box();
//    w->bkgd(' '|COLOR_PAIR(1));
//    w->refresh();
//
//    NCursesPanel *s = new NCursesPanel(w->lines() - 6, w->cols() - 6, 3, 3);
//        s->setpalette(COLOR_GREEN, COLOR_YELLOW);
//    s->scrollok(TRUE);
//    ::echo(); // Probably temprarily enable printing input chars
//
//    s->printw("Enter decimal integers.  The running total will be shown\n");
//    int nvalue = -1;
//    int result = 0;
//    while (nvalue != 0) {
//      nvalue = 0;
//      s->scanw("%d", &nvalue);
//      if (nvalue != 0) {
//        s->printw("%d: ", result += nvalue);
//      }
//      s->refresh();
//              s->setpalette(COLOR_GREEN, COLOR_YELLOW);
//    }
//    s->printw("\nPress any key to continue...");
//    s->getch(); // get input
//
//    delete s;
//    delete w;
//    delete mystd;
//    ::noecho(); // re-enable no echoing
//    return FALSE; // dunno why false
//  }
//};
//
//class UserData
//{
//private:
//  int u;
//public:
//  UserData(int x) : u(x) {}
//  int sleeptime() const { return u; }
//};
//
//class PadAction : public NCursesMenuItem
//{
//public:
//  PadAction(const char* s) : NCursesMenuItem(s) {
//  }
//
//  bool action() {
//    const int GRIDSIZE = 3;
//    const int PADSIZE  = 200;
//    unsigned gridcount = 0;
//
//    NCursesPanel mystd;
//    NCursesPanel P(mystd.lines()-2, mystd.cols()-2, 1, 1);
//    NCursesFramedPad FP(P, PADSIZE, PADSIZE);
//
//    for (int i=0; i < PADSIZE; i++) {
//      for (int j=0; j < PADSIZE; j++) {
//        if (i % GRIDSIZE == 0 && j % GRIDSIZE == 0) {
//          if (i==0 || j==0)
//            FP.addch('+');
//          else
//            FP.addch(static_cast<chtype>('A' + (gridcount++ % 26)));
//        }
//        else if (i % GRIDSIZE == 0)
//          FP.addch('-');
//        else if (j % GRIDSIZE == 0)
//          FP.addch('|');
//        else
//          FP.addch(' ');
//      }
//    }
//
//    P.label("Pad Demo", NULL);
//    FP();
//    P.clear();
//    return FALSE;
//  }
//};

class ChildPad : public NCursesFramedPad {
    public:
    ChildPad(NCursesWindow& win, int nlines, int ncols) : NCursesFramedPad(win, nlines, ncols){}

};

// TODO When I try to subclass ChildPad window doesn't appear.
class EventPad : public NCursesFramedPad {
private:
    bool (*inputCallback)(int key);
    public:
        EventPad(NCursesWindow& win, int nlines, int ncols, bool (*input)(int key)): NCursesFramedPad(win, nlines, ncols), inputCallback(input) {}
    protected:
        virtual int driver (int key);
//        void operator ()(void) {

//        }
};

int EventPad::driver(int key) {
    bool status = inputCallback(key);
    printw("This line created by EventPad::driver\n");
    refresh();
    // TODO Don't return if don't want to
    return NCursesFramedPad::driver(key);
}

//class PassiveItem : public NCursesMenuItem
//{
//public:
//  PassiveItem(const char* text) : NCursesMenuItem(text) {
//    options_off(O_SELECTABLE);
//  }
//};
//
//
//class MyMenu : public NCursesMenu
//{
//private:
//  NCursesPanel* P;
//  NCursesMenuItem** I;
//  UserData *u;
//  #define n_items 6
//
//public:
//  MyMenu ()
//    : NCursesMenu (lines() - 1, 16, 0, 0),
//      P(0), I(0),
//      u(0)
//      // TODO Expose constructor!
//  {
//    u = new UserData(1);
//    I = new NCursesMenuItem*[1+n_items];
//    I[0] = new PassiveItem("One");
//    I[1] = new PassiveItem("Two");
//    I[2] = new NCursesMenuItem("Three");
//    I[3] = new NCursesMenuItem("Form"); // FormAction
//    I[4] = new PadAction("Pad");
//    I[5] = new ScanAction("Scan");
////    I[6] = new QuitItem();
//    I[n_items] = new NCursesMenuItem(); // Terminating empty item
//
//    InitMenu(I, TRUE, TRUE);
//
//    P = new NCursesPanel(1, n_items, LINES-1, 1);
//    boldframe("Menu", "Menu");
//    P->show();
//  }
//
//  MyMenu& operator=(const MyMenu& rhs)
//  {
//    if (this != &rhs) {
//      *this = rhs;
//    }
//    return *this;
//  }
//
//  MyMenu(const MyMenu& rhs)
//    : NCursesMenu(rhs), P(0), I(0), u(0)
//  {
//  }
//
//  ~MyMenu()
//  {
//    P->hide();
//    delete P;
//    delete u;
//  }
//
//  virtual void On_Menu_Init()
//  {
//    NCursesWindow W(::stdscr);
//    P->move(0, 0);
//    P->clrtoeol();
//    for(int i=1; i<=count(); i++)
//      P->addch('0' + i);
//    P->bkgd(W.getbkgd());
//    refresh();
//  }
//
//  virtual void On_Menu_Termination()
//  {
//    P->move(0, 0);
//    P->clrtoeol();
//    refresh();
//  }
//
//  virtual void On_Item_Init(NCursesMenuItem& item)
//  {
//    P->move(0, item.index());
//    P->attron(A_REVERSE);
//    P->printw("%1d", 1+item.index());
//    P->attroff(A_REVERSE);
//    refresh();
//  }
//
//  virtual void On_Item_Termination(NCursesMenuItem& item)
//  {
//    P->move(0, item.index());
//    P->attroff(A_REVERSE);
//    P->printw("%1d", 1+item.index());
//    refresh();
//  }
//
//  virtual int virtualize( int c) {
//        switch(c) {
//            case KEY_F(1):
//            {
//                ScanAction scanAction ("wangs");
//                scanAction.action();
////                return (MAX_COMMAND + 1);
//                break;
//            }
//        }
//        return NCursesMenu::virtualize(c);
//  }
//};

class TestApplication : public NCursesApplication {
protected:
  int titlesize() const { return 1; }
  void title();
  Soft_Label_Key_Set::Label_Layout useSLKs() const {
    return Soft_Label_Key_Set::PC_Style_With_Index;
  }
  // TODO Re enable
//  void init_labels(Soft_Label_Key_Set& S) const;

public:
  TestApplication() : NCursesApplication(TRUE) {
  }
    void virtualize(int);
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

void TestApplication::virtualize(int c) {
    switch(c) {

    }
}

void TestApplication::title()
{
  const char * const titleText = "Romanian Village Simulator";
  const int len = ::strlen(titleText);

  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - len)/2, titleText);
  titleWindow->noutrefresh();
}

bool appInput(int key) {
    // TODO Stuff
    return false;
}

int TestApplication::run()
{
    // Simulations
    cout << "BEGIN PROGRAM" << endl;
    Scheduler scheduler;
    WorldMap theMap (3600, 3600, scheduler);
    VillageFactory villageFactory (&theMap, -1);
    Village *village = villageFactory.build();
    cout << village->toString() << endl;

    NCursesPanel mystd;
    init_color(COLOR_ORANGE, 999, 500, 0); // TODO Doesn't appear to work
    init_pair(7, COLOR_WHITE, COLOR_ORANGE); // TODO Doesn't appear to work
//    init_pair(0, COLOR_MAGENTA, COLOR_RED); // Unknown
//    init_pair(1, COLOR_MAGENTA, COLOR_RED); // Unknown
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Selection cursor in Menu
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Unselectable menu items // TODO Color rest of menu??
    init_pair(4, COLOR_WHITE, COLOR_RED); // Soft key labels
    init_pair(5, COLOR_WHITE, COLOR_RED); // Main window
    init_pair(6, COLOR_WHITE, COLOR_BLUE); // Title Bar

    // Time panel
    NCursesPanel *timePanel = new NCursesPanel(8, 20, 10, 3);
      timePanel->bkgd(' '|COLOR_PAIR(1));
    mystd.refresh();
    NCursesPanel pane;

    // Event Window
    const int PAD_LENGTH = 250;
    NCursesPanel P(mystd.lines()-2, mystd.cols()-2, 1, 1);
    EventPad EP(P, PAD_LENGTH, mystd.cols() - 3, appInput);
    P.label("Events", NULL);
    EP(); // TODO Can we have pad show up with while loop in parent view?
//    while(true) {
//
//    }
//  MyMenu M;
//  M();
  return 0;
}

//
// -------------------------------------------------------------------------
//
static TestApplication *Demo = new TestApplication();



//int main()
//{

//    return 0;
//}
