
#ifndef RWIN_H
#define RWIN_H

#include <string>

#include "rguiutils.h"
#include "revent.h"

namespace rtv
{

class RWinImpl;
class RApp;

class RWin
{
public:
    RWin();
    virtual ~RWin();

    virtual bool create();

    virtual void redraw();
    virtual void draw();

    void setApp(RApp *app);
    virtual void show();
    virtual void flush();
    virtual void blit(int x, int y, int width, int height, unsigned char * data);

    void setPosition(int x, int y);
    void setSize(int w, int h);

    RSizei size() const;

    RPositioni position() const;

    virtual void onCreate()
    {}

    std::string title() const;
    void setTitle(std::string const & title);

protected:
    RWinImpl * mImpl;
    RApp *mApp;
};

}

#endif

