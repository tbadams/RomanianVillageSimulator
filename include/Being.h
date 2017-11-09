#ifndef BEING_H
#define BEING_H

#include <string>
#include <random>

#include "WorldMap.h"
#include "Actor.h"

/*
 A being is an Actor that makes decisions.  On .act(), it uses its mental state to
 choose a Task (finite state) to accomplish (if haven't already) and then execute the
 component Actions of that task.  Between and during their own actions Beings observe their
 surroundings and note all events that transpire and change in physical evironment, then uses these
 inputs the following turn to decide to if task sould be changed.
*/

enum class TaskType{
    IDLE,
    WANDER
};

class Task
{
public:
    Task();
    virtual ~Task();
    // Take actions towards completing task. Returns true if task complete.
    virtual bool doTask() = 0;
};

class IdleTask : public Task {
public:
    IdleTask(long doneTime, Scheduler &scheduler);
    virtual bool doTask() override;
private:
    long doneTime;
    Scheduler &scheduler;
};

class WanderTask : public Task {
public:
    WanderTask(long );
    bool doTask() override;

};

/*
TODO Other tasks



*/


class Being : public Actor
{
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
        void moveTo(const Place &dest);
};



#endif // BEING_H
