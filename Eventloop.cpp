#include "Eventloop.h"

pthread_t Eventloop::loopThread;
std::list<Event *> Eventloop::eventList;
pthread_mutex_t Eventloop::mutex;
Eventloop * Eventloop::eventloop = NULL;

void *checkEvents(void *args)
{
    while (1) {
        std::list<Event *>::iterator it;
        for(it = Eventloop::eventList.begin() ; it != Eventloop::eventList.end() ; it++) {
            pthread_mutex_lock(&(*it)->mutex);
            (*it)->check();
            pthread_mutex_unlock(&(*it)->mutex);
        }
    }
}

Eventloop::Eventloop()
{
    pthread_create(&Eventloop::loopThread, NULL, &checkEvents, NULL);
    pthread_detach(Eventloop::loopThread);
}

void Eventloop::init()
{
    pthread_mutex_init(&mutex, NULL);
    getInstance();
}

Eventloop *Eventloop::getInstance()
{
    if(eventloop == NULL)
        eventloop = new Eventloop();
    return eventloop;
}

EventloopErr_t Eventloop::append(Event *event)
{
    pthread_mutex_lock(&mutex);
    std::list<Event *>::iterator it;
    for(it = eventList.begin() ; it != eventList.end() ; it++) {
        if((*it) == event) {
            pthread_mutex_unlock(&mutex);
            return EVL_ERR_EVENT_EXISTS;
        }
    }
    eventList.push_back(event);
    pthread_mutex_unlock(&mutex);
}

void Eventloop::remove(Event *event)
{
    pthread_mutex_lock(&mutex);
    std::list<Event *>::iterator it;
    for(it = eventList.begin() ; it != eventList.end() ; it++) {
        if((*it) == event)
        eventList.remove(event);
    }
    pthread_mutex_unlock(&mutex);
}