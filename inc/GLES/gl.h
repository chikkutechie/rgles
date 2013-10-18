
#ifndef GL_H
#define GL_H

#if defined(_WIN32)

# ifndef GLAPIENTRY
#  if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__) || defined(__LCC__)
#   define GLAPIENTRY    __stdcall
#  else
#   define GLAPIENTRY
#  endif
# endif

# ifdef GL_BUILDING_LIB
#  define GLAPI __declspec(dllexport)
# else
#  ifdef _DLL
#   define GLAPI __declspec(dllimport)
#  else
#   define GLAPI extern
#  endif
# endif

#else
# define GLAPIENTRY
# define GLAPI extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /* type declarations */
    typedef unsigned int GLenum;
    typedef unsigned char GLboolean;
    typedef unsigned int GLbitfield;
    typedef signed char GLbyte;
    typedef short GLshort;
    typedef int GLint;
    typedef int GLsizei;
    typedef unsigned char GLubyte;
    typedef unsigned short GLushort;
    typedef unsigned int GLuint;
    typedef float GLfloat;
    typedef float GLclampf;
    typedef double GLdouble;
    typedef double GLclampd;
    typedef void GLvoid;

    /* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

    /* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1

    /* primitives mode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

    /* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

    /* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C

    /* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701

    /* PixelFormat */
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

    /* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

#define GL_DEPTH_TEST                     0x0B71

#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_TEXTURE_COORD_ARRAY            0x8078

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

#define GL_LIGHTING                       0x0B50

    /* texture */
#define GL_TEXTURE_2D                     0x0DE1

    /* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

    /* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

    /* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

    /* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803

    /* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

    /* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
#define GL_REPLACE                        0x1E01
#define GL_BLEND                          0x0BE2

    /* face */
#define GL_FRONT_AND_BACK                 0x0408

    /* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

    /* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602

    /* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

#define GL_COLOR_MATERIAL                 0x0B57

    /* transformations */
    GLAPI void GLAPIENTRY glMatrixMode(GLenum mode);
    GLAPI void GLAPIENTRY glLoadIMatrix(const GLfloat m[16]);
    GLAPI void GLAPIENTRY glScalef(GLfloat sx, GLfloat sy, GLfloat sz);
    GLAPI void GLAPIENTRY glTranslatef(GLfloat tx, GLfloat ty,
                                       GLfloat tz);
    GLAPI void GLAPIENTRY glRotatef(GLfloat angle, GLfloat ax, GLfloat ay,
                                    GLfloat az);
    GLAPI void GLAPIENTRY glLoadIdentity();
    GLAPI void GLAPIENTRY glOrthof(GLfloat left, GLfloat right,
                                   GLfloat bottom, GLfloat top,
                                   GLfloat zNear, GLfloat zFar);
    GLAPI void GLAPIENTRY glFrustumf(GLfloat left, GLfloat right,
                                     GLfloat bottom, GLfloat top,
                                     GLfloat zNear, GLfloat zFar);

    /* enable and disable feature */
    GLAPI void GLAPIENTRY glEnable(GLenum cap);
    GLAPI void GLAPIENTRY glDisable(GLenum cap);
    GLAPI void GLAPIENTRY glEnableClientState(GLenum cap);
    GLAPI void GLAPIENTRY glDisableClientState(GLenum cap);

    GLAPI void GLAPIENTRY glDepthFunc(GLenum func);

    /* flush operations */
    GLAPI void GLAPIENTRY glFlush();
    GLAPI void GLAPIENTRY glFinish();

    /* retrieve color buffer */
    GLAPI void GLAPIENTRY glReadPixels(GLint x, GLint y,
                                       GLsizei width, GLsizei height,
                                       GLenum format, GLenum type, GLvoid *pixels);

    /* light operations */
    GLAPI void GLAPIENTRY glLightf(GLenum light, GLenum pname, GLfloat param);
    GLAPI void GLAPIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params);
    GLAPI void GLAPIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param);
    GLAPI void GLAPIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params);

    GLAPI void GLAPIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
    GLAPI void GLAPIENTRY glNormal3fv(const GLfloat *v);

    /* drawing operations */
    GLAPI void GLAPIENTRY glColorPointer(GLint size, GLenum type,
                                         GLsizei stride,
                                         const GLvoid *pointer);

    GLAPI void GLAPIENTRY glVertexPointer(GLint size, GLenum type,
                                          GLsizei stride,
                                          const GLvoid *pointer);
    GLAPI void GLAPIENTRY glNormalPointer(GLenum type, GLsizei stride,
                                          const GLvoid *pointer);
    GLAPI void GLAPIENTRY glDrawArrays(GLenum mode, GLint first,
                                       GLsizei count);

    /* textures */
    GLAPI void GLAPIENTRY glGenTextures(GLsizei n, GLuint *textures);
    GLAPI void GLAPIENTRY glDeleteTextures(GLsizei n, const GLuint *textures);
    GLAPI void GLAPIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                            const GLvoid *pointer);
    GLAPI void GLAPIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param);
    GLAPI void GLAPIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params);
    GLAPI void GLAPIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat,
                                       GLsizei width, GLsizei height, GLint border,
                                       GLenum format, GLenum type, const GLvoid *pixels);
    GLAPI void GLAPIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param);
    GLAPI void GLAPIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params);
    GLAPI void GLAPIENTRY glBindTexture(GLenum target, GLuint texture);

    /* clear operations */
    GLAPI void GLAPIENTRY glClearColor(GLclampf r, GLclampf g, GLclampf b,
                                       GLclampf a);

    GLAPI void GLAPIENTRY glClear(GLbitfield mask);

    /* color settings */
    GLAPI void GLAPIENTRY glColor4ub(GLubyte r, GLubyte g, GLubyte b,
                                     GLubyte a);
    GLAPI void GLAPIENTRY glColor4f(GLfloat r, GLfloat g, GLfloat b,
                                    GLfloat a);
    GLAPI void GLAPIENTRY glColor4fv(GLfloat *v);

    GLAPI void GLAPIENTRY glViewport(int x, int y, int width, int height);

    GLAPI GLenum GLAPIENTRY glGetError();

#ifdef __cplusplus
}
#endif

#endif
