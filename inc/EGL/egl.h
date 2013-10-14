
#ifndef REGL_H
#define REGL_H

#if defined(_WIN32)

# ifndef REGLAPIENTRY
#  if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__) || defined(__LCC__)
#   define REGLAPIENTRY    __stdcall
#  else
#   define REGLAPIENTRY
#  endif
# endif

# ifdef RGL_BUILDING_LIB
#  define REGLAPI __declspec(dllexport)
# else
#  ifdef _DLL
#   define REGLAPI __declspec(dllimport)
#  else
#   define REGLAPI extern
#  endif
# endif

#else
# define REGLAPIENTRY
# define REGLAPI extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef signed long long   EGLint64;
typedef unsigned long long EGLuint64;
typedef unsigned int       EGLuint32;

typedef EGLuint32          EGLNativeDisplayType;
typedef void *          EGLNativeWindowType;

/* EGL Types */
typedef int EGLint;
typedef EGLuint32 EGLuint;
typedef EGLuint EGLBoolean;
typedef EGLuint EGLenum;
typedef EGLuint EGLConfig;
typedef EGLuint EGLContext;
typedef EGLuint32 EGLDisplay;
typedef EGLuint EGLSurface;
typedef void *EGLClientBuffer;

/* EGL Versioning */
#define EGL_VERSION_1_0                 1

/* EGL aliases */
#define EGL_FALSE                       0
#define EGL_TRUE                        1

/* Out-of-band handle values */
#define EGL_DEFAULT_DISPLAY             ((EGLNativeDisplayType)0)
#define EGL_NO_CONTEXT                  ((EGLContext)0)
#define EGL_NO_DISPLAY                  ((EGLDisplay)0)
#define EGL_NO_SURFACE                  ((EGLSurface)0)

/* Out-of-band attribute value */
#define EGL_DONT_CARE                   ((EGLint)-1)

/* Errors / GetError return values */
#define EGL_SUCCESS                     0x3000
#define EGL_NOT_INITIALIZED             0x3001
#define EGL_BAD_ACCESS                  0x3002
#define EGL_BAD_ALLOC                   0x3003
#define EGL_BAD_ATTRIBUTE               0x3004
#define EGL_BAD_CONFIG                  0x3005
#define EGL_BAD_CONTEXT                 0x3006
#define EGL_BAD_CURRENT_SURFACE         0x3007
#define EGL_BAD_DISPLAY                 0x3008
#define EGL_BAD_MATCH                   0x3009
#define EGL_BAD_NATIVE_PIXMAP           0x300A
#define EGL_BAD_NATIVE_WINDOW           0x300B
#define EGL_BAD_PARAMETER               0x300C
#define EGL_BAD_SURFACE                 0x300D
#define EGL_CONTEXT_LOST                0x300E  /* EGL 1.1 - IMG_power_management */

