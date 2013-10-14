
#ifndef RWIN32WIN_H
#define RWIN32WIN_H

#if defined(_WIN32)

#include <Windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#include <string>

#include "rapp.h"
#include "rwin.h"

namespace rtv
{
class RWinImpl
{
public:
    RWinImpl(RApp *app, RWin * win)
     : mApp(app),
       mWin(win),
       mHandle(0),
       mTitle("RAPPFW"),
       mX(100),
       mY(100),
       mWidth(256),
       mHeight(256)
    {}

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
        if (!mHandle)
        {
            WNDCLASS wc;
            ATOM atom;
            DWORD flags   = 0;
            DWORD exFlags = 0;

            atom = GetClassInfo( (HINSTANCE)mApp->handle(), TEXT("RAPPFW"), &wc );
            if( atom != 0 )
            {
                flags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
                flags |= WS_OVERLAPPEDWINDOW;

                mHandle = CreateWindowEx( 0,
                            TEXT("RAPPFW"),
                            (LPCWSTR)mTitle.c_str(),
                            flags,
                            mX, mY,
                            mWidth, mHeight,
                            0,
                            (HMENU) NULL,
                            (HINSTANCE)mApp->handle(),
                            0);
                if (mHandle == 0)
                {
                    MessageBox(0, (LPCWSTR)"Window Creation Failed",
                          (LPCWSTR)"Error",
                          MB_ICONEXCLAMATION | MB_OK);
                }
            }
            
        }
        return (mHandle != 0);
    }

    virtual void show()
    {
        if (mHandle)
        {
            ShowWindow(mHandle, SW_SHOW);
            UpdateWindow(mHandle);
            ShowCursor( TRUE );
        }
    }

    void flush()
    {}

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

    void redraw()
    {

    }

protected:
    RWin *mWin;
    RApp *mApp;
    HWND mHandle;
    std::string mTitle;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};
}

#endif

#endif
