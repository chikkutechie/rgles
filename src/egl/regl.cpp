
#include "EGL/egl.h"
#include "rglinterfaceimplV_1_0.h"

#include "GUI/rwin.h"
#include "GUI/rapp.h"

#include <vector>

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) ( sizeof(a) / sizeof(a[0]) )
#endif

#define REGLASSERT(x) if (!(x)) { return; }
#define REGLASSERT_WE(x, e) if (!(x)) { eglState->mError = e; return; }

#define REGLASSERT_RET(x, r) if (!(x)) { return r; }
#define REGLASSERT_RET_WE(x, e, r) if (!(x)) { eglState->mError = e; return r; }

#ifdef __cplusplus
extern "C" {
#endif

namespace
{

class REGLSurfaceData
{
public:
    enum Type
    {
        EGLWindowSurface,
        EGLPBufferSurface,
        EGLPixmapSurface
    };
    
    Type mType;
    int mWidth;
    int mHeight;

    rtv::RWin * mWindow;
};

class REGLContext_ES_1
{
public:
	RGLInterfaceImplV_1_0 mAPI;
    RGLInterfaceImplV_1_0State mGLState;
};

class REGLConfig
{
public:
    EGLint mRedSize;
    EGLint mGreenSize;
    EGLint mBlueSize;
    EGLint mAlphaSize;
    EGLint mDepthSize;
};

typedef std::vector<REGLSurfaceData *> REGLSurfaceList;
typedef REGLSurfaceList::iterator REGLSurfaceListIter;
typedef REGLSurfaceList::const_iterator REGLSurfaceListConstIter;

typedef std::vector<REGLContext_ES_1 *> REGLContextList;
typedef REGLContextList::iterator REGLContextListIter;
typedef REGLContextList::const_iterator REGLContextListConstIter;


#define MAX_EGL_CONFIG  2

class REGLState
{
public:
	EGLSurface mCurrentSurface;
	EGLContext mCurrentContext;
    REGLSurfaceList mSurfaceList;
    REGLContextList mContextList;
    EGLint mError;
    REGLConfig mConfigs[MAX_EGL_CONFIG];
};

REGLState * eglState = 0;

}

REGLAPI EGLint REGLAPIENTRY eglGetError()
{
    EGLint error = eglState->mError;
    eglState->mError = EGL_SUCCESS;
    return error;
}

REGLAPI EGLDisplay REGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
    return EGL_DEFAULT_DISPLAY;
}

REGLAPI EGLBoolean REGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    REGLASSERT_RET(dpy == 0, EGL_FALSE);

    if (major)
    {
        *major = 1;
    }
    if (minor)
    {
        *minor = 0;
    }

    delete eglState;
    eglState = 0;
    eglState = new REGLState();

    eglState->mError = EGL_SUCCESS;
    eglState->mConfigs[0].mRedSize   = 8;
    eglState->mConfigs[0].mGreenSize = 8;
    eglState->mConfigs[0].mBlueSize  = 8;
    eglState->mConfigs[0].mAlphaSize = 8;
    eglState->mConfigs[0].mDepthSize = 8;

    eglState->mConfigs[1].mRedSize   = 8;
    eglState->mConfigs[1].mGreenSize = 8;
    eglState->mConfigs[1].mBlueSize  = 8;
    eglState->mConfigs[1].mAlphaSize = 8;
    eglState->mConfigs[1].mDepthSize = 0;

    return EGL_TRUE;
}

REGLAPI EGLBoolean REGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
    REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);

    delete eglState;
    eglState = 0;

    return EGL_TRUE;
}

REGLAPI const char * REGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name)
{
    const char *value = 0;

    switch (name)
    {
    case EGL_VENDOR:
        value = "rtv";
        break;

    case EGL_VERSION:
        value = "1.0";
        break;

    case EGL_EXTENSIONS:
        value = "";
        break;

    case EGL_CLIENT_APIS:
        value = "";
        break;
    }

    return value;
}

REGLAPI EGLBoolean REGLAPIENTRY eglGetConfigs( EGLDisplay dpy,
                                               EGLConfig *configs,
                                               EGLint config_size,
                                               EGLint *num_config )
{
    REGLASSERT_RET_WE(config_size >= 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);

    if ( num_config )
    {
        *num_config = ARRAYSIZE(eglState->mConfigs);
    }

    if ( configs )
    {
        for ( int i=0;
              i < config_size && i < (int)ARRAYSIZE(eglState->mConfigs);
              ++i )
        {
            configs[i] = i;
        }
    }

    return EGL_TRUE;
}

