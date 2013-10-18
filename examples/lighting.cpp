
#include <iostream>

#include "GUI/rapp.h"
#include "GUI/rglwin.h"
#include "GLES/gl.h"
#include "EGL/egl.h"

#include <math.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

static const int TimerDelay = 200;

class MyWindow;

class MyTimer: public rtv::RTimer
{
private:
    MyWindow *mWindow;
    rtv::RApp *mApp;

public:
    MyTimer(MyWindow *w, rtv::RApp *app)
        : mWindow(w),
          mApp(app)
    {}

    void run();
};

class MyWindow: public rtv::RGLWin
{
public:
    int mWidth;
    int mHeight;
    bool mRotateCube;
    GLfloat mCubeRotationAngle;
    bool mInitialized;

    std::vector<GLfloat> Vertices;
    std::vector<GLfloat> Normals;
    std::vector<GLfloat> TexCoords;
    std::vector<GLfloat> Colors;

    MyWindow() {
        mWidth = 256;
        mHeight = 256;
        mRotateCube = true;
        mCubeRotationAngle = 10.0f;
        mInitialized = false;
    }

    void createCube(float w, float h, float l) {
        float x2 = w / 2.0f;
        float y2 = h / 2.0f;
        float z2 = l / 2.0f;

        float v[] = { -x2, y2, z2, -x2, -y2, z2, x2, -y2, z2, x2, -y2, z2,
                      x2, y2, z2, -x2, y2, z2, x2, y2, z2, x2, -y2, z2, x2, -y2, -z2, x2, -y2, -z2,
                      x2, y2, -z2, x2, y2, z2, x2, y2, -z2, x2, -y2, -z2, -x2, -y2, -z2, -x2, -y2, -
                      z2, -x2, y2, -z2, x2, y2, -z2, -x2, y2, -z2, -x2, -y2, -z2, -x2, -y2, z2, -x2,
                      -y2, z2, -x2, y2, z2, -x2, y2, -z2, -x2, y2, -z2, -x2, y2, z2, x2, y2, z2, x2,
                      y2, z2, x2, y2, -z2, -x2, y2, -z2, -x2, -y2, z2, -x2, -y2, -z2, x2, -y2, -z2,
                      x2, -y2, -z2, x2, -y2, z2, -x2, -y2, z2
                    };

        float n[] = {0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                     1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                     1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
                     0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, -1.0, 0.0, 0.0,
                     -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                     0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                     1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                     -1.0, 0.0, 0.0, -1.0, 0.0
                    };
        float c[] = {0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0,
                     1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
                     1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0,
                     0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0,
                     0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0,
                     1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
                     1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
                     0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
                     0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
                     0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
                     0.0, 1.0, 0.0, 1.0
                    };

        float t[] = {1.0 - 1.0 / 4.0, 3.0 / 4.0, 1.0 - 1.0 / 4.0, 1.0 / 4.0, 1.0, 1.0 / 4.0, 1.0, 1.0 / 4.0, 1.0,
                     3.0 / 4.0, 1.0 - 1.0 / 4.0, 3.0 / 4.0, 0.0, 3.0 / 4.0, 0.0, 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0,
                     1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0, 3.0 / 4.0, 0.0, 3.0 / 4.0, 1.0 / 4.0, 3.0 / 4.0, 1.0 / 4.0,
                     1.0 / 4.0, 2.0 / 4.0, 1.0 / 4.0, 2.0 / 4.0, 1.0 / 4.0, 2.0 / 4.0, 3.0 / 4.0, 1.0 / 4.0,
                     3.0 / 4.0, 2.0 / 4.0, 3.0 / 4.0, 2.0 / 4.0, 1.0 / 4.0, 3.0 / 4.0, 1.0 / 4.0, 3.0 / 4.0,
                     1.0 / 4.0, 3.0 / 4.0, 3.0 / 4.0, 2.0 / 4.0, 3.0 / 4.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                     0.0, 1.0, 1.0
                    };

        Vertices.clear();
        Normals.clear();
        TexCoords.clear();
        Colors.clear();

        Vertices.insert(Vertices.begin(), v, v + sizeof(v) / sizeof(v[0]));
        Normals.insert(Normals.begin(), n, n + sizeof(n) / sizeof(n[0]));
        TexCoords.insert(TexCoords.begin(), t, t + sizeof(t) / sizeof(t[0]));
        Colors.insert(Colors.begin(), c, c + sizeof(c) / sizeof(c[0]));
    }

    void normalWithAngle(GLfloat angle, GLfloat &x, GLfloat &y, GLfloat &z) {
        x = cos(angle);
        y = 0.0f;
        z = sin(angle);
    }

    void init() {
        GLfloat mAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat mDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
        GLfloat mSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};

        GLfloat lAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat lDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat lSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat lPosition[] = {0.0f, 0.0f, 2.0f, 0.0f};

        createCube(1, 1, 1);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_COLOR_MATERIAL);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT0, GL_POSITION, lPosition);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lSpecular);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lSpecular);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mSpecular);
    }

    void drawCube() {
        glRotatef(mCubeRotationAngle, 1, 0, 0);
        glRotatef(mCubeRotationAngle, 0, 1, 0);
        glRotatef(mCubeRotationAngle, 0, 0, 1);

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glColorPointer(4, GL_FLOAT, 0, &Colors[0]);
        glNormalPointer(GL_FLOAT, 0, &Normals[0]);
        glVertexPointer(3, GL_FLOAT, 0, &Vertices[0]);

        glDrawArrays(GL_TRIANGLES, 0, Vertices.size() / 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        if (mRotateCube) {
            mCubeRotationAngle += 10.0f;
            if (mCubeRotationAngle >= 360.0f) {
                mCubeRotationAngle = 0.0f;
            }
        }
    }

    void draw() {
        if (!mInitialized) {
            init();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawCube();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << std::hex << "Error Occured :" << error;
        }
    }
};

void MyTimer::run()
{
    mWindow->redraw();
    mWindow->flush();
    mApp->registerTimer(this);
}

int main(int argc, char **argv)
{
    rtv::RApp app;
    MyWindow win;
    MyTimer timer(&win, &app);
    timer.setInterval(TimerDelay);

    app.registerTimer(&timer);

    app.init();

    app.setMainWindow(&win);

    app.exec();

    return 0;
}

