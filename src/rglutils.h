
#ifndef RGLUTILS_H
#define RGLUTILS_H

#include <math.h>
#include <limits>

#include "GLES/gl.h"

#define GL_PI 3.141592653589f

template <typename T>
inline T clamp( T v, T min = 0, T max = 1 )
{
    if ( v < min )
    {
        v = min;
    }

    if ( v > max )
    {
        v = max;
    }

    return v;
}

template <typename T>
class RGLVector
{
public:
    RGLVector( T v1 = 0, T v2 = 0, T v3 = 0, T v4 = 1 )
    {
        set( v1, v2, v3, v4 );
    }

    RGLVector( const T *v )
    {
        set( v );
    }

    void set( const T *v )
    {
        set( v[0], v[1], v[2], v[3] );
    }

    void set( T v1 = 0.0f, T v2 = 0.0f, T v3 = 0.0f, T v4 = 1.0f )
    {
        setX( v1 );
        setY( v2 );
        setZ( v3 );
        setW( v4 );
    }

    void reset()
    {
        set();
    }

    bool operator==( RGLVector const &o ) const
    {
        return x() == o.x() &&
               y() == o.y() &&
               z() == o.z() &&
               w() == o.z();
    }

    bool operator!=( RGLVector const &o ) const
    {
        return !( *this == o );
    }

    RGLVector operator+( RGLVector const &o ) const
    {
        RGLVector v;
        v.setX( x() + o.x() );
        v.setY( y() + o.y() );
        v.setZ( z() + o.z() );
        v.setW( w() + o.w() );
        return v;
    }

    RGLVector& operator+=( RGLVector const &o )
    {
        setX( x() + o.x() );
        setY( y() + o.y() );
        setZ( z() + o.z() );
        setW( w() + o.w() );
        return *this;
    }

    RGLVector operator-( RGLVector const &o ) const
    {
        RGLVector v;
        v.setX( x() - o.x() );
        v.setY( y() - o.y() );
        v.setZ( z() - o.z() );
        v.setW( w() - o.w() );
        return v;
    }

    RGLVector& operator-=( RGLVector const &o )
    {
        setX( x() - o.x() );
        setY( y() - o.y() );
        setZ( z() - o.z() );
        setW( w() - o.w() );
        return *this;
    }

    RGLVector operator*( RGLVector const &o ) const
    {
        RGLVector v;
        v.setX( x() * o.x() );
        v.setY( y() * o.y() );
        v.setZ( z() * o.z() );
        v.setW( w() * o.w() );
        return v;
    }

    RGLVector& operator*=( RGLVector const &o )
    {
        setX( x() * o.x() );
        setY( y() * o.y() );
        setZ( z() * o.z() );
        setW( w() * o.w() );

        return *this;
    }

    RGLVector operator*( T s ) const
    {
        RGLVector v;
        v.setX( x() * s );
        v.setY( y() * s );
        v.setZ( z() * s );
        v.setW( w() * s );
        return v;
    }

    T &operator[]( GLint index )
    {
        return mData[index];
    }

    const T &operator[]( GLint index ) const
    {
        return mData[index];
    }

    void setX( T v )
    {
        mData[0] = v;
    }

    void setY( T v )
    {
        mData[1] = v;
    }

    void setZ( T v )
    {
        mData[2] = v;
    }

    void setW( T v )
    {
        mData[3] = v;
    }

    void setR( T v )
    {
        setX( v );
    }

    void setG( T v )
    {
        setY( v );
    }

    void setB( T v )
    {
        setZ( v );
    }

    void setA( T v )
    {
        setW( v );
    }

    T x() const
    {
        return mData[0];
    }

    T y() const
    {
        return mData[1];
    }

    T z() const
    {
        return mData[2];
    }

    T w() const
    {
        return mData[3];
    }

    T r() const
    {
        return x();
    }

    T g() const
    {
        return y();
    }

    T b() const
    {
        return z();
    }

    T a() const
    {
        return w();
    }

    const T *data() const
    {
        return mData;
    }

    T length() const
    {
        return sqrt( x() * x() + y() * y() + z() * z() );
    }

    RGLVector toUnit() const
    {
        T l = length();

        if ( l == 0.0f )
        {
            l = 1.0f;
        }

        return RGLVector( x() / l, y() / l, z() / l );
    }

    static RGLVector normal( RGLVector const &v1, RGLVector const &v2,
                             RGLVector const &v3 )
    {
        RGLVector vect1 = v1 - v2;
        RGLVector vect2 = v3 - v2;
        RGLVector n;

        n.setX( vect1.y()*vect2.z() - vect1.z()*vect2.y() );
        n.setY( vect1.z()*vect2.x() - vect1.x()*vect2.z() );
        n.setZ( vect1.x()*vect2.y() - vect1.y()*vect2.x() );

        return n.toUnit();
    }