/* Config attributes */
#define EGL_BUFFER_SIZE                 0x3020
#define EGL_ALPHA_SIZE                  0x3021
#define EGL_BLUE_SIZE                   0x3022
#define EGL_GREEN_SIZE                  0x3023
#define EGL_RED_SIZE                    0x3024
#define EGL_DEPTH_SIZE                  0x3025
#define EGL_STENCIL_SIZE                0x3026
#define EGL_CONFIG_CAVEAT               0x3027
#define EGL_CONFIG_ID                   0x3028
#define EGL_LEVEL                       0x3029
#define EGL_MAX_PBUFFER_HEIGHT          0x302A
#define EGL_MAX_PBUFFER_PIXELS          0x302B
#define EGL_MAX_PBUFFER_WIDTH           0x302C
#define EGL_NATIVE_RENDERABLE           0x302D
#define EGL_NATIVE_VISUAL_ID            0x302E
#define EGL_NATIVE_VISUAL_TYPE          0x302F
#define EGL_PRESERVED_RESOURCES         0x3030
#define EGL_SAMPLES                     0x3031
#define EGL_SAMPLE_BUFFERS              0x3032
#define EGL_SURFACE_TYPE                0x3033
#define EGL_TRANSPARENT_TYPE            0x3034
#define EGL_TRANSPARENT_BLUE_VALUE      0x3035
#define EGL_TRANSPARENT_GREEN_VALUE     0x3036
#define EGL_TRANSPARENT_RED_VALUE       0x3037
#define EGL_NONE                        0x3038  /* Attrib list terminator */
#define EGL_BIND_TO_TEXTURE_RGB         0x3039
#define EGL_BIND_TO_TEXTURE_RGBA        0x303A
#define EGL_MIN_SWAP_INTERVAL           0x303B
#define EGL_MAX_SWAP_INTERVAL           0x303C
#define EGL_LUMINANCE_SIZE              0x303D
#define EGL_ALPHA_MASK_SIZE             0x303E
#define EGL_COLOR_BUFFER_TYPE           0x303F
#define EGL_RENDERABLE_TYPE             0x3040
#define EGL_MATCH_NATIVE_PIXMAP         0x3041  /* Pseudo-attribute (not queryable) */
#define EGL_CONFORMANT                  0x3042
#define EGL_CONTEXT_DATA_SHARING_MODE   0x3043

/* Config attribute values */
#define EGL_SLOW_CONFIG                 0x3050  /* EGL_CONFIG_CAVEAT value */
#define EGL_NON_CONFORMANT_CONFIG       0x3051  /* EGL_CONFIG_CAVEAT value */
#define EGL_TRANSPARENT_RGB             0x3052  /* EGL_TRANSPARENT_TYPE value */
#define EGL_RGB_BUFFER                  0x308E  /* EGL_COLOR_BUFFER_TYPE value */
#define EGL_LUMINANCE_BUFFER            0x308F  /* EGL_COLOR_BUFFER_TYPE value */

/* More config attribute values, for EGL_TEXTURE_FORMAT */
#define EGL_NO_TEXTURE                  0x305C
#define EGL_TEXTURE_RGB                 0x305D
#define EGL_TEXTURE_RGBA                0x305E
#define EGL_TEXTURE_2D                  0x305F

/* Config attribute values for EGL_CONTEXT_DATA_SHARING_MODE */
#define EGL_IMPLICIT_DATA_SHARING       0x30AE
#define EGL_EXPLICIT_DATA_SHARING       0x30AF

/* Config attribute mask bits */
#define EGL_PBUFFER_BIT                 0x0001  /* EGL_SURFACE_TYPE mask bits */
#define EGL_PIXMAP_BIT                  0x0002  /* EGL_SURFACE_TYPE mask bits */
#define EGL_WINDOW_BIT                  0x0004  /* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_COLORSPACE_LINEAR_BIT    0x0020  /* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_ALPHA_FORMAT_PRE_BIT     0x0040  /* EGL_SURFACE_TYPE mask bits */
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200  /* EGL_SURFACE_TYPE mask bits */
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400  /* EGL_SURFACE_TYPE mask bits */

#define EGL_OPENGL_ES_BIT               0x0001  /* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENVG_BIT                  0x0002  /* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_ES2_BIT              0x0004  /* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_BIT                  0x0008  /* EGL_RENDERABLE_TYPE mask bits */


/* QueryString targets */
#define EGL_VENDOR                      0x3053
#define EGL_VERSION                     0x3054
#define EGL_EXTENSIONS                  0x3055
#define EGL_CLIENT_APIS                 0x308D

/* QuerySurface / CreatePbufferSurface targets */
#define EGL_HEIGHT                      0x3056
#define EGL_WIDTH                       0x3057
#define EGL_LARGEST_PBUFFER             0x3058
#define EGL_TEXTURE_FORMAT              0x3080
#define EGL_TEXTURE_TARGET              0x3081
#define EGL_MIPMAP_TEXTURE              0x3082
#define EGL_MIPMAP_LEVEL                0x3083
#define EGL_RENDER_BUFFER               0x3086
#define EGL_VG_COLORSPACE               0x3087
#define EGL_VG_ALPHA_FORMAT             0x3088
#define EGL_HORIZONTAL_RESOLUTION       0x3090
#define EGL_VERTICAL_RESOLUTION         0x3091
#define EGL_PIXEL_ASPECT_RATIO          0x3092
#define EGL_SWAP_BEHAVIOR               0x3093
#define EGL_MULTISAMPLE_RESOLVE         0x3099

