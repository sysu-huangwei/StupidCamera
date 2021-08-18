//
//  FrameBuffer.cpp
//
//  Created by rayyy on 2021/7/1.
//

#include "FrameBuffer.hpp"
#include "SCBaseLog.h"
#include "FrameBufferPool.hpp"

void FrameBuffer::init(int width, int height, bool isOnlyTexture, GLuint textureID, GLuint frameBufferID) {
    this->width = width;
    this->height = height;
    this->isOnlyTexture = isOnlyTexture;
    
    if (textureID == 0) {
        createTexture();
    } else {
        this->textureID = textureID;
        isNeedReleaseTexture = false;
    }
    
    if (!isOnlyTexture) {
        if (frameBufferID == 0) {
            createAndBindFrameBuffer();
        } else {
            this->frameBufferID = frameBufferID;
            isNeedReleaseFrameBuffer = false;
        }
    }
}

void FrameBuffer::release() {
    if (textureID != 0 && isNeedReleaseTexture) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    if (frameBufferID != 0 && isNeedReleaseFrameBuffer) {
        glDeleteFramebuffers(1, &frameBufferID);
        frameBufferID = 0;
    }
}

void FrameBuffer::activeFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    glViewport(0, 0, width, height);
}

void FrameBuffer::createTexture() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    isNeedReleaseTexture = true;
}

void FrameBuffer::createAndBindFrameBuffer() {
    glGenFramebuffers(1, &frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    isNeedReleaseTexture = true;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOGE("ERROR: Incomplete filter FBO: %d; framebuffer size = %d, %d, "
             "glerror = %d, isTexture = %d, isFramebuffer = %d.",
             status, width, height,
             glGetError(), glIsTexture(textureID), glIsFramebuffer(frameBufferID));
    }
}

void FrameBuffer::lock() {
    if (enableReferenceCount) {
        referenceCount++;
    }
}

void FrameBuffer::unlock() {
    if (enableReferenceCount) {
        if (referenceCount > 0) {
            referenceCount--;
            if (referenceCount == 0) {
                FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(this);
            }
        } else {
            LOGE("Error: FrameBuffer::unlock()  referenceCount < 0");
        }
    }
}

void FrameBuffer::setEnableReferenceCount(bool enableReferenceCount) {
    this->enableReferenceCount = enableReferenceCount;
}
