
#ifndef RGUIUTILS_H
#define RGUIUTILS_H

namespace rtv
{

template <typename T>
class RSize
{
public:
    RSize( T w = 0, T h = 0 )
        : mW( w ),
          mH( h )
    {}

    void set( T w = 0, T h = 0 )
    {
        mW = w;
        mH = h;
    }

    T width() const
    {
        return mW;
    }

    T height() const
    {
        return mH;
    }

private:
    T mW;
    T mH;
};

typedef RSize<float> RSizef;
typedef RSize<int> RSizei;

template <typename T>
class RPosition
{
public:
    RPosition( T v1 = 0, T v2 = 0 )
        : mX( v1 ),
          mY( v2 )
    {}

    void set( T x = 0, T y = 0 )
    {
        mX = x;
        mY = y;
    }

    T x() const
    {
        return mX;
    }

    T y() const
    {
        return mY;
    }

private:
    T mX;
    T mY;
};

typedef RPosition<float> RPositionf;
typedef RPosition<int> RPositioni;

}

#endif
