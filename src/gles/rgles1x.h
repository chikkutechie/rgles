
#ifndef RGLINTERFACE_H
#define RGLINTERFACE_H

#include "GLES/gl.h"

class RGles1x
{
protected:
    static RGles1x * mAPI;

public:
    class InitParam
    {
    public:
        InitParam()
            : mHasDepth(false),
              mHasStencil(false)
        {}

        int mWidth;
        int mHeight;
        bool mHasDepth;
        bool mHasStencil;
    };

public:
    static RGles1x *instance(const char *hint = 0) {
        return mAPI;
    }

public:
    virtual ~RGles1x()
    {}

    /* transformations */
    virtual void matrixMode(GLenum mode) = 0;
    virtual void loadMatrix(const GLfloat m[16]) = 0;
    virtual void scale(GLfloat sx, GLfloat sy, GLfloat sz) = 0;
    virtual void translate(GLfloat tx, GLfloat ty, GLfloat tz) = 0;
    virtual void rotate(GLfloat angle, GLfloat ax, GLfloat ay,
                        GLfloat az) = 0;
    virtual void loadIdentity() = 0;
    virtual void ortho(GLfloat left, GLfloat right,
                       GLfloat bottom, GLfloat top,
                       GLfloat zNear, GLfloat zFar) = 0;
    virtual void frustum(GLfloat left, GLfloat right,
                         GLfloat bottom, GLfloat top,
                         GLfloat zNear, GLfloat zFar) = 0;
    virtual void enable(GLenum cap) = 0;
    virtual void disable(GLenum cap) = 0;

    virtual void depthFunc(GLenum func) = 0;

    /* flush operations */
    virtual void flush() = 0;
    virtual void finish() = 0;

    /* retrieve color buffer */
    virtual void readPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels, bool originTopLeft = false) = 0;

    /* drawing operations */
    virtual void normalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer) = 0;
    virtual void colorPointer(GLint size, GLenum type,
                              GLsizei stride,
                              const GLvoid *pointer) = 0;
    virtual void vertexPointer(GLint size, GLenum type,
                               GLsizei stride, const GLvoid *pointer) = 0;
    virtual void drawArrays(GLenum mode, GLint first, GLsizei count) = 0;

    /* clear operations */
    virtual void clearColor(GLclampf r, GLclampf g, GLclampf b,
                            GLclampf a) = 0;

    virtual void clear(GLbitfield mask) = 0;

    /* color settings */
    virtual void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) = 0;

    virtual void viewport(int x, int y, int width, int height) = 0;

    /* light settings */
    virtual void light(GLenum light, GLenum pname, const GLfloat *params) = 0;
    virtual void material(GLenum face, GLenum pname, const GLfloat *params) = 0;
    virtual void normal(GLfloat nx, GLfloat ny, GLfloat nz) = 0;

    /* textures */
    virtual void bindTexture(GLenum target, GLuint texture) = 0;
    virtual void genTextures(GLsizei n, GLuint *textures) = 0;
    virtual void deleteTextures(GLsizei n, const GLuint *textures) = 0;

    virtual void texCoordPointer(GLint size, GLenum type, GLsizei stride,
                                 const GLvoid *pointer) = 0;
    virtual void texEnv(GLenum target, GLenum pname, const GLint *params) = 0;

    virtual void texImage2D(GLenum target, GLint level, GLint internalformat,
                            GLsizei width, GLsizei height, GLint border,
                            GLenum format, GLenum type, const GLvoid *pixels) = 0;
    virtual void texParameter(GLenum target, GLenum pname, const GLint *params) = 0;

    /* error value */
    virtual GLenum getError() = 0;

    virtual void initialize(InitParam const &param, void * state) = 0;
};

#endif
