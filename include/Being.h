#ifndef BEING_H
#define BEING_H

#include <string>
#include <random>
#include <cmath>
#include <iostream>

#include "WorldMap.h"
#include "Actor.h"

/*
 A being is an Actor that makes decisions.  On .act(), it uses its mental state to
 choose a Task (finite state) to accomplish (if haven't already) and then execute the
 component Actions of that task.  Between and during their own actions Beings observe their
 surroundings and note all events that transpire and change in physical evironment, then uses these
 inputs the following turn to decide to if task sould be changed.
*/

const double PI = 3.141592653589793;
const int BASE_MOVE_TIME = 1;

enum class TaskType{
    IDLE,
    WANDER
};

class Being;

class Task
{
public:
    Task();
    virtual ~Task();
    // Take actions towards completing task. Returns true if task complete.
    virtual bool doTask(Being &being, Scheduler &scheduler) = 0;
};

class IdleTask : public Task {
public:
    IdleTask(long doneTime, Scheduler &scheduler);
    virtual bool doTask(Being &being, Scheduler &scheduler) override;
private:
    long doneTime;
    Scheduler &scheduler;
};

class WanderTask : public Task {
public:
    WanderTask(Place dest);
    bool doTask(Being &being, Scheduler &scheduler) override;
private:
    Place dest;

};

/*
TODO Other tasks



*/


class Being : public Actor
{
    friend class Task;
    friend class WanderTask; // TODO Why necessary?!?
    public:
        Being(std:: string, Place coords, std::mt19937 &rng);
        virtual ~Being();
        virtual void act(Scheduler& scheduler);
    protected:
    private:
        std::string name;
        Task *curTask; // TODO Can we do without pointer?
        // TODO mental state
        Place coords;
        std::mt19937 &rng;
        void moveTo(const Place &dest, Scheduler &scheduler); // Ugh, i dunno.
};



#endif // BEING_H
