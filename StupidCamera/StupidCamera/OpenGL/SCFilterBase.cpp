//
//  SCFilterBase.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCFilterBase.hpp"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"

SCFilterBase::SCFilterBase() {
    
}

SCFilterBase::~SCFilterBase() {
    delete frameBuffer;
}

void SCFilterBase::init() {
    
}

void SCFilterBase::initWithVertexStringAndFragmentString(const char* vs, const char* fs) {
    program = ProgramPool::getSharedInstance()->fetchProgramFromPool(vs, fs);
}

void SCFilterBase::resize(int width, int height) {
    if (!frameBuffer) {
        frameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(width, height);
    }
}

void SCFilterBase::release() {
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(frameBuffer);
}

void SCFilterBase::setSrcTextureID(unsigned srcTextureID) {
    this->srcTextureID = srcTextureID;
}

void SCFilterBase::beforeDraw() {
    frameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
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
