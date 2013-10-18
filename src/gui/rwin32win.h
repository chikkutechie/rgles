
#ifndef RWIN32WIN_H
#define RWIN32WIN_H

#if defined(_WIN32)

#include <Windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#include <string>

#include "GUI/rapp.h"
#include "GUI/rwin.h"

namespace rtv
{
class RWinImpl
{
public:
    RWinImpl(RApp *app, RWin * win)
        : mApp(app),
          mWin(win),
          mHandle(0),
          mTitle("App"),
          mX(100),
          mY(100),
          mWidth(256),
          mHeight(256)
    {}

    void setApp(RApp *app) {
        mApp = app;
    }

    void setWin(RWin *w) {
        mWin = w;
    }

    virtual bool create() {
        if (!mHandle) {
            WNDCLASS wc;
            ATOM atom;
            DWORD flags   = 0;
            DWORD exFlags = 0;

            atom = GetClassInfo((HINSTANCE)mApp->handle(), TEXT("RAPPFW"), &wc);
            if (atom != 0) {
                flags = WS_OVERLAPPEDWINDOW;

                mHandle = CreateWindow(TEXT("RAPPFW"),
                                       mTitle.c_str(),
                                       flags,
                                       mX, mY,
                                       mWidth, mHeight,
                                       0,
                                       (HMENU) NULL,
                                       (HINSTANCE)mApp->handle(),
                                       0);
                if (mHandle == 0) {
                    MessageBox(0, TEXT("Window Creation Failed"),
                               TEXT("Error"),
                               MB_ICONEXCLAMATION | MB_OK);
                } else {
                    show();
                    mWin->onCreate();
                }
            }

        }

        return (mHandle != 0);
    }

    virtual void show() {
        if (mHandle) {
            ShowWindow(mHandle, SW_SHOW);
            UpdateWindow(mHandle);
            ShowCursor(TRUE);
        }
    }

    virtual void hide() {
        if (mHandle) {
            ShowWindow(mHandle, SW_HIDE);
            UpdateWindow(mHandle);
        }
    }

    void flush()
    {}

    std::string title() const {
        return mTitle;
    }

    RSizei size() const {
        return RSizei(mWidth, mHeight);
    }

    RPositioni position() const {
        return RPositioni(mX, mY);
    }

    void setPosition(int x, int y) {
        mX = x;
        mY = y;
        if (mHandle) {
            SetWindowPos(mHandle, 0, mX, mY,
                         mWidth, mHeight,
                         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    void setSize(int w, int h) {
        mWidth = w;
        mHeight = h;
        if (mHandle) {
            SetWindowPos(mHandle, 0,
                         mX, mY, w, h,
                         SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    void redraw() {
        if (mHandle) {
            InvalidateRect(mHandle, 0, FALSE);
        }
    }

    void blit(int dx, int dy, int width, int height, unsigned char * data) {
        if (mHandle) {
            HDC hDC = GetDC(0);
            HDC cDC = CreateCompatibleDC(hDC);
            HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);

            BITMAPINFO info;

            ZeroMemory(&info, sizeof(info));

            info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

            info.bmiHeader.biPlanes = 1;
            info.bmiHeader.biBitCount = 32;
            info.bmiHeader.biCompression = 0;
            info.bmiHeader.biHeight = height;
            info.bmiHeader.biWidth = width;
            info.bmiHeader.biSizeImage = width * height * 4;
            info.bmiHeader.biClrUsed = 256;
            SelectObject(cDC, hBmp);
            SetDIBits(cDC, hBmp, 0, height, data, &info, DIB_RGB_COLORS);

            HDC whdc;

            whdc = GetDC(mHandle);
            BitBlt(whdc, 0, 0, width, height, cDC, 0, 0, SRCCOPY);
            ReleaseDC(mHandle, whdc);

            DeleteBitmap(hBmp);

            DeleteDC(cDC);

            ReleaseDC(0, hDC);
        }
    }

    void setTitle(std::string const & title) {
        mTitle = title;
        if (mHandle) {
            SetWindowText(mHandle, title.c_str());
        }
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
