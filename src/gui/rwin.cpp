
#include "GUI/rwin.h"

#include <string>

#if defined(_WIN32)
#include "rwin32win.h"
#else
#include "rx11win.h"
#endif

namespace rtv
{

RWin::RWin()
 : mImpl(0),
   mX(100),
   mY(100),
   mWidth(256),
   mHeight(256)
{
    mImpl = new RWinImpl(0, this);
}

RWin::~RWin()
{
    delete mImpl;
}

bool RWin::create()
{
    return mImpl->create();
}

void RWin::redraw()
{
	mImpl->redraw();
	mImpl->flush();
}

void RWin::draw()
{
}

void RWin::setApp(RApp *app)
{
    mApp = app;
    mImpl->setApp(app);
}

void RWin::show()
{
    mImpl->show();
}

void RWin::flush()
{
    mImpl->flush();
}

void RWin::setPosition(int x, int y)
{
    mImpl->setPosition(x, y);
}

void RWin::setSize(int w, int h)
{
    mImpl->setSize(w, h);
}

void RWin::blit(int x, int y, int width, int height, unsigned char * data)
{
	mImpl->blit( x, y, width, height, data );
}

void RWin::setTitle(std::string const & title)
{
	mTitle = title;
	mImpl->setTitle(title);
}

}

