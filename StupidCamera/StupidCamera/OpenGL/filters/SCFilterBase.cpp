//
//  SCFilterBase.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "SCFilterBase.hpp"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"
#include "SCBaseGLUtils.hpp"

namespace effect {

void SCFilterBase::init() {
    
}

void SCFilterBase::initWithVertexStringAndFragmentString(const char* vertexShaderName, const char* fragmentShaderName) {
    program = ProgramPool::getSharedInstance()->fetchProgramFromPool(BaseGLUtils::getVertexShaderSourceByName(vertexShaderName),
                                                                     BaseGLUtils::getFragmengShaderSourceByName(fragmentShaderName));
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
    if (!enableRender) {
        return inputFrameBuffer;
    }
    FrameBuffer *outputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(width, height);
    renderToFrameBuffer(outputFrameBuffer);
    return outputFrameBuffer;
}

void SCFilterBase::setEnableRender(bool enableRender) {
    this->enableRender = enableRender;
}

void SCFilterBase::setParams(const std::map<std::string, std::string> &param) {
    
}

}
