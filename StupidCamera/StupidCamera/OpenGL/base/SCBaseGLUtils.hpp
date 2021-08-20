//
//  SCBaseGLUtils.hpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#ifndef SCBaseGLUtils_hpp
#define SCBaseGLUtils_hpp

#include "SCBaseDefine.h"
#include "SCBaseLog.h"

#if PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif PLATFORM_IOS
#define GLES_SILENCE_DEPRECATION 1
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif


class BaseGLUtils {
public:
    
    static unsigned char *loadImageFileToRGBAPixels(const char *filePath, int &outWidth, int &outHeight);
       
    static GLuint loadImageFileToTexture(const char *filePath, int &outWidth, int &outHeight);
    
private:
    
    static char *loadImageFileToMemory(const char *filePath, unsigned long &outDataSize);
    
    static GLuint loadPixelsToTexture(const unsigned char *data, int width, int height, GLenum glFormat = GL_RGBA);
    
    static unsigned char *loadMemoryToRGBAPixels(const char *memoryData, unsigned long dataSize, int &outWidth, int &outHeight);
    
};




#endif /* SCBaseGLUtils_hpp */
