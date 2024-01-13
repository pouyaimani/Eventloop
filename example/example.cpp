#include "Eventloop.h"
#include "Timer/Timer.h"
#include <iostream>

class testTimerTask : public TimerTask
{
    public:
    void runTimerTask() {
        std::cout << "Timer is running \n";
    }
};

int main()
{
    Eventloop::init();
    testTimerTask timerTask;
    Timer timer(&timerTask);
    timer.start(1000);
    while (1)
    {
        /* code */
    }
    
}