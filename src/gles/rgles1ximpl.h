
#ifndef RGLINTERFACEIMPLV_0_1_H
#define RGLINTERFACEIMPLV_0_1_H

#include "rglutils.h"
#include "rglmatrix.h"
#include "rgles1x.h"

#include <vector>
#include <map>

#define GL_MAX_LIGHT_UNITS      1
#define GL_MAX_TEXTURE_UNITS    1

class RGles1xImplTextureUnit
{
public:
    RGles1xImplTextureUnit()
        : mMode(GL_MODULATE),
          mBoundTexture(0)
    {}

    GLint mMode;
    RGLColorf mColor;
    GLuint mBoundTexture;
};

class RGles1xImplTexture
{
public:
    RGles1xImplTexture()
        : mTarget(GL_TEXTURE_2D),
          mLevel(0),
          mPixels(0),
          mWrapS(GL_CLAMP),
          mWrapT(GL_CLAMP),
          mMinification(GL_NEAREST),
          mMagnification(GL_NEAREST)
    {}

    GLenum mTarget;
    GLint mLevel;
    GLint mInternalformat;
    GLsizei mWidth;
    GLsizei mHeight;
    GLint mBorder;
    GLenum mFormat;
    GLenum mType;
    GLubyte *mPixels;
    GLint mWrapS;
    GLint mWrapT;
    GLint mMinification;
    GLint mMagnification;
};

typedef std::map<GLuint, RGles1xImplTexture*> TextureList;
typedef TextureList::iterator TextureListIter;
typedef TextureList::const_iterator TextureListConstIter;

class RGles1xImplLight
{
public:
    RGles1xImplLight()
        : mSpotExponent(0.0f),
          mSpotCutoff(180.0f),
          mConstantAttenuation(1.0f),
          mLinearAttenuation(0.0f),
          mQuadraticAttenuation(0.0f),
          mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
          mDiffuse(1.0f, 1.0f, 1.0f, 1.0f),
          mSpecular(1.0f, 1.0f, 1.0f, 1.0f),
          mPosition(0.0f, 0.0f, 1.0f, 0.0f),
          mSpotDirection(0.0f, 0.0f, -1.0f, 0.0f)
    {}

    GLfloat mSpotExponent;
    GLfloat mSpotCutoff;
    GLfloat mConstantAttenuation;
    GLfloat mLinearAttenuation;
    GLfloat mQuadraticAttenuation;
    RGLColorf mAmbient;
    RGLColorf mDiffuse;
    RGLColorf mSpecular;
    RGLVectorf mPosition;
    RGLVectorf mSpotDirection;
};

class RGles1xImplMaterial
{
public:
    RGles1xImplMaterial()
        : mAmbient(0.2f, 0.2f, 0.2f, 1.0f),
          mDiffuse(0.8f, 0.8f, 0.8f, 1.0f),
          mSpecular(0.0f, 0.0f, 0.0f, 1.0f),
          mEmissive(0.0f, 0.0f, 0.0f, 1.0f)
    {}

    RGLColorf mAmbient;
    RGLColorf mDiffuse;
    RGLColorf mSpecular;
    RGLColorf mEmissive;
};

class RGles1xImplVertexData
{
public:
    RGles1xImplVertexData()
        : mSize(3),
          mPointer(0)
    {}

    GLint mSize;
    GLenum mType;
    GLsizei mStride;
    const GLvoid *mPointer;
};

class RGles1xImplBuffers
{
public:
    RGles1xImplBuffers()
        : mColor(0),
          mDepth(0),
          mStencil(0)
    {}

    RGLColorf *mColor;
    GLfloat *mDepth;
    GLfloat *mStencil;
};

class RGles1xImplFeature
{
public:
    RGles1xImplFeature()
        : mDepthTest(false),
          mVertexArray(false),
          mColorArray(false),
          mNormalArray(false),
          mTexCoordArray(false),
          mColorMaterial(false),
          mLighting(false),
          mTexture2D(false) {
        for (int i = 0; i < GL_MAX_LIGHT_UNITS; ++i) {
            mLights[i] = false;
        }
    }

    bool mDepthTest;
    bool mVertexArray;
    bool mColorArray;
    bool mNormalArray;
    bool mTexCoordArray;
    bool mColorMaterial;
    bool mLighting;
    bool mLights[GL_MAX_LIGHT_UNITS];
    bool mTexture2D;
};

