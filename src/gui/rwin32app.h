
#ifndef RWIN32APP_H
#define RWIN32APP_H

#if defined(_WIN32)

#include <Windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#include <iostream>
#include <queue>

namespace rtv
{

class RApp;

class RAppImpl
{
private:
    static std::queue<EventData> mEvenetQueue;

private:
    static void addEvent(const EventData & eve)
    {
        if (!mEvenetQueue.empty())
        {
            if (mEvenetQueue.front().mType != eve.mType)
            {
                mEvenetQueue.push(eve);
            }
        }
        else
        {
            mEvenetQueue.push(eve);
        }
    }

    static inline EventData retrieveEvent()
    {
        EventData eve;
        if (!mEvenetQueue.empty())
        {
            eve = mEvenetQueue.front();
            mEvenetQueue.pop();
        }
        return eve;
    }

    static LRESULT CALLBACK appfwWndProc( HWND hwnd, UINT msg,
                               WPARAM wParam, LPARAM lParam )
    {
        LRESULT result = 0;
        EventData data;
    	PAINTSTRUCT ps;
	    HDC hdc;

        switch (msg)
        {
        case WM_SIZE:
            data.mType = RAPPFWEventResize;
            data.mWidth = LOWORD(lParam);
            data.mHeight = HIWORD(lParam);
            addEvent(data);
            break;

        case WM_CLOSE:
            data.mType = RAPPFWEventExit;
            DestroyWindow(hwnd);
            addEvent(data);
            break;

        case WM_DESTROY:
            data.mType = RAPPFWEventExit;
            PostQuitMessage(WM_QUIT);
            addEvent(data);
            break;

        case WM_PAINT:
            data.mType = RAPPFWEventDraw;
            hdc = BeginPaint(hwnd, &ps);
    		EndPaint(hwnd, &ps);
            addEvent(data);
            break;

        default:
            result = DefWindowProc(hwnd, msg, wParam ,lParam);
            break;
        }

        return result;
    }

public:
    RAppImpl(RApp * app)
     : mApp(app),
       mAtom(0)
    {}

    virtual ~RAppImpl()
    {}

    virtual bool init()
    {
        if (mAtom == 0)
        {
            mInstance = GetModuleHandle(0);
            mAtom = GetClassInfo( mInstance, TEXT("RAPPFW"), &mWNDClass );

            if( mAtom == 0 )
            {
                ZeroMemory( &mWNDClass, sizeof(mWNDClass) );

                mWNDClass.lpfnWndProc    = appfwWndProc;
                mWNDClass.cbClsExtra     = 0;
                mWNDClass.cbWndExtra     = 0;
                mWNDClass.hInstance      = mInstance;
                mWNDClass.hIcon          = LoadIcon( 0, IDI_APPLICATION );
                mWNDClass.style          = CS_HREDRAW | CS_VREDRAW;
                mWNDClass.hCursor        = LoadCursor( NULL, IDC_ARROW );
                mWNDClass.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
                mWNDClass.lpszMenuName   = NULL;
                mWNDClass.lpszClassName  = TEXT("RAPPFW");

                /* Register the window class */
                mAtom = RegisterClass( &mWNDClass );
                if (!mAtom)
                {
                    MessageBox(0, TEXT("Window Registeration Failed"),
                                  TEXT("Error"),
                              MB_ICONEXCLAMATION | MB_OK);
                    return false;
                }
            }
        }

        return (mAtom != 0);
    }

    EventData readEvent()
    {
        if (mAtom != 0)
        {
            if (PeekMessage( &mMessage, NULL, 0, 0, PM_NOREMOVE ))
            {
    	        if (GetMessage(&mMessage, 0, 0, 0) > 0)
    	        {
                    TranslateMessage(&mMessage);
                    DispatchMessage(&mMessage);
    	        }
            }
        }
    	return retrieveEvent();
    }

    unsigned int handle()
    {
        return (unsigned int)mInstance;
    }

protected:
    RApp * mApp;
    ATOM mAtom;
    HINSTANCE mInstance;
    WNDCLASS mWNDClass;
    MSG mMessage;
};

std::queue<EventData> RAppImpl::mEvenetQueue;

}

#endif

#endif
