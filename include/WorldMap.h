#ifndef WORLDMAP_H
#define WORLDMAP_H
#include <chrono>
#include <unordered_map>
#include <string>
#include "Actor.h"

class WorldMap;
class TimeController;

class Place {
private:
    int x,y;
    // TODO Size?
    std::string name;
public:
    Place(int,int);

    int getX(){return x;}
    int getY(){return y;}
    void add(Place place);
    std::string toString();
};

class TimeController {
private:
    Scheduler scheduler;
    long startRealTime;
    long startSimTime;
    bool running;
public:
    TimeController(Scheduler);
    void tick(long realTime);
    // TODO Create with time offset
    // TODO Error returns of some kind.
    void setSpeed(double ratio);
    void start();
    void stop();
};

class WorldMap
{
    public:
        WorldMap(int,int, Scheduler);
        virtual ~WorldMap();
        void add(Place place);
        int getWidth(){return width;}
        int getHeight(){return height;}
        Scheduler getScheduler() {return scheduler;}
        TimeController getTimeController() {return timeController;}
    protected:
    private:
        int width, height;
        Scheduler scheduler;
        TimeController timeController;
};

#endif // WORLDMAP_H
