#ifndef WORLDMAP_H
#define WORLDMAP_H
#include <unordered_map>
#include <string>
#include "Actor.h"

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

class WorldMap
{
    public:
        WorldMap(int,int);
        virtual ~WorldMap();
        void add(Place place);
        int getWidth(){return width;}
        int getHeight(){return height;}
        Scheduler getScheduler() {return scheduler;}
    protected:
    private:
        int width, height;
        Scheduler scheduler;
};



#endif // WORLDMAP_H
