#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include <pthread.h>
#include <list>

typedef enum {
    EVL_ERR_OK = 0,
    EVL_ERR_EVENT_EXISTS,
    EVL_ERR_EVENT_NOT_EXISTS
} EventloopErr_t;

/* Every event which wants to use event loop must inherit event class and implement check interface */
class Event 
{
    public:
    pthread_mutex_t mutex;
    Event() {
        pthread_mutex_init(&mutex, NULL);
    }
    virtual void check() = 0;

};

class Eventloop
{
    private:
    static pthread_t loopThread;
    static Eventloop *eventloop;

    protected:
    Eventloop();

    public:
    static pthread_mutex_t mutex;
    static void init();
    static Eventloop *getInstance();
    static EventloopErr_t append(Event *event);
    static void remove(Event *event);

    static std::list<Event *> eventList;

};

#endif