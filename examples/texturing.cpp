
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
    GLfloat mCubeRotationAngle;
    bool mInitialized;
    GLuint mTexture;

    std::vector<GLfloat> Vertices;
    std::vector<GLfloat> Normals;
    std::vector<GLfloat> TexCoords;
    std::vector<GLfloat> Colors;

    MyWindow() {
        mWidth = 256;
        mHeight = 256;
        mCubeRotationAngle = 10.0f;
        mInitialized = false;
    }

    void createShapes() {

        float v[] = {
                    -0.5, -0.5,
                    0.5, -0.5,
                    0.5, 0.5,
                    -0.5, 0.5
                    };

        float n[] = {
        			0.0, 0.0, 1.0,
        			0.0, 0.0, 1.0,
        			0.0, 0.0, 1.0,
        			0.0, 0.0, 1.0
                    };

        float c[] = {
        		0.0, 0.0, 1.0, 1.0,
        		0.0, 0.0, 1.0, 1.0,
        		0.0, 0.0, 1.0, 1.0,
        		0.0, 0.0, 1.0, 1.0
        		};

        float t[] = {
        			0.0f, 0.0f,
        			1.0f, 0.0f,
        			1.0f, 1.0f,
        			0.0f, 1.0f
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

        GLubyte texData[] = {
        		0xFF, 0x00, 0x00, 0xFF,
        		0x00, 0xFF, 0x00, 0xFF,
        		0x00, 0x00, 0xFF, 0xFF,
        		0xFF, 0x00, 0xFF, 0xFF
        };

        createShapes();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_COLOR_MATERIAL);

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &mTexture);

        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

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

    void drawShapes() {
        glRotatef(mCubeRotationAngle, 0, 0, 1);
        mCubeRotationAngle += 10;
        if (mCubeRotationAngle > 360.0f) {
            mCubeRotationAngle = 0.0f;
        }

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glColorPointer(4, GL_FLOAT, 0, &Colors[0]);
        glNormalPointer(GL_FLOAT, 0, &Normals[0]);
        glVertexPointer(2, GL_FLOAT, 0, &Vertices[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &TexCoords[0]);

        glDrawArrays(GL_TRIANGLE_FAN, 0, Vertices.size() / 2);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    }

    void draw() {
        if (!mInitialized) {
            init();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawShapes();

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