/* EGL_RENDER_BUFFER values / BindTexImage / ReleaseTexImage buffer targets */
#define EGL_BACK_BUFFER                 0x3084
#define EGL_SINGLE_BUFFER               0x3085

/* OpenVG color spaces */
#define EGL_VG_COLORSPACE_sRGB          0x3089  /* EGL_VG_COLORSPACE value */
#define EGL_VG_COLORSPACE_LINEAR        0x308A  /* EGL_VG_COLORSPACE value */

/* OpenVG alpha formats */
#define EGL_VG_ALPHA_FORMAT_NONPRE      0x308B  /* EGL_VG_ALPHA_FORMAT value */
#define EGL_VG_ALPHA_FORMAT_PRE         0x308C  /* EGL_VG_ALPHA_FORMAT value */

/* Constant scale factor by which fractional display resolutions &
 * aspect ratio are scaled when queried as integer values.
 */
#define EGL_DISPLAY_SCALING             10000

/* Unknown display resolution/aspect ratio */
#define EGL_UNKNOWN                     ((EGLint)-1)

/* Back buffer swap behaviors */
#define EGL_BUFFER_PRESERVED            0x3094  /* EGL_SWAP_BEHAVIOR value */
#define EGL_BUFFER_DESTROYED            0x3095  /* EGL_SWAP_BEHAVIOR value */

/* CreatePbufferFromClientBuffer buffer types */
#define EGL_OPENVG_IMAGE                0x3096

/* QueryContext targets */
#define EGL_CONTEXT_CLIENT_TYPE         0x3097

/* CreateContext attributes */
#define EGL_CONTEXT_CLIENT_VERSION      0x3098

/* Multisample resolution behaviors */
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A  /* EGL_MULTISAMPLE_RESOLVE value */
#define EGL_MULTISAMPLE_RESOLVE_BOX     0x309B  /* EGL_MULTISAMPLE_RESOLVE value */

/* BindAPI/QueryAPI targets */
#define EGL_OPENGL_ES_API               0x30A0
#define EGL_OPENVG_API                  0x30A1
#define EGL_OPENGL_API                  0x30A2
#define EGL_OPENGL_SC_API               0x30A3

/* GetCurrentSurface targets */
#define EGL_DRAW                        0x3059
#define EGL_READ                        0x305A

/* WaitNative engines */
#define EGL_CORE_NATIVE_ENGINE          0x305B

/* EGL Functions */
REGLAPI EGLDisplay REGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id);
REGLAPI EGLBoolean REGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
REGLAPI EGLBoolean REGLAPIENTRY eglTerminate(EGLDisplay dpy);

REGLAPI const char * REGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name);

REGLAPI EGLBoolean REGLAPIENTRY eglGetConfigs(EGLDisplay dpy, EGLConfig *configs,
                                            EGLint config_size, EGLint *num_config);
REGLAPI EGLBoolean REGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config,
                                                 EGLint attribute, EGLint *value);

REGLAPI EGLSurface REGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
                                                     EGLNativeWindowType win,
                                                     const EGLint *attrib_list);

REGLAPI EGLContext REGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config,
                                               EGLContext share_context,
                                               const EGLint *attrib_list);
REGLAPI EGLBoolean REGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw,
                                             EGLSurface read, EGLContext ctx);

REGLAPI EGLBoolean REGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
REGLAPI EGLBoolean REGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface);

REGLAPI EGLBoolean REGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);

REGLAPI EGLint REGLAPIENTRY eglGetError();

#ifdef __cplusplus
}
#endif

#endif
