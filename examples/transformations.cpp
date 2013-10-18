
#include <iostream>

#include "GUI/rapp.h"
#include "GUI/rglwin.h"
#include "GLES/gl.h"
#include "EGL/egl.h"

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
	int mWidth;
	int mHeight;
	GLfloat mAngle;

public:
	MyWindow()
	{
		mWidth = 256;
		mHeight = 256;
		mAngle = 0.0f;
	}


	void roateRect(GLfloat cx, GLfloat cy, GLint axis)
	{
		GLfloat vertices[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		const GLfloat rectWidth = mWidth/4.0f;
		const GLfloat rectHeight = mHeight/4.0f;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glTranslatef(cx-rectWidth/2.0f, cy-rectHeight/2.0f, 0);

		glTranslatef(rectWidth/2.0f, rectHeight/2.0f, 0);
		switch (axis)
		{
		case 0:
			glRotatef(mAngle, 0, 0, 1);
			break;

		case 1:
			glRotatef(mAngle, 0, 1, 0);
			break;

		case 2:
			glRotatef(mAngle, 1, 0, 0);
			break;

		case 3:
			glRotatef(mAngle, 1, 0, 0);
			glRotatef(mAngle, 0, 1, 0);
			glRotatef(mAngle, 0, 0, 1);
			break;
		}

		glTranslatef(-rectWidth/2.0f, -rectHeight/2.0f, 0);
		glScalef(rectWidth, rectHeight, 1.0f);

		glEnableClientState( GL_VERTEX_ARRAY );
		glVertexPointer( 3, GL_FLOAT, 0, vertices );
		glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
		glDisableClientState( GL_VERTEX_ARRAY );
	}

	void draw()
	{
		reshape(mWidth, mHeight);

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glColor4f( 1.0f, 0.0f, 1.0f, 1.0f );
		roateRect( mWidth/4.0f, mHeight/4.0f, 0 );

		glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
		roateRect( mWidth*3.0f/4.0f, mHeight/4.0f, 1 );

		glColor4f( 1.0f, 0.0f, 1.0f, 1.0f );
		roateRect( mWidth*3.0f/4.0f, mHeight*3.0f/4.0f, 2 );

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		roateRect( mWidth/4.0f, mHeight*3.0f/4.0f, 3 );

		mAngle += 15.0f;
		if (mAngle >= 360.0f)
		{
			mAngle = 0.0f;
		}

		GLenum error = glGetError();
		if ( error != GL_NO_ERROR )
		{
			std::cerr << std::hex << "Error Occured :" << error;
		}
	}

	void reshape( int w, int h )
	{
		mWidth = w;
		mHeight = h;

		glViewport( 0, 0, w, h );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrthof(0.0f, (GLfloat)w, 0.0f, (GLfloat)h, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

};

void MyTimer::run()
{
	mWindow->redraw();
	mWindow->flush();
    mApp->registerTimer(this);
}

int main( int argc, char **argv )
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

