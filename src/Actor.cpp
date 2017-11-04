#include "Actor.h"

/*
    Actor
*/
Actor::Actor()
{

}
void Actor::act(Scheduler& scheduler)
{
    // Override
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

Event::Event(std::string message)
{
    baseMessage = message;
}

std::string Event::getMessage() const
{
    return baseMessage;
}


Scheduler::Scheduler()
{
//    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1);};
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
}

void Scheduler::scheduleForTime(Actor& actor, const long absoluteTime)
{
    actor.setNextAct(absoluteTime);
    schedule.push(actor);
}

void Scheduler::add(Actor& actor, const int delay)
{
    scheduleForTime(actor, curTime + delay);
}

void Scheduler::next()
{
    // TODO Empty?
    Actor next = schedule.top();
    if(next.nextAct > curTime) {
        curTime = next.nextAct;
    }
    next.act(self());
}

void Scheduler::until(long absoluteTime)
{
    while(schedule.top().nextAct <= absoluteTime) {
        next();
    }
    curTime = absoluteTime;
}

void Scheduler::goFor(long duration)
{
    until(curTime + duration);
}

void Scheduler::postEvent(const Event& event)
{

}



