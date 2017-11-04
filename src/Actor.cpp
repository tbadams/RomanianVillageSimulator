#include "Actor.h"

/*
    Actor
*/
Actor::Actor()
{

}
void Actor::act(Scheduler& scheduler)
{
        std::cout << "actor action"<< std::endl;
}

bool operator < (Actor const& lhs, Actor const& rhs)
{
    return lhs.nextAct < rhs.nextAct;
}

bool operator > (Actor const& lhs, Actor const& rhs)
/*
    Event
*/
{
    return lhs.nextAct > rhs.nextAct;
}

bool operator == (Actor const& lhs, Actor const& rhs)
{
    return lhs.nextAct == rhs.nextAct;
}

long Actor::getNextAct()
{
    return nextAct;
}

// Set the time the Actor will next act
void Actor::setNextAct(long newAct)
{
    nextAct = newAct;
}

Actor::~Actor()
{
    //dtor
}

/*
    Event
*/
Event::Event(std::string message)
{
    baseMessage = message;
}

std::string Event::getMessage() const
{
    return baseMessage;
}

/*
    Scheduler
*/
Scheduler::Scheduler() : Scheduler(0)
{
//    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1);};
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
}

Scheduler::Scheduler(long startTime) : curTime {startTime}, schedule {}
{

}

void Scheduler::scheduleForTime(Actor& actor, const long absoluteTime)
{
    std::cout << "Scheduler.scheduleForTime() at " << absoluteTime << std::endl;
    actor.setNextAct(absoluteTime);
    schedule.push(&actor);
}

void Scheduler::add(Actor& actor, const int delay)
{
    scheduleForTime(actor, curTime + delay);
}

void Scheduler::next()
{
    std::cout << "Scheduler.next()" << std::endl;
    // TODO Empty?
    Actor *next = schedule.top();
    if(next->nextAct > curTime) {
        curTime = next->nextAct;
    }
    schedule.pop();
    next->act(self());
}

void Scheduler::until(long absoluteTime)
{
    std::cout << "Scheduler.until()" << std::endl;
    while(!schedule.empty() && schedule.top()->nextAct <= absoluteTime)
    {
        next();
    }
    curTime = absoluteTime;
    std::cout << "curTime is now " << curTime << std::endl;
}

void Scheduler::goFor(long duration)
{
    until(curTime + duration);
}

void Scheduler::postEvent(const Event& event)
{
    std::cout << curTime << ": " << event.getMessage() << std::endl;
}



