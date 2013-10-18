
#ifndef RGLWIN_H
#define RGLWIN_H

#include <string>

#include "GUI/rwin.h"
#include "EGL/egl.h"

namespace rtv
{

class RGLWin: public RWin
{
public:
    RGLWin();
    virtual ~RGLWin();

    virtual bool create();

    virtual void flush();

protected:
    EGLDisplay mDisplay;
    EGLConfig mConfig;
    EGLContext mContext;
    EGLSurface mSurface;
};

}

#endif

