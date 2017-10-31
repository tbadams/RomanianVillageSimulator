#ifndef ROMANIA_H
#define ROMANIA_H

#include <string.h>
#include <stdlib.h>

#include "WorldMap.h"

class Village : public Place {
    public:
    Village(int xCoord,int yCoord);
    // Todo width, height

};

class VillageFactory {
public:
    VillageFactory(WorldMap* worldMap, int seed);
private:
    WorldMap* theMap;
    public:
    Village * build();
};



class DayTime : public Actor {
private:
    bool sunIsUp;
public:
    // TODO Set up state.
    void act(Scheduler& scheduler);
};


#endif // ROMANIA_H
