#ifndef ACTOR_H
#define ACTOR_H
#include "WorldMap.h"
#include <string>
#include <queue>


class Actor {

    public:
        Actor(std::string, Place);
        virtual ~Actor();
    protected:
    private:
        Place place;
        std::string name;
};

class Scheduler
{
public:
    void add(Actor actor, long time);

private:
    long curTime; // necessary?
    Actor getNext();
    std::priority_queue<Actor> schedule;
};

#endif // ACTOR_H
