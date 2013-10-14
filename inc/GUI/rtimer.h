
#ifndef RTIMER_H
#define RTIMER_H

namespace rtv
{

class RTimer
{
public:
    virtual ~RTimer()
    {}

    /*!
     * Retrieves the interval for the timer.
     */
    int interval()
    {
    	return mInterval;
    }
    
    /*!
     * Sets the interval for the timer.
     */
    void setInterval(int interval)
    {
    	mInterval = interval;
    }

    /*!
     * This function will be getting called once the timer expires.
     */
    virtual void run() = 0;

private:
    int mInterval;
};

}

#endif
