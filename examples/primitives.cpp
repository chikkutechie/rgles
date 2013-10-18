#include <iostream>

#include "GUI/rapp.h"
#include "GUI/rglwin.h"
#include "GLES/gl.h"
#include "EGL/egl.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

class MyWindow: public rtv::RGLWin
{
public:
    virtual void draw() {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat point[] = {
            -0.75f, -0.75f
        };

        GLfloat line[] = {
            -0.5f, -0.75f,
            0.4f, -0.75f
        };

        GLfloat lineloop[] = {
            0.5f, -0.5f,
            0.75f, -0.5f,
            0.75f, -0.25f,
            0.5f, -0.25f
        };

        GLfloat linestrip[] = {
            -0.25f, -0.5f,
            0.25f, -0.5f,
            0.0f, -0.25f
        };

        GLfloat triangles[] = {
            -0.75f, -0.25f,
            -0.25f, -0.25f,
            -0.5f, 0.15f
        };

        GLfloat trianglefan[] = {
            -0.5f, 0.5f,
            -0.25f, 0.5f,
            -0.25f, 0.75f,
            -0.5f, 0.75f,
            -0.75f, 0.5f,
            -0.5f, 0.25f,
            -0.25f, 0.5f
        };

        GLfloat trianglestrip[] = {
            0.5f, 0.25f,
            0.5f, 0.75f,
            0.75f, 0.5f,
            0.75f, 0.75f
        };

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor4ub(255, 0, 0, 255);
        glVertexPointer(2, GL_FLOAT, 0, point);
        glDrawArrays(GL_POINTS, 0, ARRAYSIZE(point) / 2);

        glColor4ub(0, 255, 0, 255);
        glVertexPointer(2, GL_FLOAT, 0, line);
        glDrawArrays(GL_LINES, 0, ARRAYSIZE(line) / 2);

        glColor4ub(0, 0, 255, 255);
        glVertexPointer(2, GL_FLOAT, 0, lineloop);
        glDrawArrays(GL_LINE_LOOP, 0, ARRAYSIZE(lineloop) / 2);

        glColor4ub(255, 255, 0, 255);
        glVertexPointer(2, GL_FLOAT, 0, linestrip);
        glDrawArrays(GL_LINE_STRIP, 0, ARRAYSIZE(linestrip) / 2);

        glColor4ub(255, 0, 255, 255);
        glVertexPointer(2, GL_FLOAT, 0, triangles);
        glDrawArrays(GL_TRIANGLES, 0, ARRAYSIZE(triangles) / 2);

        glColor4ub(0, 255, 255, 255);
        glVertexPointer(2, GL_FLOAT, 0, trianglefan);
        glDrawArrays(GL_TRIANGLE_FAN, 0, ARRAYSIZE(trianglefan) / 2);


        glColor4ub(255, 255, 255, 255);
        glVertexPointer(2, GL_FLOAT, 0, trianglestrip);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, ARRAYSIZE(trianglestrip) / 2);

        glDisableClientState(GL_VERTEX_ARRAY);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << std::hex << "Error Occured :" << error;
        }
    }

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
