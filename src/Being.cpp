#include "Being.h"

Task::Task()
{

}

Task::~Task()
{

}

bool Task::doTask()
{
    return true;
}

/*
Concrete tasks.
*/
IdleTask::IdleTask(long doneTime, Scheduler &scheduler) : doneTime {doneTime}, scheduler {scheduler}
{

}

bool IdleTask::doTask()
{
    return scheduler.getCurTime() >= doneTime;
}

WanderTask::WanderTask(long)
{

}


bool WanderTask::doTask()
{

}


/*
Being itself
*/
Being::Being(std:: string name, Place coords, std::mt19937 &rng) : name {name}, coords {coords}, rng {rng}
{

}


Being::~Being()
{
    //dtor
}


void Being::act(Scheduler& scheduler)
{
    // If SOMEHOW DETERMINE HAVE NO TASK
        // Then determine task with subroutine with access to whole Being object

    // Call .doTask() on our task, providing Being object as param, maybe more...
    // Schedule self for ??? in the future
    // TODO What if dead???
    // Determine if task done using ??? and then... ???
}

void Being::moveTo(const Place &dest)
{ //
    int dx = dest.getX() - coords.getX();
    int dy = dest.getY() - coords.getY();

}


/*
    Maybe another layer of abstraction, where task provides goals and Being makes decision on how to acheive?
*/
