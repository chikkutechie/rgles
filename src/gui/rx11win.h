
#ifndef RX11WIN_H
#define RX11WIN_H

#if !defined(_WIN32)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/X.h>
#include <X11/Xutil.h>

#include <cstring>
#include <iostream>

#include "GUI/rapp.h"
#include "GUI/rwin.h"

namespace rtv
{

static Bool WaitForNotify(Display *d, XEvent *e, char *arg)
{
  return (e->type == MapNotify) && (e->xmap.window == (Window)arg);
}

class RWinImpl
{
public:
    RWinImpl(RApp *app, RWin * mHandle)
     : mApp(app),
       mWin(mHandle),
       mHandle(0),
       mTitle("RAPPFW"),
       mX(100),
       mY(100),
       mWidth(256),
       mHeight(256)
    {}

    ~RWinImpl()
    {
        XFreeGC((Display *)mApp->handle(), mGC);
        XDestroyWindow((Display *)mApp->handle(), mHandle);
    }

    void setApp(RApp *app)
    {
        mApp = app;
    }

    void setWin(RWin *w)
    {
        mWin = w;
    }

    virtual bool create()
    {
    	bool result = true;
    	unsigned long black;
    	unsigned long white;
    	int n;
    	XVisualInfo vinfo;
    	XVisualInfo *vi;
    	Colormap cmap;
    	XSetWindowAttributes swa;
    	XEvent event;
        Display * dis = (Display *)mApp->handle();

    	mScreen = XDefaultScreen(dis);

    	black = XBlackPixel(dis,mScreen),
    	white = XWhitePixel(dis, mScreen);

    	XMatchVisualInfo (dis, mScreen, 32, TrueColor, &vinfo);

    	vi = XGetVisualInfo(dis, VisualAllMask, &vinfo, &n);
    	cmap = XCreateColormap( dis, RootWindow(dis, vi->screen),
    	             	 	    vi->visual, AllocNone );

    	swa.colormap = cmap;
    	swa.border_pixel = 0;
    	swa.event_mask = StructureNotifyMask;

    	mHandle = XCreateWindow( dis, RootWindow(dis, vi->screen), 0, 0, mWidth, mHeight,
                                 0, vi->depth, InputOutput, vi->visual,
                                 CWBorderPixel|CWColormap|CWEventMask, &swa );



    	XSetStandardProperties(dis, mHandle, mTitle.c_str(), mTitle.c_str(), None, NULL, 0, 0);

    	XSelectInput(dis, mHandle, ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask);

    	mGC = XCreateGC(dis, mHandle, 0,0);

    	XSetForeground(dis, mGC, white);
    	XSetBackground(dis, mGC, black);
    	XClearWindow(dis, mHandle);

    	XMapWindow(dis, mHandle);
    	XIfEvent(dis, &event, WaitForNotify, (char*)mHandle);

		mWin->onCreate();

        return result;
    }

    void flush()
    {
		XFlush((Display *)mApp->handle());
    }

    void show()
    {
    }

    void setPosition(int x, int y)
    {
        mX = x;
        mY = y;
    }

    void setSize(int w, int h)
    {
        mWidth = w;
        mHeight = h;
    }

    void setTitle(std::string const & title)
    {
    	mTitle = title;
    }

    void blit(int dx, int dy, int width, int height, unsigned char * data)
    {
    	Display * dis = (Display *)mApp->handle();
    	int depth = 32;
    	int bytes_per_line = 0;
    	int bitmap_pad = 32;
    	XImage *img = XCreateImage(dis, CopyFromParent, depth, ZPixmap, 0, (char *)data, width, height, bitmap_pad, bytes_per_line);
    	XPutImage(dis, mHandle, mGC, img, 0, 0, 0, 0, width, height);
    	XFlush(dis);
    }

    void redraw()
    {
    	mWin->draw();
    }

private:
    RApp *mApp;
    RWin *mWin;
    int mScreen;
    Window mHandle;
    GC mGC;
    Colormap mColorMap;
    std::string mTitle;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};

}

#endif

#endif