REGLAPI EGLBoolean REGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
                                                 EGLint attribute, EGLint *value)
{
    REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(config < MAX_EGL_CONFIG, EGL_BAD_ATTRIBUTE, EGL_FALSE);

    return EGL_FALSE;
}

REGLAPI EGLSurface REGLAPIENTRY eglCreateWindowSurface( EGLDisplay dpy, EGLConfig config,
                                                        EGLNativeWindowType win,
                                                        const EGLint *attrib_list)
{
	REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(config < MAX_EGL_CONFIG, EGL_BAD_ATTRIBUTE, EGL_NO_SURFACE);

    rtv::RWin * window = (rtv::RWin *)win;
    REGLSurfaceData * surface = new REGLSurfaceData();

    surface->mType = REGLSurfaceData::EGLWindowSurface;
    surface->mWidth = window->size().width();
    surface->mHeight = window->size().height();
    surface->mWindow = window;

    eglState->mSurfaceList.push_back(surface);


    return (eglState->mSurfaceList.size());
}

REGLAPI EGLContext REGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
                                               EGLContext share_context,
                                               const EGLint *attrib_list)
{
	REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(config < MAX_EGL_CONFIG, EGL_BAD_ATTRIBUTE, EGL_NO_CONTEXT);

    REGLContext_ES_1 * context = new REGLContext_ES_1();

    eglState->mContextList.push_back(context);

    return (eglState->mContextList.size());
}

REGLAPI EGLBoolean REGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
                                             EGLSurface read, EGLContext ctx)
{
	REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
	REGLASSERT_RET_WE(draw == read, EGL_BAD_ATTRIBUTE, EGL_FALSE);
	REGLASSERT_RET_WE(draw > 0 && draw-1 < eglState->mSurfaceList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);
	REGLASSERT_RET_WE(ctx > 0 && ctx-1 < eglState->mContextList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);

	REGLContext_ES_1 * context = eglState->mContextList[ctx-1];
	REGLSurfaceData * surface = eglState->mSurfaceList[draw-1];

	RGLInterface::InitParam param;
	param.mHasDepth = true;
	param.mWidth = surface->mWidth;
	param.mHeight = surface->mHeight;

	context->mAPI.initialize(param, (void *)&(context->mGLState));

	eglState->mCurrentSurface = draw;
	eglState->mCurrentContext = ctx;

    return EGL_TRUE;
}

REGLAPI EGLBoolean REGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(surface > 0 && surface-1 < eglState->mSurfaceList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(eglState->mCurrentContext-1 < eglState->mContextList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);

    REGLSurfaceData * eglSurface = eglState->mSurfaceList[surface - 1];
    REGLContext_ES_1 * context = eglState->mContextList[eglState->mCurrentContext - 1];

    REGLASSERT_RET_WE(eglSurface->mType == REGLSurfaceData::EGLWindowSurface, EGL_BAD_ATTRIBUTE, EGL_FALSE);

    GLubyte *buffer = new GLubyte[eglSurface->mWidth * eglSurface->mHeight * 4];

    bool inverted = true;

#ifdef _WIN32
    inverted = false;
#endif

	context->mAPI.readPixels( 0, 0, eglSurface->mWidth, eglSurface->mHeight,
                              GL_RGBA, GL_UNSIGNED_BYTE, buffer, inverted );

    eglSurface->mWindow->blit( 0, 0,
    						   eglSurface->mWidth, eglSurface->mHeight,
    						   buffer );

    delete [] buffer;

    return EGL_TRUE;
}

REGLAPI EGLBoolean REGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
	REGLASSERT_RET_WE(ctx > 0 && ctx-1 < eglState->mContextList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);

	delete eglState->mContextList[ctx - 1];

    eglState->mContextList.erase(eglState->mContextList.begin() + ctx - 1);

    return EGL_TRUE;
}

REGLAPI EGLBoolean REGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    REGLASSERT_RET_WE(dpy == 0, EGL_BAD_ATTRIBUTE, EGL_FALSE);
    REGLASSERT_RET_WE(surface > 0 && surface-1 < eglState->mSurfaceList.size(), EGL_BAD_ATTRIBUTE, EGL_FALSE);

    delete eglState->mSurfaceList[surface - 1];

    eglState->mSurfaceList.erase(eglState->mSurfaceList.begin() + surface - 1);

    return EGL_TRUE;
}

#ifdef __cplusplus
}
#endif
