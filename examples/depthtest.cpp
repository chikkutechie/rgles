
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
    MyWindow() {
        setSize(128, 256);
        setTitle("depth test");
    }

    void draw() {
        GLfloat rectangle1[] = {
            -1.0f, -1.0f, 1.0f,
            0.25f, -1.0f, 1.0f,
            0.25f, 0.25f, 1.0f,
            -1.0f, 0.25f, 1.0f
        };
        GLfloat rectangle2[] = {
            -0.25f, -0.25f, 0.5f,
            1.0f, -0.25f, 0.5f,
            1.0f, 1.0f, 0.5f,
            -0.25f, 1.0f, 0.5f
        };

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        glVertexPointer(3, GL_FLOAT, 0, rectangle1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, ARRAYSIZE(rectangle1) / 3);

        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glVertexPointer(3, GL_FLOAT, 0, rectangle2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, ARRAYSIZE(rectangle2) / 3);

        glDisableClientState(GL_VERTEX_ARRAY);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error Occured : " << error << std::endl;
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
