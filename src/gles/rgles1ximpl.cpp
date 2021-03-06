
#include "rgles1ximpl.h"

#include <iostream>
#include <math.h>
#include <string.h>

RGles1x * RGles1x::mAPI = 0;

RGles1xImpl::RGles1xImpl()
{}

void RGles1xImpl::matrixMode(GLenum mode)
{
    mState->mMatrixMode = mode;
}

void RGles1xImpl::initialize(InitParam const &param, void * state)
{
    mState = (RGles1xImplState *)state;

    RGles1x::mAPI = this;

    bool reinitialization = false;

    if (mState->mBuffers.mColor) {
        reinitialization = true;
    }

    mState->mWidth = param.mWidth;
    mState->mHeight = param.mHeight;

    delete [] mState->mBuffers.mColor;
    delete [] mState->mBuffers.mDepth;
    delete [] mState->mBuffers.mStencil;

    mState->mBuffers.mColor = 0;
    mState->mBuffers.mDepth = 0;
    mState->mBuffers.mStencil = 0;

    mState->mBuffers.mColor = new RGLColorf[mState->mWidth * mState->mHeight];

    if (param.mHasDepth) {
        mState->mBuffers.mDepth = new GLfloat[mState->mWidth * mState->mHeight];
    } else {
        mState->mBuffers.mStencil = new GLfloat[mState->mWidth * mState->mHeight];
    }

    if (!reinitialization) {
        matrixMode(GL_PROJECTION);
        loadIdentity();

        matrixMode(GL_MODELVIEW);
        loadIdentity();

        viewport(0, 0, mState->mWidth, mState->mHeight);

        clearColor(0.0f, 0.0f, 0.0f, 1.0f);
        color(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

void RGles1xImpl::loadMatrix(const GLfloat m[16])
{
    switch (mState->mMatrixMode) {
    case GL_PROJECTION:
        mState->mProjection.load(m);
        break;

    case GL_MODELVIEW:
        mState->mModelview.load(m);
        break;
    }
}

void RGles1xImpl::frustum(GLfloat leftValue, GLfloat rightValue,
                                    GLfloat bottomValue, GLfloat topValue,
                                    GLfloat nearValue, GLfloat farValue)
{
    GLfloat fm[4 * 4];
    fm[0] = 2.0f * nearValue / (rightValue - leftValue);
    fm[1] = 0.0f;
    fm[2] = 0.0f;
    fm[3] = 0.0f;

    fm[4] = 0.0f;
    fm[5] = 2.0f * nearValue / (topValue - bottomValue);
    fm[6] = 0.0f;
    fm[7] = 0.0f;

    fm[8] = (rightValue + leftValue) / (rightValue - leftValue);
    fm[9] = (topValue + bottomValue) / (topValue - bottomValue);
    fm[10] = -(farValue + nearValue) / (farValue - nearValue);
    fm[11] = -1.0f;

    fm[12] = 0.0f;
    fm[13] = 0.0f;
    fm[14] = -2.0f * (farValue * nearValue) / (farValue - nearValue);
    fm[15] = 0.0f;

    switch (mState->mMatrixMode) {
    case GL_PROJECTION: {
        RGLMatrix m;
        m.load(fm);
        mState->mProjection = mState->mProjection.multiply(RGLMatrix(m));
        break;
    }

    case GL_MODELVIEW: {
        RGLMatrix m;
        m.load(fm);
        mState->mModelview = mState->mModelview.multiply(RGLMatrix(m));
        break;
    }
    }
}

void RGles1xImpl::ortho(GLfloat leftValue, GLfloat rightValue,
                                  GLfloat bottomValue, GLfloat topValue,
                                  GLfloat nearValue, GLfloat farValue)
{
    GLfloat om[4 * 4];
    om[0] = 2.0f / (rightValue - leftValue);
    om[1] = 0.0f;
    om[2] = 0.0f;
    om[3] = 0.0f;

    om[4] = 0.0f;
    om[5] = 2.0f / (topValue - bottomValue);
    om[6] = 0.0f;
    om[7] = 0.0f;

    om[8] = 0.0f;
    om[9] = 0.0f;
    om[10] = -2.0f / (farValue - nearValue);
    om[11] = 0.0f;

    om[12] = -(rightValue + leftValue) / (rightValue - leftValue);
    om[13] = -(topValue + bottomValue) / (topValue - bottomValue);
    om[14] = -(farValue + nearValue) / (farValue - nearValue);
    om[15] = 1.0f;

    switch (mState->mMatrixMode) {
    case GL_PROJECTION: {
        RGLMatrix m;
        m.load(om);
        mState->mProjection = mState->mProjection.multiply(RGLMatrix(m));
        break;
    }

    case GL_MODELVIEW: {
        RGLMatrix m;
        m.load(om);
        mState->mModelview = mState->mModelview.multiply(RGLMatrix(m));
        break;
    }
    }
}

void RGles1xImpl::scale(GLfloat sx, GLfloat sy, GLfloat sz)
{
    GLfloat sm[4 * 4] = {
        sx, 0.0f, 0.0f, 0.0f,
        0.0f, sy, 0.0f, 0.0f,
        0.0f, 0.0f, sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    switch (mState->mMatrixMode) {
    case GL_PROJECTION: {
        RGLMatrix m;
        m.load(sm);
        mState->mProjection = mState->mProjection.multiply(m);
        break;
    }

    case GL_MODELVIEW: {
        RGLMatrix m;
        m.load(sm);
        mState->mModelview = mState->mModelview.multiply(m);
        break;
    }
    }
}

void RGles1xImpl::translate(GLfloat tx, GLfloat ty, GLfloat tz)
{
    GLfloat tm[4 * 4] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        tx, ty, tz, 1.0f
    };

    switch (mState->mMatrixMode) {
    case GL_PROJECTION: {
        RGLMatrix m;
        m.load(tm);
        mState->mProjection = mState->mProjection.multiply(m);
        break;
    }

    case GL_MODELVIEW: {
        RGLMatrix m;
        m.load(tm);
        mState->mModelview = mState->mModelview.multiply(m);
        break;
    }
    }
}

void RGles1xImpl::rotate(GLfloat angle, GLfloat ax, GLfloat ay,
                                   GLfloat az)
{
    RGLMatrix m;

    GLfloat radians, sine, cosine, ab, bc, ca, t;
    RGLVectorf axis(ax, ay, az);

    axis = axis.toUnit();

    radians = angle * GL_PI / 180.0f;
    sine = sinf(radians);
    cosine = cosf(radians);
    ab = axis[0] * axis[1] * (1 - cosine);
    bc = axis[1] * axis[2] * (1 - cosine);
    ca = axis[2] * axis[0] * (1 - cosine);

    t = axis[0] * axis[0];
    m[0][0] = t + cosine * (1 - t);
    m[2][1] = bc - axis[0] * sine;
    m[1][2] = bc + axis[0] * sine;

    t = axis[1] * axis[1];
    m[1][1] = t + cosine * (1 - t);
    m[2][0] = ca + axis[1] * sine;
    m[0][2] = ca - axis[1] * sine;

    t = axis[2] * axis[2];
    m[2][2] = t + cosine * (1 - t);
    m[1][0] = ab - axis[2] * sine;
    m[0][1] = ab + axis[2] * sine;

    switch (mState->mMatrixMode) {
    case GL_PROJECTION: {
        mState->mProjection = mState->mProjection.multiply(m);
        break;
    }

    case GL_MODELVIEW: {
        mState->mModelview = mState->mModelview.multiply(m);
        break;
    }
    }
}

void RGles1xImpl::loadIdentity()
{
    switch (mState->mMatrixMode) {
    case GL_PROJECTION:
        mState->mProjection.reset();
        break;

    case GL_MODELVIEW:
        mState->mModelview.reset();
        break;
    }
}

void RGles1xImpl::enable(GLenum cap)
{
    switch (cap) {
    case GL_TEXTURE_2D:
        mState->mFeature.mTexture2D = true;
        break;

    case GL_COLOR_MATERIAL:
        mState->mFeature.mColorMaterial = true;
        break;

    case GL_LIGHTING:
        mState->mFeature.mLighting = true;
        break;

    case GL_LIGHT0:
        mState->mFeature.mLights[0] = true;
        break;

    case GL_DEPTH_TEST:
        mState->mFeature.mDepthTest = true;
        break;

    case GL_VERTEX_ARRAY:
        mState->mFeature.mVertexArray = true;
        break;

    case GL_NORMAL_ARRAY:
        mState->mFeature.mNormalArray = true;
        break;

    case GL_COLOR_ARRAY:
        mState->mFeature.mColorArray = true;
        break;

    case GL_TEXTURE_COORD_ARRAY:
        mState->mFeature.mTexCoordArray = true;
        break;
    }
}

void RGles1xImpl::disable(GLenum cap)
{
    switch (cap) {
    case GL_TEXTURE_2D:
        mState->mFeature.mTexture2D = false;
        break;

    case GL_COLOR_MATERIAL:
        mState->mFeature.mColorMaterial = false;
        break;

    case GL_LIGHTING:
        mState->mFeature.mLighting = false;
        break;

    case GL_LIGHT0:
        mState->mFeature.mLights[0] = false;
        break;

    case GL_DEPTH_TEST:
        mState->mFeature.mDepthTest = false;
        break;

    case GL_VERTEX_ARRAY:
        mState->mFeature.mVertexArray = false;
        break;

    case GL_NORMAL_ARRAY:
        mState->mFeature.mNormalArray = false;
        break;

    case GL_COLOR_ARRAY:
        mState->mFeature.mColorArray = false;
        break;

    case GL_TEXTURE_COORD_ARRAY:
        mState->mFeature.mTexCoordArray = false;
        break;

    }
}

void RGles1xImpl::depthFunc(GLenum func)
{
    switch (func) {
    case GL_ALWAYS:
        mState->mFuncs.mDepthFunc = rglFuncAlways<GLfloat>;
        break;

    case GL_LESS:
        mState->mFuncs.mDepthFunc = rglFuncLess;
        break;

    case GL_LEQUAL:
        mState->mFuncs.mDepthFunc = rglFuncLEqual<GLfloat>;
        break;

    default:
        mState->mError = GL_INVALID_ENUM;
        break;
    }
}

/* flush operations */
void RGles1xImpl::flush()
{}

void RGles1xImpl::finish()
{
    flush();
}

/* retrieve color buffer */
void RGles1xImpl::readPixels(GLint x, GLint y, GLsizei width,
                                       GLsizei height, GLenum format,
                                       GLenum type, GLvoid *pixels,
                                       bool originTopLeft)
{
    GLint colorCount = 0;
    int readIndex;
    int writeIndex;
    int newJ;

    switch (format) {
    case GL_RGB:
        colorCount = 3;
        break;

    case GL_RGBA:
        colorCount = 4;
        break;
    }

    for (int i = x; i < width; ++i) {
        for (int j = y; j < height; ++j) {
            newJ = j;
            writeIndex = ((i) + j * width) * colorCount;
            if (originTopLeft) {
                newJ = (height - 1) - (j - y);
            }

            readIndex = i + (newJ * width);

            for (GLint k = 0; k < colorCount; ++k) {
                switch (type) {
                case GL_UNSIGNED_BYTE: {
                    ((GLubyte *)pixels)[writeIndex + k] = (GLubyte)(
                            0xFF * mState->mBuffers.mColor[readIndex].data()[k]);
                    break;
                }

                case GL_FLOAT: {
                    ((GLfloat *)pixels)[writeIndex + k] =
                        mState->mBuffers.mColor[readIndex].data()[k];
                    break;
                }
                }
            }
        }
    }

    return;
}

void RGles1xImpl::normal(GLfloat nx, GLfloat ny, GLfloat nz)
{
    mState->mCurrentNormal.setX(nx);
    mState->mCurrentNormal.setY(ny);
    mState->mCurrentNormal.setZ(nz);
}

void RGles1xImpl::light(GLenum light, GLenum pname, const GLfloat *params)
{
    RGLASSERT_WE((light - GL_LIGHT0) < GL_MAX_LIGHT_UNITS, GL_INVALID_ENUM);

    RGles1xImplLight & l = mState->mLights[light - GL_LIGHT0];

    switch (pname) {
    case GL_AMBIENT:
        l.mAmbient.set(params);
        break;

    case GL_DIFFUSE:
        l.mDiffuse.set(params);
        break;

    case GL_SPECULAR:
        l.mSpecular.set(params);
        break;

    case GL_POSITION:
        l.mPosition.set(params);
        break;

    case GL_SPOT_DIRECTION:
        l.mSpotDirection.set(params);
        break;

    case GL_SPOT_EXPONENT:
        l.mSpotExponent = *params;
        break;

    case GL_SPOT_CUTOFF:
        l.mSpotCutoff = *params;
        break;

    case GL_CONSTANT_ATTENUATION:
        l.mConstantAttenuation = *params;
        break;

    case GL_LINEAR_ATTENUATION:
        l.mLinearAttenuation = *params;
        break;

    case GL_QUADRATIC_ATTENUATION:
        l.mQuadraticAttenuation = *params;
        break;

    default:
        mState->mError = GL_INVALID_ENUM;
        break;
    }

}

void RGles1xImpl::material(GLenum face, GLenum pname, const GLfloat *params)
{
    RGLASSERT_WE(face == GL_FRONT_AND_BACK, GL_INVALID_VALUE);

    switch (pname) {
    case GL_AMBIENT:
        mState->mMaterial.mAmbient.set(params);
        break;

    case GL_DIFFUSE:
        mState->mMaterial.mDiffuse.set(params);
        break;

    case GL_SPECULAR:
        mState->mMaterial.mSpecular.set(params);
        break;

    case GL_EMISSION:
        mState->mMaterial.mEmissive.set(params);
        break;

    default:
        mState->mError = GL_INVALID_ENUM;
        break;
    }
}


void RGles1xImpl::texCoordPointer(GLint size, GLenum type, GLsizei stride,
        const GLvoid *pointer)
{
    RGLASSERT_WE(size == 2, GL_INVALID_VALUE);
    RGLASSERT_WE(type == GL_FLOAT, GL_INVALID_VALUE);
    RGLASSERT_WE(stride == 0, GL_INVALID_VALUE);

    mState->mTexCoordData.mSize = size;
    mState->mTexCoordData.mType = type;
    mState->mTexCoordData.mStride = stride;
    mState->mTexCoordData.mPointer = pointer;
}

void RGles1xImpl::normalPointer(GLenum type, GLsizei stride,
        const GLvoid *pointer)
{
    RGLASSERT_WE(type == GL_FLOAT, GL_INVALID_VALUE);
    RGLASSERT_WE(stride == 0, GL_INVALID_VALUE);


    mState->mNormalData.mSize = 3;
    mState->mNormalData.mType = type;
    mState->mNormalData.mStride = stride;
    mState->mNormalData.mPointer = pointer;
}

void RGles1xImpl::colorPointer(GLint size, GLenum type,
        GLsizei stride,
        const GLvoid *pointer)
{
    RGLASSERT_WE(size == 4, GL_INVALID_VALUE);
    RGLASSERT_WE(type == GL_FLOAT, GL_INVALID_VALUE);
    RGLASSERT_WE(stride == 0, GL_INVALID_VALUE);

    mState->mColorData.mSize = size;
    mState->mColorData.mType = type;
    mState->mColorData.mStride = stride;
    mState->mColorData.mPointer = pointer;
}

void RGles1xImpl::vertexPointer(GLint size, GLenum type,
        GLsizei stride, const GLvoid *pointer)
{
    RGLASSERT_WE(size == 2 || size == 3, GL_INVALID_VALUE);
    RGLASSERT_WE(type == GL_FLOAT, GL_INVALID_VALUE);
    RGLASSERT_WE(stride == 0, GL_INVALID_VALUE);

    mState->mVertexData.mSize = size;
    mState->mVertexData.mType = type;
    mState->mVertexData.mStride = stride;
    mState->mVertexData.mPointer = pointer;
}

RGLVectorf *readVertexData(const GLvoid *pointer,
                           GLint size, GLenum type,
                           GLint first, GLsizei count)
{
    RGLVectorf *points = new RGLVectorf[count];

    for (int i = 0; i < count; ++i) {
        switch (type) {
        case GL_FLOAT: {
            GLfloat *fpointer = (GLfloat *)pointer;

            if (size > 0) {
                points[i].setX(fpointer[size * (first + i) + 0]);
            }

            if (size > 1) {
                points[i].setY(fpointer[size * (first + i) + 1]);
            }

            if (size > 2) {
                points[i].setZ(fpointer[size * (first + i) + 2]);
            }

            if (size > 3) {
                points[i].setW(fpointer[size * (first + i) + 3]);
            }

            break;
        }

        case GL_UNSIGNED_BYTE: {
            GLubyte *ubpointer = (GLubyte *)pointer;

            if (size > 0) {
                points[i].setX(ubpointer[size * (first + i) + 0]);
            }

            if (size > 1) {
                points[i].setY(ubpointer[size * (first + i) + 1]);
            }

            if (size > 2) {
                points[i].setZ(ubpointer[size * (first + i) + 2]);
            }

            if (size > 3) {
                points[i].setW(ubpointer[size * (first + i) + 3]);
            }

            break;
        }
        }
    }

    return points;
}

void RGles1xImpl::drawArrays(GLenum mode, GLint first,
                                       GLsizei count)
{
    if (!mState->mVertexData.mPointer ||
            !mState->mFeature.mVertexArray) {
        return;
    }

    RGles1xImplPrimitive primitive;
    RGLColorf *colors = 0;
    RGLVectorf *normals = 0;
    RGLVectorf *texcoords = 0;
    RGLVectorf *points = readVertexData(mState->mVertexData.mPointer,
                                        mState->mVertexData.mSize,
                                        mState->mVertexData.mType,
                                        first, count);

    if (mState->mFeature.mTexture2D &&
    		mState->mFeature.mTexCoordArray &&
            mState->mTexCoordData.mPointer) {
        texcoords = (RGLColorf *) readVertexData(mState->mTexCoordData.mPointer,
                    mState->mTexCoordData.mSize,
                    mState->mTexCoordData.mType,
                    first, count);
    }

    if (mState->mFeature.mColorArray &&
            mState->mColorData.mPointer) {
        colors = (RGLColorf *) readVertexData(mState->mColorData.mPointer,
                                              mState->mColorData.mSize,
                                              mState->mColorData.mType,
                                              first, count);

    }

    if (mState->mFeature.mNormalArray &&
            mState->mNormalData.mPointer) {
        normals = (RGLVectorf *) readVertexData(mState->mNormalData.mPointer,
                                                mState->mNormalData.mSize,
                                                mState->mNormalData.mType,
                                                first, count);
    }

    primitive.mMode = mode;
    primitive.mCount = count;
    primitive.mPoints = points;
    primitive.mColors = colors;
    primitive.mNormals = normals;
    primitive.mTexCoords = texcoords;

    perVertexOperations(&primitive);

    delete [] points;
    delete [] colors;
    delete [] normals;
    delete [] texcoords;
}

/* clear operations */
void RGles1xImpl::clearColor(GLclampf r, GLclampf g, GLclampf b,
                                       GLclampf a)
{
    mState->mClearColor.setR(clamp(r));
    mState->mClearColor.setG(clamp(g));
    mState->mClearColor.setB(clamp(b));
    mState->mClearColor.setA(clamp(a));
}

void RGles1xImpl::clear(GLbitfield mask)
{
    for (int i = 0; i < mState->mWidth * mState->mHeight; ++i) {
        if (mask & GL_COLOR_BUFFER_BIT) {
            mState->mBuffers.mColor[i] = mState->mClearColor;
        }

        if (mask & GL_DEPTH_BUFFER_BIT && mState->mBuffers.mDepth) {
            mState->mBuffers.mDepth[i] = mState->mClearDepth;
        }

        if (mask & GL_STENCIL_BUFFER_BIT && mState->mBuffers.mStencil) {
            mState->mBuffers.mStencil[i] = mState->mClearStencil;
        }
    }
}

/* color settings */
void RGles1xImpl::color(GLfloat r, GLfloat g, GLfloat b,
                                  GLfloat a)
{
    mState->mCurrentColor.setR(clamp(r));
    mState->mCurrentColor.setG(clamp(g));
    mState->mCurrentColor.setB(clamp(b));
    mState->mCurrentColor.setA(clamp(a));
}

void RGles1xImpl::viewport(int x, int y, int width, int height)
{
    mState->mViewportX = x;
    mState->mViewportY = y;
    mState->mViewportWidth = width;
    mState->mViewportHeight = height;
}

void RGles1xImpl::drawPoint(RGles1xImplFragments
                                      &fragments,
                                      RGles1xImplPrimitive const & primitive)
{
    const RGLVectorf &p = primitive.mPoints[0];
    GLfloat depth = p.z();
    if (p.x() >= 0 && p.y() >= 0 &&
            p.x() < mState->mWidth && p.y() < mState->mHeight &&
            depth >= mState->mDepthRange[0] && depth <= mState->mDepthRange[1]) {
        RGles1xImplFragments::Fragment fragment;
        if (primitive.mColors) {
            fragment.mColor = primitive.mColors[0];
        } else {
            fragment.mColor = mState->mCurrentColor;
        }

        if (mState->mFeature.mTexture2D) {
        	if (primitive.mTexCoords) {
        		fragment.mTexCoords = primitive.mTexCoords[0];
        	} else {
        		fragment.mTexCoords = mState->mCurrentTexCoord;
        	}
        }

        fragment.mPoint = RGLVector2Di((int)p.x(), (int)p.y());
        fragment.mDepth = depth;

        fragments.add(fragment);
    }
}

void RGles1xImpl::drawLine(RGles1xImplFragments
                                     &fragments,
                                     RGles1xImplPrimitive const & primitive)
{
    RGLVectorf p1 = primitive.mPoints[0];
    RGLVectorf p2 = primitive.mPoints[1];

    RGLColorf color;
    RGLVectorf texcoord;

    clipLine(p1, p2);

    float t = 0.0f;
    float tInc = 1.0f / (lineLength(p1, p2) + 4);

    for (; t <= 1.0f; t += tInc) {
        RGles1xImplPrimitive pointPrimitive;
        RGLVectorf point(interpolate(t, p1, p2));

        pointPrimitive.mCount = 1;
        pointPrimitive.mPoints = &point;
        pointPrimitive.mMode = GL_POINTS;

        if (primitive.mColors) {
            color = interpolate(t, primitive.mColors[0], primitive.mColors[1]);

            pointPrimitive.mColors = &color;
        }
        if (primitive.mTexCoords) {
        	texcoord = interpolate(t, primitive.mTexCoords[0], primitive.mTexCoords[1]);
        	pointPrimitive.mTexCoords = &texcoord;
        }

        drawPoint(fragments, pointPrimitive);
    }
}

/* This one of the most worst way to render a triangle, but performance is not our aim */
void RGles1xImpl::drawTriangle(RGles1xImplFragments
        &fragments,
        RGles1xImplPrimitive const & primitive)
{
    const RGLVectorf &p1 = primitive.mPoints[0];
    const RGLVectorf &p2 = primitive.mPoints[1];
    const RGLVectorf &p3 = primitive.mPoints[2];
    RGLColorf colors[2];
    RGLVectorf texcoords[2];

    float t = 0.0f;
    float tInc = 0.5f / lineLength(p2, p3);

    for (; t <= 1.0f; t += tInc) {
        RGles1xImplPrimitive linePrimitive;
        RGLVectorf points[2] = {p1, interpolate(t, p2, p3)};

        linePrimitive.mCount = 2;
        linePrimitive.mPoints = &points[0];
        linePrimitive.mMode = GL_LINES;

        if (primitive.mColors) {
            const RGLColorf &c1 = primitive.mColors[0];
            const RGLColorf &c2 = primitive.mColors[1];
            const RGLColorf &c3 = primitive.mColors[2];

            colors[0] = c1;
            colors[1] = interpolate(t, c2, c3);

            linePrimitive.mColors = &colors[0];
        }
        if (primitive.mTexCoords) {
            const RGLColorf &v1 = primitive.mTexCoords[0];
            const RGLColorf &v2 = primitive.mTexCoords[1];
            const RGLColorf &v3 = primitive.mTexCoords[2];

            texcoords[0] = v1;
            texcoords[1] = interpolate(t, v2, v3);

            linePrimitive.mTexCoords = &texcoords[0];
        }

        drawLine(fragments, linePrimitive);
    }
}

void RGles1xImpl::perVertexOperations(
    RGles1xImplPrimitive *primitive)
{
    /* apply model view transformations */
    for (int i = 0; i < primitive->mCount; ++i) {
        primitive->mPoints[i] = mState->mModelview.multiply(
                                    primitive->mPoints[i]);
    }

    bool updateColors = false;
    RGLColorf * colors = 0;

    /* apply light */
    if (enabledLighting()) {
        colors = new RGLColorf[primitive->mCount];
        updateColors = true;
        applyLighting(primitive, colors);
    }

    /* apply projection transformations */
    for (int i = 0; i < primitive->mCount; ++i) {
        primitive->mPoints[i] = mState->mProjection.multiply(
                                    primitive->mPoints[i]);
    }

    /* apply perspective division */
    for (int i = 0; i < primitive->mCount; ++i) {
        RGLVectorf &v = primitive->mPoints[i];

        if (rglFuncNotEqual(v.w(), 1.0f)) {
            v.setX(v.x() / v.w());
            v.setY(v.y() / v.w());
            v.setZ(v.z() / v.w());
        }
    }

    /*
    * generate window coordinate
    * this will generate window coordinate
    * with respect to view port (x, y) and (width, height)
    */
    GLfloat dz = mState->mDepthRange[1] - mState->mDepthRange[0];
    GLfloat cz = (mState->mDepthRange[1] + mState->mDepthRange[0])  / 2.0f;

    for (int i = 0; i < primitive->mCount; ++i) {
        RGLVectorf &p = primitive->mPoints[i];

        p.setX((mState->mViewportWidth / 2.0f) * p.x() +
               (mState->mViewportX +
                (mState->mViewportWidth / 2.0f)));
        p.setY((mState->mViewportHeight / 2.0f) * p.y() +
               (mState->mViewportY + (mState->mViewportHeight / 2.0f)));
        p.setZ((dz / 2.0f) * p.z() + cz);
    }

    if (updateColors) {
        primitive->mColors = colors;
    }

    clipAndRasterization(primitive);

    if (updateColors) {
        delete [] colors;
    }
}

bool RGles1xImpl::enabledLighting()
{
    bool enabled = false;
    if (mState->mFeature.mLighting) {
        for (int lightIndex = 0; lightIndex < GL_MAX_LIGHT_UNITS; ++lightIndex) {
            if (mState->mFeature.mLights[lightIndex]) {
                enabled = true;
                break;
            }
        }
    }

    return enabled;
}

void RGles1xImpl::applyLighting(RGles1xImplPrimitive *primitive,
        RGLColorf * colors)
{
    if (!mState->mFeature.mLighting) {
        return;
    }

    RGLMatrix mat = mState->mModelview.invertTranspose();

    RGLVectorf normal;

    if (!primitive->mNormals) {
        normal = mState->mCurrentNormal;
    }

    normal = mat.multiply(normal);
    normal = normal.toUnit();

    for (int lightIndex = 0; lightIndex < GL_MAX_LIGHT_UNITS; ++lightIndex) {
        if (mState->mFeature.mLights[lightIndex]) {
            RGles1xImplLight & light = mState->mLights[lightIndex];

            for (int j = 0; j < primitive->mCount; ++j) {
                RGLVectorf & position = primitive->mPoints[j];

                if (primitive->mNormals) {
                    normal = primitive->mNormals[j];
                    normal = mat.multiply(normal);
                    normal = normal.toUnit();
                }

                RGLVectorf ldir;
                if (rglFuncEqual(light.mPosition.w(), 0.0f)) {
                    ldir = light.mPosition;
                } else {
                    ldir = light.mPosition - position;
                }

                ldir = ldir.toUnit();

                GLfloat nDotVP = rglMax(0.0f, normal.dot(ldir));
                GLfloat nDotHV = rglMax(0.0f, normal.dot(ldir));
                GLfloat pf;

                if (rglFuncEqual(nDotHV, 0.0f)) {
                    pf = 0.0f;
                } else {
                    pf = powf(nDotHV, light.mSpotExponent);
                }

                RGLColorf ambient(light.mAmbient);
                RGLColorf diffuse(light.mDiffuse);
                RGLColorf specular(light.mSpecular);

                if (mState->mFeature.mColorMaterial) {
                    if (primitive->mColors) {
                        diffuse *= primitive->mColors[j];
                    } else {
                        diffuse *= mState->mCurrentColor;
                    }
                } else {
                    diffuse *= mState->mMaterial.mDiffuse;
                }

                ambient *= mState->mMaterial.mAmbient;
                specular *= mState->mMaterial.mSpecular;

                colors[j] += ambient +
                             (diffuse * nDotVP) +
                             (specular * pf);

                colors[j].clampValues();
            }

        }
    }
}

void RGles1xImpl::clipAndRasterization(
    RGles1xImplPrimitive *primitive)
{
    RGles1xImplFragments fragments(mState->mWidth, mState->mHeight);

    switch (primitive->mMode) {
    case GL_POINTS: {
        RGles1xImplPrimitive pointPrimitive;
        pointPrimitive.mCount = 1;
        pointPrimitive.mMode = GL_POINTS;
        for (int i = 0; i < primitive->mCount; ++i) {
            pointPrimitive.mPoints = &(primitive->mPoints[i]);
            if (primitive->mColors) {
                pointPrimitive.mColors = &(primitive->mColors[i]);
            }
            if (primitive->mTexCoords) {
            	pointPrimitive.mTexCoords = &(primitive->mTexCoords[i]);
            }
            drawPoint(fragments,  pointPrimitive);
            perFragmentOperations(fragments);
        }
        break;
    }

    case GL_LINES: {
        if (primitive->mCount < 2) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        /* not even ignore the last point */
        if ((primitive->mCount % 2) != 0) {
            --primitive->mCount;
        }

        const GLint size = primitive->mCount / 2;

        RGles1xImplPrimitive linePrimitive;
        linePrimitive.mCount = 2;
        linePrimitive.mMode = GL_LINES;

        for (int i = 0; i < size; ++i) {
            linePrimitive.mPoints = primitive->mPoints + 2 * i;
            if (primitive->mColors) {
                linePrimitive.mColors = primitive->mColors + 2 * i;
            }

            if (primitive->mTexCoords) {
            	linePrimitive.mTexCoords = primitive->mTexCoords + 2 * i;
            }

            drawLine(fragments, linePrimitive);
            perFragmentOperations(fragments);
        }
        break;
    }

    case GL_LINE_LOOP: {
        if (primitive->mCount < 2) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        RGles1xImplPrimitive linePrimitive;
        linePrimitive.mCount = 2;
        linePrimitive.mMode = GL_LINES;

        RGLColorf colors[2];
        RGLVectorf points[2];
        RGLVectorf texcoords[2];
        points[0] = primitive->mPoints[0];

        if (primitive->mColors) {
            colors[0] = primitive->mColors[0];
            linePrimitive.mColors = &(colors[0]);
        }

        if (primitive->mTexCoords) {
        	texcoords[0] = primitive->mTexCoords[0];
            linePrimitive.mTexCoords = &(texcoords[0]);
        }

        linePrimitive.mPoints = &(points[0]);

        for (int i = 1; i < primitive->mCount; ++i) {
            points[1] = primitive->mPoints[i];
            if (primitive->mColors) {
                colors[1] = primitive->mColors[i];
            }

            if (primitive->mTexCoords) {
            	texcoords[1] = primitive->mTexCoords[i];
            }

            drawLine(fragments, linePrimitive);
            perFragmentOperations(fragments);

            points[0] = points[1];

            if (primitive->mColors) {
                colors[0] = colors[1];
            }
            if (primitive->mTexCoords) {
            	texcoords[0] = texcoords[1];
            }
        }

        points[1] = primitive->mPoints[0];
        if (primitive->mColors) {
            colors[1] = primitive->mColors[0];
        }
        if (primitive->mTexCoords) {
        	texcoords[1] = primitive->mTexCoords[0];
        }

        drawLine(fragments, linePrimitive);
        perFragmentOperations(fragments);
        break;
    }

    case GL_LINE_STRIP: {
        if (primitive->mCount < 2) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        RGles1xImplPrimitive linePrimitive;
        linePrimitive.mCount = 2;
        linePrimitive.mMode = GL_LINES;

        RGLColorf colors[2];
        RGLVectorf points[2];
        RGLVectorf texcoords[2];
        points[0] = primitive->mPoints[0];

        if (primitive->mColors) {
            colors[0] = primitive->mColors[0];
            linePrimitive.mColors = &(colors[0]);
        }
        if (primitive->mTexCoords) {
        	texcoords[0] = primitive->mTexCoords[0];
            linePrimitive.mTexCoords = &(texcoords[0]);
        }

        linePrimitive.mPoints = &(points[0]);

        for (int i = 1; i < primitive->mCount; ++i) {
            points[1] = primitive->mPoints[i];
            if (primitive->mColors) {
                colors[1] = primitive->mColors[i];
            }
            if (primitive->mTexCoords) {
            	texcoords[1] = primitive->mTexCoords[i];
            }

            drawLine(fragments, linePrimitive);
            perFragmentOperations(fragments);

            points[0] = points[1];

            if (primitive->mColors) {
                colors[0] = colors[1];
            }
            if (primitive->mTexCoords) {
            	texcoords[0] = texcoords[1];
            }
        }

        break;
    }

    case GL_TRIANGLES: {
        if (primitive->mCount < 3) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        /* if not a multiple of 3 ignore the remainder when divided by 3 */
        const GLint size = primitive->mCount / 3;

        RGles1xImplPrimitive trianglePrimitive;
        trianglePrimitive.mCount = 3;
        trianglePrimitive.mMode = GL_TRIANGLES;

        for (int i = 0; i < size; ++i) {
            trianglePrimitive.mPoints = primitive->mPoints + (3 * i);
            if (primitive->mColors) {
                trianglePrimitive.mColors = primitive->mColors + (3 * i);
            }
            if (primitive->mTexCoords) {
                trianglePrimitive.mTexCoords = primitive->mTexCoords + (3 * i);
            }
            drawTriangle(fragments, trianglePrimitive);
            perFragmentOperations(fragments);
        }

        break;
    }

    case GL_TRIANGLE_FAN: {
        if (primitive->mCount < 3) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        RGles1xImplPrimitive trianglePrimitive;
        trianglePrimitive.mCount = 3;
        trianglePrimitive.mMode = GL_TRIANGLES;

        RGLColorf colors[3];
        RGLVectorf points[3];
        RGLVectorf texcoords[3];

        if (primitive->mColors) {
            colors[0] = primitive->mColors[0];
            colors[1] = primitive->mColors[1];
            trianglePrimitive.mColors = &(colors[0]);
        }
        if (primitive->mTexCoords) {
        	texcoords[0] = primitive->mTexCoords[0];
        	texcoords[1] = primitive->mTexCoords[1];
            trianglePrimitive.mTexCoords = &(texcoords[0]);
        }

        trianglePrimitive.mPoints = &(points[0]);

        points[0] = primitive->mPoints[0];
        points[1] = primitive->mPoints[1];

        for (int i = 2; i < primitive->mCount; ++i) {
            points[2] = primitive->mPoints[i];

            if (primitive->mColors) {
                colors[2] = primitive->mColors[i];
            }
            if (primitive->mTexCoords) {
            	texcoords[2] = primitive->mTexCoords[i];
            }

            drawTriangle(fragments, trianglePrimitive);
            perFragmentOperations(fragments);

            points[1] = points[2];

            if (primitive->mColors) {
                colors[1] = colors[2];
            }
            if (primitive->mTexCoords) {
            	texcoords[1] = texcoords[2];
            }
        }

        break;
    }

    case GL_TRIANGLE_STRIP: {
        if (primitive->mCount < 3) {
            mState->mError = GL_INVALID_VALUE;
            break;
        }

        RGles1xImplPrimitive trianglePrimitive;
        trianglePrimitive.mCount = 3;
        trianglePrimitive.mMode = GL_TRIANGLES;

        RGLColorf colors[3];
        RGLVectorf points[3];
        RGLVectorf texcoords[3];

        if (primitive->mColors) {
            colors[0] = primitive->mColors[0];
            colors[1] = primitive->mColors[1];
            trianglePrimitive.mColors = &(colors[0]);
        }
        if (primitive->mTexCoords) {
        	texcoords[0] = primitive->mTexCoords[0];
        	texcoords[1] = primitive->mTexCoords[1];
            trianglePrimitive.mTexCoords = &(texcoords[0]);
        }

        trianglePrimitive.mPoints = &(points[0]);

        points[0] = primitive->mPoints[0];
        points[1] = primitive->mPoints[1];

        for (int i = 2; i < primitive->mCount; ++i) {
            points[2] = primitive->mPoints[i];

            if (primitive->mColors) {
                colors[2] = primitive->mColors[i];
            }
            if (primitive->mTexCoords) {
            	texcoords[2] = primitive->mTexCoords[i];
            }

            drawTriangle(fragments, trianglePrimitive);
            perFragmentOperations(fragments);

            points[0] = points[1];
            points[1] = points[2];

            if (primitive->mColors) {
                colors[0] = colors[1];
                colors[1] = colors[2];
            }
            if (primitive->mTexCoords) {
            	texcoords[0] = texcoords[1];
            	texcoords[1] = texcoords[2];
            }
        }

        break;
    }

    default:
        mState->mError = GL_INVALID_ENUM;
        break;
    }
}

bool RGles1xImpl::depthTest(
    const RGles1xImplFragments::Fragment & fragment)
{
    bool result = true;

    if (mState->mFeature.mDepthTest) {
        int index = fragment.mPoint.x() + fragment.mPoint.y() * mState->mWidth;

        result = mState->mFuncs.mDepthFunc(mState->mBuffers.mDepth[index],
                                           fragment.mDepth);

        /* update the depth buffer, only if depth test passed */
        if (result) {
            mState->mBuffers.mDepth[index] = fragment.mDepth;
        }
    }

    return result;
}

void RGles1xImpl::applyTextureMapping(
    RGles1xImplFragments &fragments)
{
	RGLVectorf result;
	RGles1xImplTexture * texture = getCurrentTexture();
	if (mState->mFeature.mTexture2D && texture) {
		for (int i = 0; i < fragments.count(); ++i) {
			RGles1xImplFragments::Fragment &fragment = fragments.data()[i];
			if (fragment.mValid) {
				nearestFilter(texture, fragment.mTexCoords.x(), fragment.mTexCoords.y(), result);

				switch (mState->mTextureUnits[mState->mCurrentActiveTexture].mMode)
				{
				case GL_REPLACE:
					fragment.mColor = result;
					break;

				case GL_MODULATE:
					fragment.mColor *= result;
					fragment.mColor.clampValues();
					break;
				}
			}
		}
	}
}

void RGles1xImpl::perFragmentOperations(
    RGles1xImplFragments &fragments)
{
	applyTextureMapping(fragments);

    bool depthTestResult = true;

    for (int i = 0; i < fragments.count(); ++i) {
        RGles1xImplFragments::Fragment &fragment = fragments.data()[i];

        if (fragment.mValid) {
            /* do depth test (if not enabled will allways pass )*/
            depthTestResult = depthTest(fragment);

            if (depthTestResult) {
                int index = fragment.mPoint.x() + fragment.mPoint.y() * mState->mWidth;
                mState->mBuffers.mColor[index] = fragment.mColor;
            }
        }
    }
    fragments.reset();
}

RGles1xImpl::OutCode RGles1xImpl::computeOutCode(
    GLfloat x, GLfloat y,
    GLfloat xmin, GLfloat ymin,
    GLfloat xmax, GLfloat ymax)
{
    OutCode code = Inside;

    if (x < xmin) {
        code = Left;
    } else if (x > xmax) {
        code = Right;
    }

    if (y < ymin) {
        code = Bottom;
    } else if (y > ymax) {
        code = Top;
    }

    return code;
}

int RGles1xImpl::clipLine(RGLVectorf &p1, RGLVectorf &p2)
{
    const GLfloat xmin = 0.0f;
    const GLfloat ymin = 0.0f;
    GLfloat xmax = (GLfloat)mState->mWidth;
    GLfloat ymax = (GLfloat)mState->mHeight;

    /* is the line completely out side */
    OutCode outcode0 = computeOutCode(p1.x(), p1.y(), xmin, ymin, xmax, ymax);
    OutCode outcode1 = computeOutCode(p2.x(), p2.y(), xmin, ymin, xmax, ymax);

    int accept = 0;

    while (1) {
        if (!(outcode0 | outcode1)) {
            accept = 1;
            break;
        } else if (outcode0 & outcode1) {
            break;
        } else {
            GLfloat x;
            GLfloat y;

            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

            if (outcodeOut & Top) {
                x = p1.x() + (p2.x() - p1.x()) * (ymax - p1.y()) / (p2.y() - p1.y());
                y = ymax;
            } else if (outcodeOut & Bottom) {
                x = p1.x() + (p2.x() - p1.x()) * (ymin - p1.y()) / (p2.y() - p1.y());
                y = ymin;
            } else if (outcodeOut & Right) {
                y = p1.y() + (p2.y() - p1.y()) * (xmax - p1.x()) / (p2.x() - p1.x());
                x = xmax;
            } else if (outcodeOut & Left) {
                y = p1.y() + (p2.y() - p1.y()) * (xmin - p1.x()) / (p2.x() - p1.x());
                x = xmin;
            }

            if (outcodeOut == outcode0) {
                p1.setX(x);
                p1.setY(y);
                outcode0 = computeOutCode(p1.x(), p1.y(),
                                          xmin, ymin, xmax, ymax);
            } else {
                p2.setX(x);
                p2.setY(y);
                outcode1 = computeOutCode(p2.x(), p2.y(),
                                          xmin, ymin, xmax, ymax);
            }
        }
    }

    return accept;
}

/* textures */
void RGles1xImpl::genTextures(GLsizei n, GLuint *textures)
{
    for (int i = 0; i < n; ++i) {
        RGles1xImplTexture * tex = new RGles1xImplTexture();
        textures[i] = mState->mTextures.size();
        mState->mTextures.insert(std::make_pair(textures[i], tex));
    }
}

void RGles1xImpl::deleteTextures(GLsizei n, const GLuint *textures)
{
    for (int i = 0; i < n; ++i) {
        TextureListIter iter = mState->mTextures.find(textures[i]);
        if (iter != mState->mTextures.end()) {
            delete iter->second;
            mState->mTextures.erase(iter);
        }
    }
}

void RGles1xImpl::bindTexture(GLenum target, GLuint texture)
{
    RGLASSERT_WE(target == GL_TEXTURE_2D, GL_INVALID_VALUE);

    TextureListIter iter = mState->mTextures.find(texture);
    if (iter != mState->mTextures.end()) {
        mState->mTextureUnits[mState->mCurrentActiveTexture].mBoundTexture = texture;
    } else {
        mState->mError = GL_INVALID_VALUE;
    }
}

void RGles1xImpl::texEnv(GLenum target, GLenum pname, const GLint *params)
{
    RGLASSERT_WE(target == GL_TEXTURE_ENV, GL_INVALID_ENUM);
    RGLASSERT_WE(pname == GL_TEXTURE_ENV_MODE, GL_INVALID_ENUM);

    if (pname == GL_TEXTURE_ENV_MODE) {
        switch (*params) {
        case GL_REPLACE:
            mState->mTextureUnits[mState->mCurrentActiveTexture].mMode = *params;
            break;
        case GL_MODULATE:
            mState->mTextureUnits[mState->mCurrentActiveTexture].mMode = *params;
            break;
        default:
            mState->mError = GL_INVALID_VALUE;
            break;
        }
    }
}

RGles1xImplTexture *RGles1xImpl::getCurrentTexture()
{
	RGles1xImplTexture * texture = 0;
	TextureListIter iter = mState->mTextures.find(mState->mTextureUnits[mState->mCurrentActiveTexture].mBoundTexture);
	if (iter != mState->mTextures.end()) {
		texture = iter->second;
	}
	return texture;
}

void RGles1xImpl::texImage2D(GLenum target, GLint level, GLint internalformat,
                                       GLsizei width, GLsizei height, GLint border,
                                       GLenum format, GLenum type, const GLvoid *pixels)
{
    RGLASSERT_WE(target == GL_TEXTURE_2D, GL_INVALID_VALUE);
    RGLASSERT_WE(level == 0, GL_INVALID_VALUE);
    RGLASSERT_WE(border == 0, GL_INVALID_VALUE);
    RGLASSERT_WE(type == GL_UNSIGNED_BYTE, GL_INVALID_ENUM);
    RGLASSERT_WE(format == (GLenum)internalformat, GL_INVALID_VALUE);
    RGLASSERT_WE(format == GL_RGBA, GL_INVALID_VALUE);
    RGLASSERT_WE(width > 0, GL_INVALID_VALUE);
    RGLASSERT_WE(height > 0, GL_INVALID_VALUE);
    RGLASSERT_WE((width & (width - 1)) == 0, GL_INVALID_VALUE);
    RGLASSERT_WE((height & (height - 1)) == 0, GL_INVALID_VALUE);

    RGles1xImplTexture *texture = getCurrentTexture();
    if (texture) {
    	texture->mTarget = target;
    	texture->mLevel = level;
    	texture->mInternalformat = internalformat;
    	texture->mWidth = width;
    	texture->mHeight = height;
    	texture->mBorder = border;
    	texture->mFormat = format;
    	texture->mType = type;

        delete [] texture->mPixels;
        texture->mPixels = 0;

        switch (format) {
        case GL_RGBA: {
            const int size = 4 * width * height;
            texture->mPixels = new GLubyte[size];
            memcpy(texture->mPixels, pixels, size);
        }
        break;

        default: {
            mState->mError = GL_INVALID_ENUM;
        }
        break;
        }
    }
}

void RGles1xImpl::texParameter(GLenum target, GLenum pname, const GLint *params)
{
    RGLASSERT_WE(target == GL_TEXTURE_2D, GL_INVALID_VALUE);

    RGles1xImplTexture *texture = getCurrentTexture();
    if (texture) {
        switch (pname) {
        case GL_TEXTURE_WRAP_S:
            texture->mWrapS = *params;
            break;

        case GL_TEXTURE_WRAP_T:
            texture->mWrapT = *params;
            break;

        case GL_TEXTURE_MAG_FILTER:
            texture->mMagnification = *params;
            break;

        case GL_TEXTURE_MIN_FILTER:
            texture->mMinification = *params;
            break;
        }
    }
}

void RGles1xImpl::nearestFilter(RGles1xImplTexture * texture,
        GLfloat s, GLfloat t, RGLColorf & result)
{
    s *= texture->mWidth;
    t *= texture->mHeight;

    GLint row = (GLint) t;
    GLint col = (GLint) s;

    GLint w2 = texture->mWidth;
    GLint h2 = texture->mHeight;

    /* Find texel column address */
    if (texture->mWrapS == GL_REPEAT) {
        col &= w2 - 1;
    } else {
        if (col < 0) {
            col = 0;
        } else if (col >= w2) {
            col = w2 - 1;
        }
    }

    /* Find texel row address */
    if (texture->mWrapT == GL_REPEAT) {
        row &= h2 - 1;
    } else {
        if (row < 0) {
            row = 0;
        } else if (row >= h2) {
            row = h2 - 1;
        }
    }

    extractRGBA(texture, row, col, result);
}

void RGles1xImpl::extractRGBA(RGles1xImplTexture * texture,
                                        GLint row, GLint col, RGLColorf & result)
{
    GLint index = (row * texture->mWidth + col) * 4;

    result.setR(texture->mPixels[index + 0] / 255.0f);
    result.setG(texture->mPixels[index + 1] / 255.0f);
    result.setB(texture->mPixels[index + 2] / 255.0f);
    result.setA(texture->mPixels[index + 3] / 255.0f);
}
