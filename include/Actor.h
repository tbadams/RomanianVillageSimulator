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
        virtual void act(Scheduler& scheduler) = 0;
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

class Scheduler // TODO Own file.
{
public:
    // TODO File constants?
    const int SECOND    {1};
    const int MINUTE    {60 * SECOND};
    const int HOUR      {60 * MINUTE};
    const int DAY       {24 * HOUR};


    Scheduler();
    // Specify the clock time to initialize to.
    Scheduler(long startTime);
    // Schedule an event a specified amount of time in the future.
    void add(Actor& actor, const int delay);
    // Schedule an event for the specified time.
    void scheduleForTime(Actor& actor, const long absoluteTime);
    // Advance time to next scheduled event and run it.
    void next();
    // Advance clock to specified time, executing all scheduled events.
    void until(long absoluteTime);
    // Advance clock for the specified amount of time.
    void goFor(long duration);
    // Broadcast an event message.
    void postEvent(const Event& event);
    // Get current clock time.
    long getCurTime();
    // Human readable time.
    std::string formatTime(long time);
    // Helper for constructing times
    long makeTime(long secs = 0, int mins = 0, int hour = 0, int day = 0);

private:
    long curTime; // TODO float?
    std::priority_queue<Actor*> schedule;
    Scheduler& self() { return *this; }
};

#endif // ACTOR_H
