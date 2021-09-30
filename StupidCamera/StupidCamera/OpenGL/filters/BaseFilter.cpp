//
//  BaseFilter.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "BaseFilter.hpp"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"
#include "SCBaseGLUtils.hpp"

namespace effect {

void BaseFilter::init() {
    
}

void BaseFilter::initWithVertexStringAndFragmentString(const char* vertexShaderName, const char* fragmentShaderName) {
    program = ProgramPool::getSharedInstance()->fetchProgramFromPool(BaseGLUtils::getVertexShaderSourceByName(vertexShaderName),
                                                                     BaseGLUtils::getFragmengShaderSourceByName(fragmentShaderName));
}

void BaseFilter::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

void BaseFilter::release() {
    
}

void BaseFilter::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    if (inputFrameBuffers.empty()) {
        firstInputWidth = inputFrameBuffer->getWidth();
        firstInputHeight = inputFrameBuffer->getHeight();
    }
    inputFrameBuffer->lock();
    inputFrameBuffers.push_back(inputFrameBuffer);
    inputFrameBufferIndices.push_back(index);
}

std::shared_ptr<FrameBuffer> BaseFilter::render() {
    // 如果当前滤镜没有外部指定渲染尺寸，那么就直接使用第一个输入的FBO的尺寸
    if (width == 0 || height == 0) {
        width = firstInputWidth;
        height = firstInputHeight;
    }
    
    std::shared_ptr<FrameBuffer> outputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(width, height);
    if (isNeedRender()) {
        renderToFrameBuffer(outputFrameBuffer);
    }
    return outputFrameBuffer;
}

void BaseFilter::setEnableRender(bool enableRender) {
    this->enableRender = enableRender;
}

bool BaseFilter::isAllInputReady() {
    return inputFrameBuffers.size() == 1;
}

bool BaseFilter::isNeedRender() {
    return isAllInputReady() && enableRender;
}

void BaseFilter::setParams(const std::map<std::string, std::string> &param) {
    
}

void BaseFilter::unlockAndClearAllInputFrameBuffers() {
    for (size_t i= 0; i < inputFrameBuffers.size(); i++) {
        inputFrameBuffers[i]->unlock();
    }
    inputFrameBuffers.clear();
    inputFrameBufferIndices.clear();
}

}