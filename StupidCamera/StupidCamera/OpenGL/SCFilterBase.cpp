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
    
}

void SCFilterBase::init() {
    
}

void SCFilterBase::initWithVertexStringAndFragmentString(const char* vs, const char* fs) {
    program = ProgramPool::getSharedInstance()->fetchProgramFromPool(vs, fs);
}

void SCFilterBase::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

void SCFilterBase::release() {
    
}

void SCFilterBase::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    this->inputFrameBuffer = inputFrameBuffer;
    this->inputFrameBuffer->lock();
}

FrameBuffer *SCFilterBase::render() {
    FrameBuffer *outputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(width, height);
    renderToFrameBuffer(outputFrameBuffer);
    return outputFrameBuffer;
}

void SCFilterBase::setParams(const std::map<std::string, std::string> &param) {
    
}
