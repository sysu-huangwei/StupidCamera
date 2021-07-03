//
//  FrameBuffer.hpp
//
//  Created by rayyy on 2021/7/1.
//

#ifndef FrameBuffer_hpp
#define FrameBuffer_hpp

#include "SCBaseDefine.h"

#if PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif PLATFORM_IOS
#define GLES_SILENCE_DEPRECATION 1
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

class FrameBuffer {
public:
    
    void activeFrameBuffer();
    
    GLuint getTextureID() const { return textureID; }
    
    GLuint getFrameBufferID() const { return frameBufferID; }
    
private:
    int width = 0, height = 0;
    GLuint textureID = 0, frameBufferID = 0;
    bool isOnlyTexture = false;
    bool isNeedReleaseTexture = false, isNeedReleaseFrameBuffer = false;

    friend class FrameBufferPool;
    void init(int width, int height, bool isOnlyTexture = false, GLuint textureID = 0, GLuint frameBufferID = 0);
    void release();
    int referenceCount = 0;
    void lock();
    void unlock();
    
    void createTexture();
    void createAndBindFrameBuffer();
};

#endif /* FrameBuffer_hpp */
