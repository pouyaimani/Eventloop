#include "Eventloop.h"

pthread_t Eventloop::loopThread;
std::list<Event *> Eventloop::eventList;
pthread_mutex_t Eventloop::mutex;
Eventloop * Eventloop::eventloop = NULL;

/* Event thread to concurently check new events with other threads */
void *checkEvents(void *args)
{
    while (1) {
        std::list<Event *>::iterator it;
        /* If event list is empty release control of processor 
        ** The thread is moved to the end of the queue
        */
       pthread_mutex_lock(&Eventloop::mutex);
        if (Eventloop::eventList.empty()) {
            pthread_mutex_unlock(&Eventloop::mutex);
            sched_yield();
        }
        else {
            for(it = Eventloop::eventList.begin() ; it != Eventloop::eventList.end() ; it++) {
                (*it)->check();
            }
        }
        pthread_mutex_unlock(&Eventloop::mutex);
    }
}

/* Event loop constructor to create and detach the event thread */
Eventloop::Eventloop()
{
    pthread_create(&Eventloop::loopThread, NULL, &checkEvents, NULL);
    pthread_detach(Eventloop::loopThread);
}

void Eventloop::init()
{
    if (pthread_mutex_init(&mutex, NULL) == 0) {
        std::cout << "Eventloop mutex init succeed. \n";
    } else {
        std::cout << "Eventloop mutex init failed. \n";
    }
    getInstance();
}

/* Instantiate the event loop.
** Event loop use singleton design pattern to ensure just only one object is instantiated
 */
Eventloop *Eventloop::getInstance()
{
    if(eventloop == NULL)
        eventloop = new Eventloop();
    return eventloop;
}

/* append() method to append events */
EventloopErr_t Eventloop::append(Event **event)
{
    pthread_mutex_lock(&mutex);
    std::list<Event *>::iterator it;
    for(it = eventList.begin() ; it != eventList.end() ; it++) {
        if((*it) == *event) {
            pthread_mutex_unlock(&mutex);
            return EVL_ERR_EVENT_EXISTS;
        }
    }
    eventList.push_back(*event);
    pthread_mutex_unlock(&mutex);
    return EVL_ERR_OK;
}

/* remove() method to remove events */
void Eventloop::remove(Event **event)
{
    pthread_mutex_lock(&mutex);
    std::list<Event *>::iterator it;
    Event *ev = NULL;
    for(it = eventList.begin() ; it != eventList.end() ; it++) {
        std::cout << "event = " << (*it) << "\n";
        if((*it) == *event) {
            ev = *it;
        }
    }
    if(ev != NULL) {
        eventList.remove(ev);

    }
    pthread_mutex_unlock(&mutex);
}