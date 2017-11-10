#include "Being.h"

Task::Task()
{

}

Task::~Task()
{

}

bool Task::doTask(Being &being, Scheduler &scheduler)
{
    return true;
}

/*
Concrete tasks.
*/
IdleTask::IdleTask(long doneTime, Scheduler &scheduler) : doneTime {doneTime}, scheduler {scheduler}
{

}

bool IdleTask::doTask(Being &being, Scheduler &scheduler)
{
    return scheduler.getCurTime() >= doneTime;
}

WanderTask::WanderTask(Place dest) : dest {dest}
{

}

bool WanderTask::doTask(Being &being, Scheduler &scheduler)
{
    being.moveTo(dest, scheduler);
}


/*
Being itself
*/
Being::Being(std:: string name, Place coords, std::mt19937 &rng) : name {name}, coords {coords}, rng {rng}
{
    std::cout << "Constructing Being " + name + " at " + coords.toString() + "\n";
    Place place {0,0};
    WanderTask aTask {place};
    curTask = &aTask;
}


Being::~Being()
{
    //dtor
}


void Being::act(Scheduler& scheduler)
{
    std::cout << "Being.act()\n";
    // If SOMEHOW DETERMINE HAVE NO TASK
        // Then determine task with subroutine with access to whole Being object

    // Call .doTask() on our task, providing Being object as param, maybe more...
    Being thisRef = *this;
    curTask->doTask(thisRef, scheduler);
    // Schedule self for ??? in the future
    // TODO What if dead???
    // Determine if task done using ??? and then... ???
}

Place chooseCardinal(const Place &start, const Place &dest) {
    std::cout << "chooseCardinal " + start.toString() + " to " + dest.toString() + ".\n";
    // TODO Error if the same?
    int dx = dest.getX() - start.getX();
    int dy = dest.getY() - start.getY();
    int dxSign = (dx > 0) - (dx < 0); // TODO Expose elsewhere
    int dySign = (dy > 0) - (dy < 0);

    // non-diagonal movement only
    if(std::abs(dx) >= std::abs(dy)) {
        return Place {start.getX() + dxSign, start.getY()};
    }

//    // TODO Must be a better way.
//    double radians = std::atan2(dy, dx);
//    double sixteenth = (2 * PI) / 16;
//    //int xDelta = // in 8s, 0,1, -3, -4, -5, 7
    return Place {start.getX(), start.getY() + dySign};
}

void Being::moveTo(const Place &dest, Scheduler &scheduler)
{
    std::cout << "moveTo " + dest.toString() + "\n";
    coords = chooseCardinal(coords, dest);
    Event event {name + " moved to " + coords.toString() + "."};
    scheduler.postEvent(event);
    // TODO post self again
}


/*
    Maybe another layer of abstraction, where task provides goals and Being makes decision on how to acheive?
*/