class RGles1xImplFuncs
{
public:
    RGles1xImplFuncs() {
        mDepthFunc = rglFuncLess;
    }

    bool (*mDepthFunc)(const GLfloat &, const GLfloat &);
};

class RGles1xImplState
{
public:
    RGles1xImplState()
        : mClearColor(0.0f, 0.0f, 0.0f, 1.0f),
          mClearDepth(0.0f),
          mClearStencil(0.0f),
          mCurrentColor(1.0f, 1.0f, 1.0f, 1.0f),
          mCurrentNormal(0.0f, 0.0f, 1.0f),
          mViewportX(0),
          mViewportY(0),
          mViewportWidth(0),
          mViewportHeight(0),
          mWidth(0),
          mHeight(0),
          mError(GL_NO_ERROR),
          mMatrixMode(GL_PROJECTION),
          mCurrentActiveTexture(0) {
        mDepthRange[0] = 0.0f;
        mDepthRange[1] = 1.0f;

        for (int i = 0; i < GL_MAX_TEXTURE_UNITS; ++i) {
            mActiveTextures[i] = 0;
        }
        mActiveTextures[0] = 1;
    }

    RGLColorf mClearColor;
    GLfloat mClearDepth;
    GLfloat mClearStencil;
    RGLColorf mCurrentColor;
    RGLVectorf mCurrentNormal;
    RGLVectorf mCurrentTexCoord;
    GLint mViewportX;
    GLint mViewportY;
    GLint mViewportWidth;
    GLint mViewportHeight;
    GLint mWidth;
    GLint mHeight;
    GLenum mError;
    GLenum mMatrixMode;
    GLfloat mDepthRange[2];
    RGLMatrix mProjection;
    RGLMatrix mModelview;
    RGles1xImplVertexData mVertexData;
    RGles1xImplVertexData mColorData;
    RGles1xImplVertexData mNormalData;
    RGles1xImplVertexData mTexCoordData;
    RGles1xImplBuffers mBuffers;
    RGles1xImplFeature mFeature;
    RGles1xImplFuncs mFuncs;
    RGles1xImplMaterial mMaterial;
    RGles1xImplLight mLights[GL_MAX_LIGHT_UNITS];
    TextureList mTextures;
    GLuint mActiveTextures[GL_MAX_TEXTURE_UNITS];
    GLuint mCurrentActiveTexture;
    RGles1xImplTextureUnit mTextureUnits[GL_MAX_TEXTURE_UNITS];
};

class RGles1xImplPrimitive
{
private:
    RGles1xImplPrimitive(RGles1xImplPrimitive const &);
    RGles1xImplPrimitive& operator=(RGles1xImplPrimitive const &);

public:
    RGles1xImplPrimitive()
        : mCount(0),
          mPoints(0),
          mColors(0),
          mNormals(0),
          mTexCoords(0)
    {}

    GLint mMode;
    GLint mCount;
    RGLVectorf *mPoints;
    RGLColorf *mColors;
    RGLVectorf *mNormals;
    RGLVectorf *mTexCoords;
};

class RGles1xImplFragments
{
public:
    class Fragment
    {
    public:
        Fragment()
            : mDepth(0.0f),
              mCoverage(0.0f),
              mValid(false)
        {}

        RGLVector2Di mPoint;
        RGLColorf mColor;
        RGLVectorf mTexCoords;
        GLfloat mDepth;
        GLfloat mCoverage;
        bool mValid;
    };

    RGles1xImplFragments(int width, int height)
        : mFragments(width * height),
          mWidth(width)
    {}

    ~RGles1xImplFragments()
    {}

    void add(Fragment const &fragment) {
        int index = fragment.mPoint.x() + fragment.mPoint.y() * mWidth;
        mFragments[index] = fragment;
        mFragments[index].mValid = true;
    }

    int count() const {
        return mFragments.size();
    }

    Fragment *data() {
        return &mFragments[0];
    }

    const Fragment *data() const {
        return &mFragments[0];
    }

    void reset() {
        static const int count = mFragments.size();
        for (int i = 0; i < count; ++i) {
            if (mFragments[i].mValid) {
                mFragments[i] = Fragment();
            }
        }
    }

private:
    std::vector<Fragment> mFragments;
    int mWidth;
};

class RGles1xImpl: public RGles1x
{
protected:

