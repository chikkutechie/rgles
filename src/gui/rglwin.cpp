
#include "GUI/rglwin.h"

#include <string>

#if defined(_WIN32)
#include "rwin32win.h"
#else
#include "rx11win.h"
#endif

namespace rtv
{

RGLWin::RGLWin()
{}

RGLWin::~RGLWin()
{
	eglDestroyContext(mDisplay, mContext);
	eglDestroySurface(mDisplay, mSurface);
}

bool RGLWin::create()
{
	if (RWin::create())
	{
		mDisplay = eglGetDisplay(0);

		if (!eglInitialize(mDisplay, 0, 0))
		{
			std::cerr << "eglInitialize failed" << std::endl;
			return false;
		}

		if (!eglGetConfigs(mDisplay, &mConfig, 1, 0))
		{
			std::cerr << "eglGetConfigs failed" << std::endl;
			return false;
		}

		mContext = eglCreateContext(mDisplay, mConfig, EGL_NO_CONTEXT, 0);
		if (!mContext)
		{
			std::cerr << "eglCreateContext failed" << std::endl;
			return false;
		}

		mSurface = eglCreateWindowSurface(mDisplay, mConfig, (EGLNativeWindowType)this, 0);
		if (!mSurface)
		{
			std::cerr << "eglCreateWindowSurface failed" << std::endl;
			return false;
		}

		if (!eglMakeCurrent(mDisplay, mSurface, mSurface, mContext))
		{
			std::cerr << "eglMakeCurrent failed" << std::endl;
			return false;
		}
	}

	return true;
}

void RGLWin::flush()
{
	eglSwapBuffers(mDisplay, mSurface);
}


}

