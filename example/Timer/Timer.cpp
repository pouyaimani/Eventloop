#include "Timer.h"
#include <sys/time.h>

Timer::Timer(TimerTask *_timerTask)
{
    timerEvent = new TimerEvent(this);
    Eventloop::append(timerEvent);
    timerTask = _timerTask;
    stopFlag = false;
}

Timer::~Timer()
{
    pthread_mutex_lock(&mutex);
    Eventloop::remove(timerEvent);
    pthread_mutex_lock(&mutex);
}

void Timer::start(uint16_t ms)
{
    pthread_mutex_lock(&mutex);
    durMs = ms;
    startTime = getTimeMs();
    pthread_mutex_lock(&mutex);
    stopFlag = false;
}

void Timer::stop()
{
    stopFlag = true;
}

long long Timer::getTimeMs()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void Timer::handle()
{
    pthread_mutex_lock(&mutex);
    if (!stopFlag) {
        if (getTimeMs() - startTime >= durMs) {
            timerTask->runTimerTask();
            startTime = getTimeMs();
        }
    }
    pthread_mutex_lock(&mutex);
}