    RGLVector cross( RGLVector const &oth ) const
    {
        RGLVector r;

        r.setX( ( y() * oth.z() ) - ( z() * oth.y() ) );
        r.setY( ( z() * oth.x() ) - ( x() * oth.z() ) );
        r.setZ( ( x() * oth.y() ) - ( y() * oth.x() ) );

        return r;
    }

    GLfloat dot( RGLVector const &oth ) const
    {
        GLfloat r;

        r = x() * oth.x() + y() * oth.y() + z() * oth.z();

        return r;
    }

    void clampValues(T const &v1=0, T const &v2=1)
    {
        mData[0] = clamp(mData[0], v1, v2);
        mData[1] = clamp(mData[1], v1, v2);
        mData[2] = clamp(mData[2], v1, v2);
        mData[3] = clamp(mData[3], v1, v2);
    }

private:
    T mData[4];
};

template <typename T>
class RGLVector2D
{
public:
    RGLVector2D( T v1 = 0, T v2 = 0 )
        : mX( v1 ),
          mY( v2 )
    {}

    bool operator==( RGLVector2D<T> const &oth ) const
    {
        if ( x() == oth.x() &&
             y() == oth.y() )
        {
            return true;
        }

        return false;
    }

    T x() const
    {
        return mX;
    }

    T y() const
    {
        return mY;
    }

    T width() const
    {
        return mX;
    }

    T height() const
    {
        return mY;
    }

private:
    T mX;
    T mY;
};

typedef RGLVector<GLfloat> RGLVectorf;
typedef RGLVector<GLubyte> RGLVectorub;

typedef RGLVector<GLfloat> RGLColorf;
typedef RGLVector<GLubyte> RGLColorub;

typedef RGLVector2D<GLfloat> RGLVector2Df;
typedef RGLVector2D<GLint>   RGLVector2Di;

inline GLfloat lineLength( RGLVectorf const &p1, RGLVectorf const &p2 )
{
    return sqrtf( ( p2.x() - p1.x() ) * ( p2.x() - p1.x() ) +
                  ( p2.y() - p1.y() ) *
                  ( p2.y() - p1.y() ) );
}

inline GLfloat interpolate( GLfloat t, GLfloat start, GLfloat end )
{
    if ( t < 0.0f )
    {
        t = 0.0f;
    }

    if ( t > 1.0f )
    {
        t = 1.0f;
    }

    return ( start * ( 1.0f - t ) + t * end );
}

inline bool rglFuncEqual( const GLfloat &v1, const GLfloat &v2 )
{
    return fabsf( v1 - v2 ) < std::numeric_limits<GLfloat>().epsilon();
}

inline bool rglFuncLess( const GLfloat &v1, const GLfloat &v2 )
{
    return !rglFuncEqual( v1, v2 ) && ( v1 < v2 );
}

template <typename T>
inline bool rglFuncLess( const T &v1, const T &v2 )
{
    return v1 < v2;
}

template <typename T>
inline bool rglFuncEqual( const T &v1, const T &v2 )
{
    return !rglFuncLess( v1, v2 ) && !rglFuncLess( v2, v1 );
}

template <typename T>
inline bool rglFuncLEqual( const T &v1, const T &v2 )
{
    return rglFuncLess( v1, v2 ) || rglFuncEqual( v1, v2 );
}

template <typename T>
inline bool rglFuncGreater( const T &v1, const T &v2 )
{
    return !rglFuncLess( v1, v2 ) && !rglFuncEqual( v1, v2 );
}

template <typename T>
inline bool rglFuncNotEqual( const T &v1, const T &v2 )
{
    return !rglFuncLEqual( v1, v2 );
}

template <typename T>
inline bool rglFuncGEqual( const T &v1, const T &v2 )
{
    return !rglFuncLess( v1, v2 );
}

template <typename T>
inline bool rglFuncAlways( const T &v1, const T &v2 )
{
    return true;
}

template <typename T>
inline bool rglFuncNever( const T &, const T & )
{
    return false;
}

template <typename T>
inline T rglMin( const T &v1, const T & v2)
{
    return v1 < v2 ? v1 : v2;
}

template <typename T>
inline T rglMax( const T &v1, const T & v2)
{
    return v1 > v2 ? v1 : v2;
}

inline GLint round(GLfloat v)
{
    GLint r = (GLint)v;
    GLfloat diff = v - (GLint)v; 
    if (diff > 0.5f)
    {
        r = (GLint)(v+1.0f);
    }
    return r;
}

#endif

