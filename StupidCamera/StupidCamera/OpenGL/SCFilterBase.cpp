//
//  SCFilterBase.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCFilterBase.hpp"
#include "FrameBufferPool.hpp"

SCFilterBase::SCFilterBase() {
    programID = 0;
    positionAttribute = 0;
    textureCoordinateAttribute = 0;
}

SCFilterBase::~SCFilterBase() {
    delete frameBuffer;
}

void SCFilterBase::init() {
    
}

void SCFilterBase::initWithVertexStringAndFragmentString(const char* vs, const char* fs) {
    if (programID > 0) {
        glDeleteProgram(programID);
    }
    programID = BaseGLUtils::createProgram(vs, fs);
}

void SCFilterBase::resize(int width, int height) {
    if (!frameBuffer) {
        frameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(width, height);
    }
}

void SCFilterBase::release() {
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(frameBuffer);
    if (programID > 0) {
        glDeleteProgram(programID);
        programID = 0;
    }
}

void SCFilterBase::setSrcTextureID(unsigned srcTextureID) {
    this->srcTextureID = srcTextureID;
}

void SCFilterBase::beforeDraw() {
    frameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, imageVertices);
    
    glEnableVertexAttribArray(textureCoordinateAttribute);
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
}

void SCFilterBase::afterDraw() {
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    //    glDisableVertexAttribArray(positionAttribute);
    //    glDisableVertexAttribArray(textureCoordinateAttribute);
}

FrameBuffer *SCFilterBase::render() {
    return frameBuffer;
}

void SCFilterBase::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    
}
