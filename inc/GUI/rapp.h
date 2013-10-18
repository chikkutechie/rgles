
#ifndef RAPP_H
#define RAPP_H

#include "rtime.h"
#include "rtimer.h"
#include "revent.h"

#include <vector>

namespace rtv
{

class RAppImpl;
class RWin;

class RApp
{
public:
    RApp();
    virtual ~RApp();

    virtual bool init();

    virtual void exec();

    void setMainWindow(RWin * window);

    unsigned int handle();

    void registerTimer(RTimer *timer);
    void unregisterTimer(RTimer *timer);

private:
    void checkTimers();

private:
    RAppImpl * mImpl;
    friend class RAppImpl;

protected:
    RWin *mMainWindow;
    bool mFinished;

    class TimerEntry
    {
    public:
        RTime mTime;
        RTimer *mTimer;
    };

    typedef std::vector<TimerEntry> TimerSet;
    typedef TimerSet::iterator TimerSetIter;

    TimerSet mTimers;
};

}

#endif

