
#ifndef RX11APP_H
#define RX11APP_H

#if !defined(_WIN32)

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace rtv
{

class RApp;

class RAppImpl
{
public:
    RAppImpl(RApp * app)
     : mApp(app),
       mDisplay(0)
    {}

    virtual ~RAppImpl()
    {
    	XCloseDisplay(mDisplay);
    }

    virtual bool init()
    {
        mDisplay = XOpenDisplay( 0 );
        return mDisplay != 0;
    }

    EventData readEvent()
    {
    	EventData appEve;
        XEvent event;
        KeySym key;
        char text[255];

        if (XPending(mDisplay))
        {
			XNextEvent( mDisplay, &event );

			switch (event.type)
			{
				case Expose:
				{
					if (event.xexpose.count == 0)
					{
						appEve.mType = RAPPFWEventDraw;
					}
					break;
				}

				case KeyPress:
				{
					if (XLookupString(&event.xkey,text,255,&key,0)==1)
					{
						appEve.mType = RAPPFWEventKeyPress;
						appEve.mKey = text[0];
					}
					break;
				}

				case ButtonPress:
				{
					appEve.mType = RAPPFWEventButtonClick;
					appEve.mX = event.xbutton.x;
					appEve.mY = event.xbutton.y;
					break;
				}
			}
        }

        return appEve;
    }

    unsigned int handle()
    {
        return (unsigned int)mDisplay;
    }

private:
    RApp *mApp;
    Display                 *mDisplay;
};

}

#endif

#endif
