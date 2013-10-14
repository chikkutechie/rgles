
#include "GLES/gl.h"

#include "rglinterface.h"

#ifdef __cplusplus
extern "C" {
#endif

GLAPI void GLAPIENTRY glLoadMatrix( const GLfloat m[16] )
{
    RGLInterface::instance()->loadMatrix( m );
}

GLAPI void GLAPIENTRY glScalef( GLfloat sx, GLfloat sy, GLfloat sz )
{
    RGLInterface::instance()->scale( sx, sy, sz );
}

GLAPI void GLAPIENTRY glTranslatef( GLfloat tx, GLfloat ty, GLfloat tz )
{
    RGLInterface::instance()->translate( tx, ty, tz );
}

GLAPI void GLAPIENTRY glRotatef( GLfloat angle, GLfloat ax, GLfloat ay,
                                    GLfloat az )
{
    RGLInterface::instance()->rotate( angle, ax, ay, az );
}

GLAPI void GLAPIENTRY glMatrixMode( GLenum mode )
{
    RGLInterface::instance()->matrixMode( mode );
}

GLAPI void GLAPIENTRY glLoadIdentity()
{
    RGLInterface::instance()->loadIdentity();
}

GLAPI void GLAPIENTRY glFrustumf( GLfloat left, GLfloat right,
                                     GLfloat bottom, GLfloat top,
                                     GLfloat zNear, GLfloat zFar )
{
    RGLInterface::instance()->frustum( left, right, bottom, top,
                                       zNear, zFar );
}

GLAPI void GLAPIENTRY glOrthof( GLfloat left, GLfloat right,
                                   GLfloat bottom, GLfloat top,
                                   GLfloat zNear, GLfloat zFar )
{
    RGLInterface::instance()->ortho( left, right, bottom, top,
                                     zNear, zFar );
}

GLAPI void GLAPIENTRY glFlush()
{
    RGLInterface::instance()->flush();
}

GLAPI void GLAPIENTRY glFinish()
{
    RGLInterface::instance()->finish();
}

GLAPI void GLAPIENTRY glReadPixels( GLint x, GLint y, GLsizei width,
                                       GLsizei height, GLenum format, GLenum type, GLvoid *pixels )
{
    RGLInterface::instance()->readPixels( x, y, width, height, format, type,
                                          pixels );
}

GLAPI void GLAPIENTRY glNormalPointer (GLenum type, GLsizei stride,
        const GLvoid *pointer)
{
    RGLInterface::instance()->normalPointer( type, stride, pointer );
}

GLAPI void GLAPIENTRY glColorPointer( GLint size, GLenum type,
        GLsizei stride,
        const GLvoid *pointer )
{
    RGLInterface::instance()->colorPointer( size, type, stride, pointer );
}

GLAPI void GLAPIENTRY glVertexPointer( GLint size, GLenum type,
        GLsizei stride, const GLvoid *pointer )
{
    RGLInterface::instance()->vertexPointer( size, type, stride, pointer );
}

GLAPI void GLAPIENTRY glDrawArrays( GLenum mode, GLint first,
                                       GLsizei count )
{
    RGLInterface::instance()->drawArrays( mode, first, count );
}

GLAPI void GLAPIENTRY glClearColor( GLclampf r, GLclampf g,
                                       GLclampf b, GLclampf a )
{
    RGLInterface::instance()->clearColor( r, g, b, a );
}

GLAPI void GLAPIENTRY glClear( GLbitfield mask )
{
    RGLInterface::instance()->clear( mask );
}

GLAPI void GLAPIENTRY glColor4ub( GLubyte r, GLubyte g, GLubyte b,
                                     GLubyte a )
{
    RGLInterface::instance()->color( ( GLfloat )r / 255.0f,
                                     ( GLfloat )g / 255.0f,
                                     ( GLfloat )b / 255.0f,
                                     ( GLfloat )a / 255.0f );
}

GLAPI void GLAPIENTRY glColor4f( GLfloat r, GLfloat g, GLfloat b,
                                    GLfloat a )
{
    RGLInterface::instance()->color( r, g, b, a );
}

GLAPI void GLAPIENTRY glColor4fv( GLfloat *v )
{
    RGLInterface::instance()->color( v[0], v[1], v[2], v[3] );
}

GLAPI void GLAPIENTRY glViewport( int x, int y, int width, int height )
{
    RGLInterface::instance()->viewport( x, y, width, height );
}

GLAPI GLenum GLAPIENTRY glGetError()
{
    return RGLInterface::instance()->getError();
}

GLAPI void GLAPIENTRY glEnable( GLenum cap )
{
    RGLInterface::instance()->enable( cap );
}

GLAPI void GLAPIENTRY glDisable( GLenum cap )
{
    RGLInterface::instance()->disable( cap );
}

GLAPI void GLAPIENTRY glEnableClientState( GLenum cap )
{
    RGLInterface::instance()->enable( cap );
}

GLAPI void GLAPIENTRY glDisableClientState( GLenum cap )
{
    RGLInterface::instance()->disable( cap );
}

GLAPI void GLAPIENTRY glDepthFunc( GLenum func )
{
    RGLInterface::instance()->depthFunc( func );
}

GLAPI void GLAPIENTRY glNormal3f ( GLfloat nx, GLfloat ny, GLfloat nz )
{
    RGLInterface::instance()->normal( nx, ny, nz );
}

GLAPI void GLAPIENTRY glNormal3fv ( const GLfloat *v )
{
    RGLInterface::instance()->normal( v[0], v[0], v[0] );
}

GLAPI void GLAPIENTRY glLightf (GLenum light, GLenum pname, GLfloat param)
{
    RGLInterface::instance()->light( light, pname, &param);
}

GLAPI void GLAPIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params)
{
    RGLInterface::instance()->light( light, pname, params);
}

GLAPI void GLAPIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param)
{
}

GLAPI void GLAPIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params)
{
}

/* textures */
GLAPI void GLAPIENTRY glGenTextures (GLsizei n, GLuint *textures)
{
}

GLAPI void GLAPIENTRY glDeleteTextures (GLsizei n, const GLuint *textures)
{
}

GLAPI void GLAPIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride,
								           const GLvoid *pointer)
{
}

GLAPI void GLAPIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param)
{
}

GLAPI void GLAPIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params)
{
}

GLAPI void GLAPIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat,
									  GLsizei width, GLsizei height, GLint border,
									  GLenum format, GLenum type, const GLvoid *pixels)
{
}

GLAPI void GLAPIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
}

GLAPI void GLAPIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
}

GLAPI void GLAPIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset,
										 GLint yoffset, GLsizei width, GLsizei height,
										 GLenum format, GLenum type, const GLvoid *pixels)
{
}


#ifdef __cplusplus
}
#endif

