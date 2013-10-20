
#include "GLES/gl.h"

#include "rgles1x.h"

#ifdef __cplusplus
extern "C" {
#endif

    GLAPI void GLAPIENTRY glLoadMatrix(const GLfloat m[16])
    {
        RGles1x::instance()->loadMatrix(m);
    }

    GLAPI void GLAPIENTRY glScalef(GLfloat sx, GLfloat sy, GLfloat sz)
    {
        RGles1x::instance()->scale(sx, sy, sz);
    }

    GLAPI void GLAPIENTRY glTranslatef(GLfloat tx, GLfloat ty, GLfloat tz)
    {
        RGles1x::instance()->translate(tx, ty, tz);
    }

    GLAPI void GLAPIENTRY glRotatef(GLfloat angle, GLfloat ax, GLfloat ay,
                                    GLfloat az)
    {
        RGles1x::instance()->rotate(angle, ax, ay, az);
    }

    GLAPI void GLAPIENTRY glMatrixMode(GLenum mode)
    {
        RGles1x::instance()->matrixMode(mode);
    }

    GLAPI void GLAPIENTRY glLoadIdentity()
    {
        RGles1x::instance()->loadIdentity();
    }

    GLAPI void GLAPIENTRY glFrustumf(GLfloat left, GLfloat right,
                                     GLfloat bottom, GLfloat top,
                                     GLfloat zNear, GLfloat zFar)
    {
        RGles1x::instance()->frustum(left, right, bottom, top,
                                          zNear, zFar);
    }

    GLAPI void GLAPIENTRY glOrthof(GLfloat left, GLfloat right,
                                   GLfloat bottom, GLfloat top,
                                   GLfloat zNear, GLfloat zFar)
    {
        RGles1x::instance()->ortho(left, right, bottom, top,
                                        zNear, zFar);
    }

    GLAPI void GLAPIENTRY glFlush()
    {
        RGles1x::instance()->flush();
    }

    GLAPI void GLAPIENTRY glFinish()
    {
        RGles1x::instance()->finish();
    }

    GLAPI void GLAPIENTRY glReadPixels(GLint x, GLint y, GLsizei width,
                                       GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
    {
        RGles1x::instance()->readPixels(x, y, width, height, format, type,
                                             pixels);
    }

    GLAPI void GLAPIENTRY glNormalPointer(GLenum type, GLsizei stride,
                                          const GLvoid *pointer)
    {
        RGles1x::instance()->normalPointer(type, stride, pointer);
    }

    GLAPI void GLAPIENTRY glColorPointer(GLint size, GLenum type,
                                         GLsizei stride,
                                         const GLvoid *pointer)
    {
        RGles1x::instance()->colorPointer(size, type, stride, pointer);
    }

    GLAPI void GLAPIENTRY glVertexPointer(GLint size, GLenum type,
                                          GLsizei stride, const GLvoid *pointer)
    {
        RGles1x::instance()->vertexPointer(size, type, stride, pointer);
    }

    GLAPI void GLAPIENTRY glDrawArrays(GLenum mode, GLint first,
                                       GLsizei count)
    {
        RGles1x::instance()->drawArrays(mode, first, count);
    }

    GLAPI void GLAPIENTRY glClearColor(GLclampf r, GLclampf g,
                                       GLclampf b, GLclampf a)
    {
        RGles1x::instance()->clearColor(r, g, b, a);
    }

    GLAPI void GLAPIENTRY glClear(GLbitfield mask)
    {
        RGles1x::instance()->clear(mask);
    }

    GLAPI void GLAPIENTRY glColor4ub(GLubyte r, GLubyte g, GLubyte b,
                                     GLubyte a)
    {
        RGles1x::instance()->color((GLfloat)r / 255.0f,
                                        (GLfloat)g / 255.0f,
                                        (GLfloat)b / 255.0f,
                                        (GLfloat)a / 255.0f);
    }

    GLAPI void GLAPIENTRY glColor4f(GLfloat r, GLfloat g, GLfloat b,
                                    GLfloat a)
    {
        RGles1x::instance()->color(r, g, b, a);
    }

    GLAPI void GLAPIENTRY glColor4fv(GLfloat *v)
    {
        RGles1x::instance()->color(v[0], v[1], v[2], v[3]);
    }

    GLAPI void GLAPIENTRY glViewport(int x, int y, int width, int height)
    {
        RGles1x::instance()->viewport(x, y, width, height);
    }

    GLAPI GLenum GLAPIENTRY glGetError()
    {
        return RGles1x::instance()->getError();
    }

    GLAPI void GLAPIENTRY glEnable(GLenum cap)
    {
        RGles1x::instance()->enable(cap);
    }

    GLAPI void GLAPIENTRY glDisable(GLenum cap)
    {
        RGles1x::instance()->disable(cap);
    }

    GLAPI void GLAPIENTRY glEnableClientState(GLenum cap)
    {
        RGles1x::instance()->enable(cap);
    }

    GLAPI void GLAPIENTRY glDisableClientState(GLenum cap)
    {
        RGles1x::instance()->disable(cap);
    }

    GLAPI void GLAPIENTRY glDepthFunc(GLenum func)
    {
        RGles1x::instance()->depthFunc(func);
    }

    GLAPI void GLAPIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
    {
        RGles1x::instance()->normal(nx, ny, nz);
    }

    GLAPI void GLAPIENTRY glNormal3fv(const GLfloat *v)
    {
        RGles1x::instance()->normal(v[0], v[0], v[0]);
    }

    GLAPI void GLAPIENTRY glLightf(GLenum light, GLenum pname, GLfloat param)
    {
        RGles1x::instance()->light(light, pname, &param);
    }

    GLAPI void GLAPIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params)
    {
        RGles1x::instance()->light(light, pname, params);
    }

    GLAPI void GLAPIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param)
    {
        RGles1x::instance()->material(face, pname, &param);
    }

    GLAPI void GLAPIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
    {
        RGles1x::instance()->material(face, pname, params);
    }

    /* textures */
    GLAPI void GLAPIENTRY glGenTextures(GLsizei n, GLuint *textures)
    {
        RGles1x::instance()->genTextures(n, textures);
    }

    GLAPI void GLAPIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
    {
        RGles1x::instance()->deleteTextures(n, textures);
    }

    GLAPI void GLAPIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride,
                                            const GLvoid *pointer)
    {
        RGles1x::instance()->texCoordPointer(size, type, stride, pointer);
    }

    GLAPI void GLAPIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param)
    {
        RGles1x::instance()->texEnv(target, pname, &param);
    }

    GLAPI void GLAPIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params)
    {
        RGles1x::instance()->texEnv(target, pname, params);
    }

    GLAPI void GLAPIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat,
                                       GLsizei width, GLsizei height, GLint border,
                                       GLenum format, GLenum type, const GLvoid *pixels)
    {
        RGles1x::instance()->texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    }

    GLAPI void GLAPIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
    {
        RGles1x::instance()->texParameter(target, pname, &param);
    }

    GLAPI void GLAPIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
    {
        RGles1x::instance()->texParameter(target, pname, params);
    }

    GLAPI void GLAPIENTRY glBindTexture(GLenum target, GLuint texture)
    {
        RGles1x::instance()->bindTexture(target, texture);
    }

#ifdef __cplusplus
}
#endif

