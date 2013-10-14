
#ifndef RWIN32APP_H
#define RWIN32APP_H

#if defined(_WIN32)

#include <Windows.h>
#include <windowsx.h>
#include <mmsystem.h>

namespace rtv
{

LRESULT CALLBACK appfwWndProc( HWND hwnd, UINT msg,
                               WPARAM wParam, LPARAM lParam )
{
    LRESULT result = 0;

    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        result = DefWindowProc(hwnd, msg, wParam ,lParam);
        break;
    }

    return result;
}

class RApp;

class RAppImpl
{
public:
    RAppImpl(RApp * app)
     : mApp(app)
    {}

    virtual ~RAppImpl()
    {}

    virtual bool init()
    {
        ATOM atom;

        mInstance = GetModuleHandle(0);
        atom = GetClassInfo( mInstance, TEXT("RAPPFW"), &mWNDClass );

        if( atom == 0 )
        {
            ZeroMemory( &mWNDClass, sizeof(mWNDClass) );

            mWNDClass.lpfnWndProc    = appfwWndProc;
            mWNDClass.cbClsExtra     = 0;
            mWNDClass.cbWndExtra     = 0;
            mWNDClass.hInstance      = mInstance;
            mWNDClass.hIcon          = LoadIcon( 0, IDI_APPLICATION );
            mWNDClass.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
            if (!mWNDClass.hIcon)
            {
                mWNDClass.hIcon        = LoadIcon( NULL, IDI_APPLICATION );
            }

            mWNDClass.hCursor        = LoadCursor( NULL, IDC_ARROW );
            mWNDClass.hbrBackground  = NULL;
            mWNDClass.lpszMenuName   = NULL;
            mWNDClass.lpszClassName  = TEXT("RAPPFW");

            /* Register the window class */
            atom = RegisterClass( &mWNDClass );
            if (!atom)
            {
                MessageBox(0, (LPCWSTR)"Window Registeration Failed",
                          (LPCWSTR)"Error",
                          MB_ICONEXCLAMATION | MB_OK);
                return false;
            }
        }

        return true;
    }

    EventData readEvent()
    {
    	if (GetMessage(&mMessage, 0, 0, 0) > 0)
    	{
            TranslateMessage(&mMessage);
            DispatchMessage(&mMessage);
    	}

    	return EventData();
    }

    unsigned int handle()
    {
        return (unsigned int)mInstance;
    }

protected:
    RApp * mApp;
    HINSTANCE mInstance;
    WNDCLASS mWNDClass;
    MSG mMessage;
};

}

#endif

#endif
