//
//  SCBaseGLUtils.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "SCBaseGLUtils.hpp"
#include <stdio.h>
#include <cstring>
#ifdef PLATFORM_IOS
#include "FileUtilsForIOS.h"
#endif

unsigned char *BaseGLUtils::loadImageFileToRGBAPixels(const char *filePath, int &outWidth, int &outHeight) {
    outWidth = 0;
    outHeight = 0;
    
    if (filePath == NULL || strcmp(filePath, "") == 0) {
        LOGE("ERROR: loadImageFileToRGBAPixels: filePath = NULL");
        return NULL;
    }
    
    unsigned long dataSize;
    char *memoryData = (char *) loadImageFileToMemory(filePath, dataSize);
    if (memoryData == NULL || dataSize == 0) {
        LOGE("ERROR: loadImageFileToRGBAPixels: loadImageFileToMemory failed: filePath = %s", filePath);
        return NULL;
    }
    
    unsigned char *data = loadMemoryToRGBAPixels(memoryData, dataSize, outWidth, outHeight);
    
    SAFE_DELETE_ARRAY(memoryData);
    
    if (data == NULL || outWidth == 0 || outHeight == 0) {
        LOGE("ERROR: loadImageFileToRGBAPixels: loadMemoryToRGBAPixels failed: filePath = %s", filePath);
        return NULL;
    }
    
    return data;
}

GLuint BaseGLUtils::loadImageFileToTexture(const char *filePath, int &outWidth, int &outHeight) {
    outWidth = 0;
    outHeight = 0;
    
    if (filePath == NULL || strcmp(filePath, "") == 0) {
        LOGE("ERROR: loadImageFileToTexture: filePath = NULL");
        return 0;
    }
    
    unsigned char *data = loadImageFileToRGBAPixels(filePath, outWidth, outHeight);
    if (data == NULL || outHeight * outHeight <= 0) {
        LOGE("ERROR: loadImageFileToTexture failed to load image: filePath: %s, pData = %p, w * h: %d * %d", filePath, data, outHeight, outHeight);
        return 0;
    }
    
    GLuint result = loadPixelsToTexture(data, outWidth, outHeight, GL_RGBA);
    SAFE_DELETE_ARRAY(data);
    
    return result;
}



char *BaseGLUtils::loadImageFileToMemory(const char *filePath, unsigned long &outDataSize) {
    char *data = NULL;
    FILE *file = fopen(filePath, "r");
    if (file) {
        // 先读取大小
        fseek(file,0,SEEK_END);
        long length = ftell(file);
        fseek(file,0,SEEK_SET);
        
        if (length > 0) {
            data = new char[length + 1];
            memset(data, 0, length + 1);
            fread(data, length, 1, file);
            outDataSize = length;
        } else {
            LOGE("ERROR: loadImageFileToMemory file size < 0: %ld", length);
        }
        
        fclose(file);
    } else {
        LOGE("ERROR: loadImageFileToMemory failed to open file, filePath = %s", filePath);
    }
    return data;
}


GLuint BaseGLUtils::loadPixelsToTexture(const unsigned char *data, int width, int height, GLenum glFormat) {
    GLuint textures;
    glGenTextures(1, &textures);
    if (textures != 0) {
        glBindTexture(GL_TEXTURE_2D, textures);
        if (glFormat == GL_LUMINANCE) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
        }
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return textures;
    } else {
        LOGE("ERROR: loadRGBAPixelsToTexture failed to glGenTextures");
        return 0;
    }
}

unsigned char *BaseGLUtils::loadMemoryToRGBAPixels(const char *memoryData, unsigned long dataSize, int &outWidth, int &outHeight) {
#ifdef PLATFORM_IOS
    return loadMemoryToRGBAPixelsForIOS(memoryData, dataSize, outWidth, outHeight);
#endif
}
