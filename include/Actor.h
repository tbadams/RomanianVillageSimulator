#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include <queue>

class Scheduler;

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

class Scheduler
{
public:
    Scheduler();
    void add(Actor& actor, const int delay);
    void scheduleForTime(Actor& actor, const long absoluteTime);
    void next();
    void until(long absoluteTime);
    void goFor(long duration);

private:
    long curTime; // TODO necessary? float?
    std::priority_queue<Actor> schedule;
    Scheduler& self() { return *this; }
};

#endif // ACTOR_H
