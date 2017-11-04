#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include <queue>
#include <iostream>

class Scheduler;

// Represents a thing that happened in the world (usually)
class Event {
    // TODO Should eventually use funtion pointer type paradigm to generate text from data
    // TODO Timestamp???
public:
    Event(std::string);
    std::string getMessage() const;
private:
    std::string baseMessage;

};

class Actor {
    friend class Scheduler;
    public:
        Actor();
        virtual void act(Scheduler& scheduler);
        friend bool operator< ( Actor const& a, Actor const& b);
        friend bool operator== ( Actor const& a, Actor const& b);
        friend bool operator> ( Actor const& a, Actor const& b);
        virtual ~Actor();
        long getNextAct();
    protected:
    private:
        long nextAct;
        void setNextAct(long);
};

class EventManager {
    // TODO way more accessor options; query/filter...I guess mostly that.

};

class Scheduler
{
public:
    Scheduler();
    Scheduler(long startTime);
    void add(Actor& actor, const int delay);
    void scheduleForTime(Actor& actor, const long absoluteTime);
    void next();
    void until(long absoluteTime);
    void goFor(long duration);
    void postEvent(const Event& event);

private:
    long curTime; // TODO necessary? float?
    std::priority_queue<Actor*> schedule;
    Scheduler& self() { return *this; }
};

#endif // ACTOR_H
