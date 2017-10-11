#ifndef ACTOR_H
#define ACTOR_H
#include "WorldMap.h"
#include <string>


class Actor {

    public:
        Actor(std::string, Place);
        virtual ~Actor();
    protected:
    private:
        Place place;
        std::string name;
};

#endif // ACTOR_H
