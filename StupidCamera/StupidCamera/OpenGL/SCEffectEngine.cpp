//
//  SCEffectEngine.cpp
//
//  Created by rayyyhuang on 2021/6/30.
//

#include "SCEffectEngine.hpp"
#include "BaseDefine.h"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"

namespace effect {

SCEffectEngine::SCEffectEngine() {
    lutFilter = std::make_shared<LutFilter>();
    smallHeadFilter = std::make_shared<SmallHeadFilter>();
    smoothFilter = std::make_shared<SmoothFilter>();
    sharpenFilter = std::make_shared<SharpenFilter>();
    currentFilters.push_back(lutFilter);
    currentFilters.push_back(smallHeadFilter);
    currentFilters.push_back(smoothFilter);
    currentFilters.push_back(sharpenFilter);
}

SCEffectEngine::~SCEffectEngine() {
    
}

void SCEffectEngine::init() {
    lutFilter->init();
    smallHeadFilter->init();
    smoothFilter->init();
    sharpenFilter->init();
}

void SCEffectEngine::release() {
    lutFilter->release();
    smallHeadFilter->release();
    smoothFilter->release();
    sharpenFilter->release();
    FrameBufferPool::getSharedInstance()->clearFrameBufferPool();
    ProgramPool::getSharedInstance()->clearProgramFromPool();
}

void SCEffectEngine::resize(int width, int height) {
    lutFilter->resize(width, height);
    smallHeadFilter->resize(width, height);
    smoothFilter->resize(width, height);
    sharpenFilter->resize(width, height);
}

void SCEffectEngine::setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer) {
    lutFilter->setInputFrameBufferAtIndex(inputFrameBuffer, 0);
}

std::shared_ptr<FrameBuffer> SCEffectEngine::render() {
    return sharpenFilter->render();
//    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
//    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
//    lutResultFrameBuffer->unlock();
//    return smallHeadFilter->render();
}

void SCEffectEngine::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    std::shared_ptr<FrameBuffer> lutResult = lutFilter->render();
    smallHeadFilter->setInputFrameBufferAtIndex(lutResult, 0);
    lutResult->unlock();
    
    std::shared_ptr<FrameBuffer> smallHeadResult = smallHeadFilter->render();
    smoothFilter->setInputFrameBufferAtIndex(smallHeadResult, 0);
    smallHeadResult->unlock();
    
    std::shared_ptr<FrameBuffer> smoothResult = smoothFilter->render();
    sharpenFilter->setInputFrameBufferAtIndex(smoothResult, 0);
    smoothResult->unlock();
    
    sharpenFilter->renderToFrameBuffer(outputFrameBuffer);
}

void SCEffectEngine::setFaceData(SCFaceData *faceData) {
    smallHeadFilter->setFaceData(faceData);
}

void SCEffectEngine::setParams(const std::map<std::string, std::map<std::string, std::string> > &params) {
    std::map<std::string, std::map<std::string, std::string> >::const_iterator it;
    for (it = params.begin(); it != params.end(); it++) {
        for (std::shared_ptr<BaseFilter> filter : currentFilters) {
            if (filter->filterType() == (*it).first) {
                filter->setParams((*it).second);
            }
        }
    }
}

}
