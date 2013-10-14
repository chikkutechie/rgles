
#include "rglmatrix.h"

void RGLMatrix::reset()
{
    mData[0][0] = 1.0f;
    mData[0][1] = 0.0f;
    mData[0][2] = 0.0f;
    mData[0][3] = 0.0f;
    mData[1][0] = 0.0f;
    mData[1][1] = 1.0f;
    mData[1][2] = 0.0f;
    mData[1][3] = 0.0f;
    mData[2][0] = 0.0f;
    mData[2][1] = 0.0f;
    mData[2][2] = 1.0f;
    mData[2][3] = 0.0f;
    mData[3][0] = 0.0f;
    mData[3][1] = 0.0f;
    mData[3][2] = 0.0f;
    mData[3][3] = 1.0f;
}

void RGLMatrix::load( const GLfloat m[4 * 4] )
{
    mData[0][0] = m[0];
    mData[0][1] = m[1];
    mData[0][2] = m[2];
    mData[0][3] = m[3];
    mData[1][0] = m[4];
    mData[1][1] = m[5];
    mData[1][2] = m[6];
    mData[1][3] = m[7];
    mData[2][0] = m[8];
    mData[2][1] = m[9];
    mData[2][2] = m[10];
    mData[2][3] = m[11];
    mData[3][0] = m[12];
    mData[3][1] = m[13];
    mData[3][2] = m[14];
    mData[3][3] = m[15];
}

RGLVectorf RGLMatrix::multiply( RGLVectorf const &p ) const
{
    RGLVectorf r;

    r.setX( p.x()*mData[0][0] + p.y()*mData[1][0] + p.z()*mData[2][0] + p.w()
            *mData[3][0] );
    r.setY( p.x()*mData[0][1] + p.y()*mData[1][1] + p.z()*mData[2][1] + p.w()
            *mData[3][1] );
    r.setZ( p.x()*mData[0][2] + p.y()*mData[1][2] + p.z()*mData[2][2] + p.w()
            *mData[3][2] );
    r.setW( p.x()*mData[0][3] + p.y()*mData[1][3] + p.z()*mData[2][3] + p.w()
            *mData[3][3] );

    return r;
}

RGLMatrix &RGLMatrix::multiply( RGLMatrix &r, RGLMatrix const &a,
                                const RGLMatrix &b )
{
    GLfloat d00, d01, d02, d03;
    GLfloat d10, d11, d12, d13;
    GLfloat d20, d21, d22, d23;
    GLfloat d30, d31, d32, d33;

    d00 = b.mData[0][0];
    d01 = b.mData[0][1];
    d02 = b.mData[0][2];
    d03 = b.mData[0][3];

    d10 = b.mData[1][0];
    d11 = b.mData[1][1];
    d12 = b.mData[1][2];
    d13 = b.mData[1][3];

    d20 = b.mData[2][0];
    d21 = b.mData[2][1];
    d22 = b.mData[2][2];
    d23 = b.mData[2][3];

    d30 = b.mData[3][0];
    d31 = b.mData[3][1];
    d32 = b.mData[3][2];
    d33 = b.mData[3][3];

    for ( GLint i = 0; i < 4; i++ )
    {
        r.mData[i][0] = a.mData[i][0] * d00 + a.mData[i][1] * d10
                        + a.mData[i][2] * d20 + a.mData[i][3] * d30;
        r.mData[i][1] = a.mData[i][0] * d01 + a.mData[i][1] * d11
                        + a.mData[i][2] * d21 + a.mData[i][3] * d31;
        r.mData[i][2] = a.mData[i][0] * d02 + a.mData[i][1] * d12
                        + a.mData[i][2] * d22 + a.mData[i][3] * d32;
        r.mData[i][3] = a.mData[i][0] * d03 + a.mData[i][1] * d13
                        + a.mData[i][2] * d23 + a.mData[i][3] * d33;
    }

    return r;
}

GLfloat RGLMatrix::determinant() const
{
    GLfloat v = mData[3][3] * det3x3( mData[0][0], mData[0][1], mData[0][2],
                                       mData[1][0], mData[1][1], mData[1][2],
                                       mData[2][0], mData[2][1], mData[2][2] );

    if ( mData[3][0] == 0.0 && mData[3][1] == 0.0 && mData[3][2] == 0.0 )
    {
        return v;
    }

    v = -mData[0][3] * det3x3( mData[1][0], mData[1][1], mData[1][2],
                               mData[2][0], mData[2][1], mData[2][2],
                               mData[3][0], mData[3][1], mData[3][2] )

        + mData[1][3] * det3x3( mData[0][0], mData[0][1], mData[0][2],
                                mData[2][0], mData[2][1], mData[2][2],
                                mData[3][0], mData[3][1], mData[3][2] )

        - mData[2][3] * det3x3( mData[0][0], mData[0][1], mData[0][2],
                                mData[1][0], mData[1][1], mData[1][2],
                                mData[3][0], mData[3][1], mData[3][2] )
        + v;

    return v;
}

