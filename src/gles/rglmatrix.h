
#ifndef RGLMATRIX_H
#define RGLMATRIX_H

#include "rglutils.h"

class RGLMatrix
{
public:
    RGLMatrix() {
        reset();
    }

    void reset();

    void load(const GLfloat d[4 * 4]);

    RGLMatrix multiply(const RGLMatrix &matrix2) const {
        RGLMatrix result;
        return multiply(result, matrix2, *this);
    }

    RGLVectorf multiply(RGLVectorf const &p) const;

    RGLVectorf &operator[](GLint index) {
        return mData[index];
    }

    const RGLVectorf &operator[](GLint index) const {
        return mData[index];
    }

    float det3x3(float a, float b, float c,
                 float d, float e, float f,
                 float g, float h, float i) const {
        return a * e * i + d * h * c + g * b * f - a * h * f - g * e * c - d * b * i;
    }

    float determinant() const;

    RGLMatrix invertTranspose() const;

    RGLMatrix transpose() const;

public:
    static RGLMatrix &multiply(RGLMatrix &result,
                               RGLMatrix const &matrix1,
                               RGLMatrix const &matrix2
                              );

private:
    RGLVectorf mData[4];
};

#endif

