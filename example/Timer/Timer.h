#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <signal.h>
#include <Eventloop.h>

/*
** each client which wants to use timer must inherit a class form TimerTask 
** and implement runTimerTask() method
*/
class TimerTask
{
    public:
    virtual void runTimerTask() = 0;
};

class Timer
{
    private:
    uint16_t  durMs;
    TimerTask *timerTask;
    static long long getTimeMs();
    pthread_mutex_t mutex;
    long long startTime;
    sig_atomic_t stopFlag;
    Event *timerEvent;

    /*
    ** TimerEvent inherit form Event class and implement check interface
    ** Check interface execute timer handle() method
    */

    class TimerEvent : public Event 
    {
        private:
        Timer *timer;

        public:
        TimerEvent(Timer *t) {
            timer = t;
        }
        void check() {
            timer->handle();
        }
    };

    public:
    explicit Timer(TimerTask *_timerTask);
    ~Timer();
    void handle();
    void start(uint16_t ms);
    void stop();
};

#endif