RGLMatrix RGLMatrix::invertTranspose() const
{
    RGLMatrix inverse;

    GLfloat x00, x01, x02;
    GLfloat x10, x11, x12;
    GLfloat x20, x21, x22;
    GLfloat rcp;

    GLfloat x30, x31, x32;
    GLfloat y01, y02, y03, y12, y13, y23;
    GLfloat z02, z03, z12, z13, z22, z23, z32, z33;

    x00 = mData[0][0];
    x01 = mData[0][1];
    x10 = mData[1][0];
    x11 = mData[1][1];
    x20 = mData[2][0];
    x21 = mData[2][1];
    x30 = mData[3][0];
    x31 = mData[3][1];

    y01 = x00 * x11 - x10 * x01;
    y02 = x00 * x21 - x20 * x01;
    y03 = x00 * x31 - x30 * x01;
    y12 = x10 * x21 - x20 * x11;
    y13 = x10 * x31 - x30 * x11;
    y23 = x20 * x31 - x30 * x21;

    x02 = mData[0][2];
    x01 = mData[0][3];
    x12 = mData[1][2];
    x11 = mData[1][3];
    x22 = mData[2][2];
    x21 = mData[2][3];
    x32 = mData[3][2];
    x31 = mData[3][3];

    z33 = x02 * y12 - x12 * y02 + x22 * y01;
    z23 = x12 * y03 - x32 * y01 - x02 * y13;
    z13 = x02 * y23 - x22 * y03 + x32 * y02;
    z03 = x22 * y13 - x32 * y12 - x12 * y23;
    z32 = x11 * y02 - x21 * y01 - x01 * y12;
    z22 = x01 * y13 - x11 * y03 + x31 * y01;
    z12 = x21 * y03 - x31 * y02 - x01 * y23;
    z02 = x11 * y23 - x21 * y13 + x31 * y12;

    y01 = x02 * x11 - x12 * x01;
    y02 = x02 * x21 - x22 * x01;
    y03 = x02 * x31 - x32 * x01;
    y12 = x12 * x21 - x22 * x11;
    y13 = x12 * x31 - x32 * x11;
    y23 = x22 * x31 - x32 * x21;

    x00 = mData[0][0];
    x01 = mData[0][1];
    x10 = mData[1][0];
    x11 = mData[1][1];
    x20 = mData[2][0];
    x21 = mData[2][1];
    x30 = mData[3][0];
    x31 = mData[3][1];

    x32 = x11 * y02 - x21 * y01 - x01 * y12;
    x22 = x01 * y13 - x11 * y03 + x31 * y01;
    x12 = x21 * y03 - x31 * y02 - x01 * y23;
    x02 = x11 * y23 - x21 * y13 + x31 * y12;

    rcp = x30 * x32 + x20 * x22 + x10 * x12 + x00 * x02;

    if ( rcp == (float)0 )
    {
        return *this;
    }

    rcp = (float)1 / rcp;

    x31 = x00 * y12 - x10 * y02 + x20 * y01;
    x21 = x10 * y03 - x30 * y01 - x00 * y13;
    x11 = x00 * y23 - x20 * y03 + x30 * y02;
    x01 = x20 * y13 - x30 * y12 - x10 * y23;

    inverse.mData[0][0] = x02 * rcp;
    inverse.mData[0][1] = x01 * rcp;
    inverse.mData[1][0] = x12 * rcp;
    inverse.mData[0][2] = z02 * rcp;
    inverse.mData[2][0] = x22 * rcp;
    inverse.mData[0][3] = z03 * rcp;
    inverse.mData[3][0] = x32 * rcp;
    inverse.mData[1][1] = x11 * rcp;
    inverse.mData[1][2] = z12 * rcp;
    inverse.mData[2][1] = x21 * rcp;
    inverse.mData[1][3] = z13 * rcp;
    inverse.mData[3][1] = x31 * rcp;
    inverse.mData[2][2] = z22 * rcp;
    inverse.mData[2][3] = z23 * rcp;
    inverse.mData[3][2] = z32 * rcp;
    inverse.mData[3][3] = z33 * rcp;

    return inverse;
}

RGLMatrix RGLMatrix::transpose() const
{
    RGLMatrix r;

    r.mData[0][0] = mData[0][0];
    r.mData[0][1] = mData[1][0];
    r.mData[0][2] = mData[2][0];
    r.mData[0][3] = mData[3][0];
    r.mData[1][0] = mData[0][1];
    r.mData[1][1] = mData[1][1];
    r.mData[1][2] = mData[2][1];
    r.mData[1][3] = mData[3][1];
    r.mData[2][0] = mData[0][2];
    r.mData[2][1] = mData[1][2];
    r.mData[2][2] = mData[2][2];
    r.mData[2][3] = mData[3][2];
    r.mData[3][0] = mData[0][3];
    r.mData[3][1] = mData[1][3];
    r.mData[3][2] = mData[2][3];
    r.mData[3][3] = mData[3][3];

    return r;
}


