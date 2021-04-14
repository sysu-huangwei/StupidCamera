//
//  SCFilterBase.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCFilterBase.hpp"

SCFilterBase::SCFilterBase() {
    width = 0;
    height = 0;
    textureID = 0;
    fboID = 0;
    programID = 0;
    positionAttribute = 0;
    textureCoordinateAttribute = 0;
    
    textureIDOutside = 0;
    fboIDOutside = 0;
    isRenderToOutside = false;
}

SCFilterBase::~SCFilterBase() {
    
}

void SCFilterBase::init() {
    
}

void SCFilterBase::initWithVertexStringAndFragmentString(const char* vs, const char* fs) {
    if (programID > 0) {
        glDeleteProgram(programID);
    }
    programID = BaseGLUtils::createProgram(vs, fs);
    if (textureID == 0) {
        textureID = BaseGLUtils::createTexture2D();
    }
}

void SCFilterBase::resize(int width, int height) {
    if (this->width != width || this->height != height) {
        this->width = width;
        this->height = height;
        if (fboID > 0) {
            glDeleteFramebuffers(1, &fboID);
            fboID = 0;
        }
        if (width > 0 && height > 0) {
            fboID = BaseGLUtils::createFBO(textureID, width, height);
        }
    }
}

void SCFilterBase::release() {
    if (textureID > 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
    if (fboID > 0) {
        glDeleteFramebuffers(1, &fboID);
        fboID = 0;
    }
    if (programID > 0) {
        glDeleteProgram(programID);
        programID = 0;
    }
}

void SCFilterBase::beforeDraw() {
    if (isRenderToOutside) {
        glBindFramebuffer(GL_FRAMEBUFFER, fboIDOutside);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureIDOutside, 0);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    }
    
    glViewport(0, 0, width, height);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, imageVertices);
    
    glEnableVertexAttribArray(textureCoordinateAttribute);
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
}

void SCFilterBase::afterDraw() {
//    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
//    glDisableVertexAttribArray(positionAttribute);
//    glDisableVertexAttribArray(textureCoordinateAttribute);
}

unsigned SCFilterBase::render() {
    if (isRenderToOutside) {
        return textureIDOutside;
    } else {
        return textureID;
    }
}

void SCFilterBase::setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside) {
    this->textureIDOutside = textureIDOutside;
    this->fboIDOutside = fboIDOutside;
    isRenderToOutside = textureIDOutside != 0 && fboIDOutside != 0;
}
