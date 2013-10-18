
#ifndef RTIME_H
#define RTIME_H

namespace rtv
{

class RTime
{
public:
    RTime();

    /*!
     * Capture the current time and set it.
     */
    void start();

    /*!
     * Returns the time passed from start time.
     */
    int elapsed() const;

    /*!
     * Retunns the current time
     */
    static RTime currentTime();

private:
    static unsigned long fromTimeComponentToMS(unsigned long hour,
            unsigned long minute,
            unsigned long sec,
            unsigned long msec = 0);
private:
    unsigned long mMS;
};

}

#endif

