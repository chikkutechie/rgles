
#include <iostream>

#include "GUI/rwin.h"
#include "GUI/rapp.h"
#include "GLES/gl.h"
#include "EGL/egl.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

class MyWindow: public rtv::RWin
{
public:
    MyWindow()
    {}

    ~MyWindow() {
        eglDestroyContext(mDisplay, mContext);
        eglDestroySurface(mDisplay, mSurface);
        eglTerminate(mDisplay);
    }

    virtual void onCreate() {
        std::cout << "Setting up EGL" << std::endl;

        mDisplay = eglGetDisplay(0);

        if (!eglInitialize(mDisplay, 0, 0)) {
            std::cerr << "eglInitialize failed" << std::endl;
            return;
        }

        if (!eglGetConfigs(mDisplay, &mConfig, 1, 0)) {
            std::cerr << "eglGetConfigs failed" << std::endl;
            return;
        }

        mContext = eglCreateContext(mDisplay, mConfig, EGL_NO_CONTEXT, 0);
        if (!mContext) {
            std::cerr << "eglCreateContext failed" << std::endl;
            return;
        }

        mSurface = eglCreateWindowSurface(mDisplay, mConfig, (EGLNativeWindowType)this, 0);
        if (!mSurface) {
            std::cerr << "eglCreateWindowSurface failed" << std::endl;
            return;
        }

        if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext)) {
            std::cerr << "eglMakeCurrent failed" << std::endl;
            return;
        }
    }

    virtual void draw() {
        std::cout << "Drawing" << std::endl;

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::cout << "Drawn" << std::endl;
        std::cout << "Swapping" << std::endl;
        eglSwapBuffers(mDisplay, mSurface);
        std::cout << "Swapped" << std::endl;
    }

private:
    EGLDisplay mDisplay;
    EGLConfig mConfig;
    EGLContext mContext;
    EGLSurface mSurface;
};


int main(int argc, char **argv)
{
    rtv::RApp app;
    MyWindow win;

    app.init();

    app.setMainWindow(&win);

    app.exec();

    return 0;
}
