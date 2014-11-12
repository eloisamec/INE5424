// EPOS Alarm Abstraction Declarations

#ifndef __alarm_h
#define __alarm_h

#include <utility/queue.h>
#include <utility/handler.h>
#include <tsc.h>
#include <rtc.h>
#include <timer.h>
#include <semaphore_kernel.h>

__BEGIN_SYS

class Alarm
{
    friend class System;

private:
    typedef Timer::Tick Tick;  
    typedef Relative_Queue<Alarm, Tick> Queue;

public:
    typedef TSC::Hertz Hertz;
    typedef RTC::Microsecond Microsecond;
    
    // Infinite times (for alarms)
    enum { INFINITE = RTC::INFINITE };
    
public:
    Alarm(Microsecond time, Handler * handler, int times = 1);
    ~Alarm();

    static Hertz frequency() { return _timer->frequency(); }

    static void delay(Microsecond time);

private:
    static void init();

    static Microsecond period() {
        return 1000000 / frequency();
    }

    static Tick ticks(const Microsecond & time) {
        return (time + period() / 2) / period();
    }

    static void lock() { Thread::lock(); }
    static void unlock() { Thread::unlock(); }

    static void handler();

private:
    Tick _ticks;
    Handler * _handler;
    int _times; 
    Queue::Element _link;

    static Alarm_Timer * _timer;
    static volatile Tick _elapsed;
    static Queue _request;
};


class Delay
{
private:
    typedef RTC::Microsecond Microsecond;

public:
    Delay(const Microsecond & time): _time(time)  { Alarm::delay(_time); }

private:
    Microsecond _time;
};

__END_SYS

#endif
