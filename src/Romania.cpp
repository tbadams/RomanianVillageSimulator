#include "Romania.h"


Village::Village(int xCoord,int yCoord):Place(xCoord,yCoord) {}



VillageFactory::VillageFactory(WorldMap* worldMap, int seed)
{
    theMap = worldMap;
    long curSeed = seed >= 0 ? seed : time(NULL); // Use seed if provided, else random
    srand(static_cast<unsigned int>(curSeed));
}

Village* VillageFactory::build() {
    return new Village(rand() % (theMap->getWidth()-1), rand() % (theMap->getHeight()-1));
}


void DayTime::act(Scheduler& scheduler)
{
//    std::cout << "DayTime act" << std::endl;
    std::string msg;
    if(!sunIsUp) {
        msg = "The sun rises.";
    } else {
        msg = "The sun sets.";
    }
    sunIsUp = !sunIsUp;
    Event event (msg);
    scheduler.postEvent(event);
    scheduler.add(*this, scheduler.makeTime(0,0,12));
}

