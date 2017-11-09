#include "WorldMap.h"

// Place
Place::Place(int xCoord, int yCoord)
{
    x = xCoord;
    y = yCoord;
}

std::string Place::toString() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

// TimeController
// TODO Synchronization

TimeController::TimeController(Scheduler scheduler) : scheduler(scheduler)
{

}


void TimeController::tick(long realTime)
{
    // TODO Calculate simulation time that corresponds to passed real time
        //
    long simTime; // TODO Assign

}

void TimeController::setSpeed(double ratio)
{
    // TODO
}

void TimeController::start()
{
    startRealTime = (std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch())).count(); // TODO Parameter?
    // TODO fake time set
    running = true;

}

void TimeController::stop()
{
    running = false;
}


// World
WorldMap::WorldMap(int mapWidth, int mapHeight, Scheduler scheduler) : timeController (scheduler)
{
    width = mapWidth;
    height = mapHeight;
}

WorldMap::~WorldMap()
{
    //dtor
}


