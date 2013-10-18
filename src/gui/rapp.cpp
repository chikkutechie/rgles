
#include "GUI/rapp.h"
#include "GUI/rwin.h"

#include <iostream>

#if defined(_WIN32)
#include "rwin32app.h"
#else
#include "rx11app.h"
#endif

namespace rtv
{

RApp::RApp()
 : mImpl(0),
   mMainWindow(0),
   mFinished(false)
{
    mImpl = new RAppImpl(this);
}

RApp::~RApp()
{
    delete mImpl;
}

bool RApp::init()
{
    return mImpl->init();
}

void RApp::exec()
{
    if (mImpl->init())
    {
        if (mMainWindow)
        {
            if (!mMainWindow->create())
            {
                std::cerr << "Main window creation failed" << std::endl;
                mFinished = true;
            }
            else
            {
                mMainWindow->show();
            }
        }
        else
        {
            std::cerr << "Main window not set" << std::endl;
            mFinished = true;
        }
    }
    else
    {
        std::cerr << "Application initialization failed" << std::endl;
        mFinished = true;
    }

    while (!mFinished)
    {
    	EventData eve = mImpl->readEvent();

    	switch (eve.mType)
    	{
    	case RAPPFWEventReshape:
    		break;

    	case RAPPFWEventButtonClick:
    		break;

    	case RAPPFWEventKeyPress:
    		break;

    	case RAPPFWEventDraw:
    		if (mMainWindow)
    		{
    			mMainWindow->draw();
    		    mMainWindow->flush();
    		}
    		break;

        case RAPPFWEventExit:
    		mFinished = true;
    		break;

    	default:
    		{
    		break;
    		}
    	}

    	// check for timers to execution
		// this may not be the perfect way to implement
		// but this is good enough
		checkTimers();
    }
}

unsigned int RApp::handle()
{
    return mImpl->handle();
}

void RApp::setMainWindow(RWin * window)
{
    mMainWindow = window;
    mMainWindow->setApp(this);
}

void RApp::registerTimer(RTimer *timer)
{
    TimerEntry entry;
    entry.mTime.start();
    entry.mTimer = timer;
    mTimers.push_back(entry);
}

void RApp::unregisterTimer(RTimer *timer)
{
    for (TimerSetIter iter = mTimers.begin(); iter != mTimers.end(); ++iter) {
        if (iter->mTimer == timer) {
            mTimers.erase(iter);
            break;
        }
    }
}

void RApp::checkTimers()
{
    if (mTimers.empty()) {
        return;
    }

    std::vector<TimerEntry> expiredTimers;

    for (unsigned int i = 0; i < mTimers.size();) {
        TimerEntry &te = mTimers[i];
        if (te.mTimer->interval() < te.mTime.elapsed()) {
            expiredTimers.push_back(te);
            mTimers.erase(mTimers.begin() + i);
        } else {
            ++i;
        }
    }

    int expiredTimersCount = expiredTimers.size();
    for (int i = 0; i < expiredTimersCount; ++i) {
        expiredTimers[i].mTimer->run();
    }
}

}