    /* for clipping */
    enum OutCode {
        Inside = 0,
        Left = 1,
        Right = 2,
        Bottom = 4,
        Top = 8
    };

public:
    RGles1xImpl();

    /* transformations */
    virtual void loadIdentity();
    virtual void loadMatrix(const GLfloat m[16]);
    virtual void matrixMode(GLenum mode);

    virtual void scale(GLfloat sx, GLfloat sy, GLfloat sz);
    virtual void translate(GLfloat tx, GLfloat ty, GLfloat tz);
    virtual void rotate(GLfloat angle, GLfloat ax, GLfloat ay, GLfloat az);

    virtual void frustum(GLfloat leftValue, GLfloat rightValue,
                         GLfloat bottomValue, GLfloat topValue,
                         GLfloat nearValue, GLfloat farValue);
    virtual void ortho(GLfloat leftValue, GLfloat rightValue,
                       GLfloat bottomValue, GLfloat topValue,
                       GLfloat nearValue, GLfloat farValue);

    virtual void enable(GLenum cap);
    virtual void disable(GLenum cap);

    virtual void depthFunc(GLenum func);

    /* flush operations */
    virtual void flush();
    virtual void finish();

    /* retrieve color buffer */
    virtual void readPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, GLvoid *pixels, bool originTopLeft = false);

    /* drawing operations */
    virtual void normalPointer(GLenum type, GLsizei stride,
                               const GLvoid *pointer);
    virtual void colorPointer(GLint size, GLenum type,
                              GLsizei stride,
                              const GLvoid *pointer);
    virtual void vertexPointer(GLint size, GLenum type,
                               GLsizei stride, const GLvoid *pointer);
    virtual void drawArrays(GLenum mode, GLint first, GLsizei count);

    /* clear operations */
    virtual void clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

    virtual void clear(GLbitfield mask);

    /* color settings */
    virtual void color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /* light settings */
    void normal(GLfloat nx, GLfloat ny, GLfloat nz);
    void light(GLenum light, GLenum pname, const GLfloat *params);
    void material(GLenum face, GLenum pname, const GLfloat *params);

    /* textures */
    void bindTexture(GLenum target, GLuint texture);
    void genTextures(GLsizei n, GLuint *textures);
    void deleteTextures(GLsizei n, const GLuint *textures);

    void texCoordPointer(GLint size, GLenum type, GLsizei stride,
                         const GLvoid *pointer);
    void texEnv(GLenum target, GLenum pname, const GLint *params);

    void texImage2D(GLenum target, GLint level, GLint internalformat,
                    GLsizei width, GLsizei height, GLint border,
                    GLenum format, GLenum type, const GLvoid *pixels);
    void texParameter(GLenum target, GLenum pname, const GLint *params);

    void viewport(int x, int y, int width, int height);

    virtual GLenum getError() {
        return mState->mError;
    }

    void initialize(InitParam const &param, void * state);

protected:
    void drawPoint(RGles1xImplFragments &fragments,
                   RGles1xImplPrimitive const & primitive);
    void drawLine(RGles1xImplFragments &fragments,
                  RGles1xImplPrimitive const & primitive);
    void drawTriangle(RGles1xImplFragments &fragments,
                      RGles1xImplPrimitive const & primitive);

    void perVertexOperations(RGles1xImplPrimitive *primitive);
    bool enabledLighting();
    void applyLighting(RGles1xImplPrimitive *primitive, RGLColorf * colors);
    void clipAndRasterization(RGles1xImplPrimitive *primitive);
    void perFragmentOperations(RGles1xImplFragments &fragments);
    void applyTextureMapping(RGles1xImplFragments &fragments);
    OutCode computeOutCode(GLfloat x, GLfloat y,
                           GLfloat xmin, GLfloat ymin,
                           GLfloat xmax, GLfloat ymax);
    int clipLine(RGLVectorf &p1, RGLVectorf &p2);

    RGles1xImplTexture *getCurrentTexture();

    bool depthTest(const RGles1xImplFragments::Fragment &fragment);
    void nearestFilter(RGles1xImplTexture * texture,
                       GLfloat s, GLfloat t, RGLColorf & result);
    void extractRGBA(RGles1xImplTexture * texture,
                     GLint row, GLint col, RGLColorf & result);
protected:
    RGles1xImplState * mState;
};

#endif

