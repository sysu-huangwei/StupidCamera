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
    lutFilter = std::make_shared<SCFilterLut>();
    smallHeadFilter = std::make_shared<SCFilterSmallHead>();
    smoothFilter = std::make_shared<SCFilterSmooth>();
    sharpenFilter = std::make_shared<SCFilterSharpenUSM>();
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
    lutFilter->setInputFrameBuffer(inputFrameBuffer);
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
    smallHeadFilter->setInputFrameBuffer(lutResult);
    lutResult->unlock();
    
    std::shared_ptr<FrameBuffer> smallHeadResult = smallHeadFilter->render();
    smoothFilter->setInputFrameBuffer(smallHeadResult);
    smallHeadResult->unlock();
    
    std::shared_ptr<FrameBuffer> smoothResult = smoothFilter->render();
    sharpenFilter->setInputFrameBuffer(smoothResult);
    smoothResult->unlock();
    
    sharpenFilter->renderToFrameBuffer(outputFrameBuffer);
}

void SCEffectEngine::setFaceData(SCFaceData *faceData) {
    smallHeadFilter->setFaceData(faceData);
}

void SCEffectEngine::setParams(const std::map<std::string, std::map<std::string, std::string> > &params) {
    std::map<std::string, std::map<std::string, std::string> >::const_iterator it;
    for (it = params.begin(); it != params.end(); it++) {
        for (std::shared_ptr<SCFilterBase> filter : currentFilters) {
            if (filter->filterName() == (*it).first) {
                filter->setParams((*it).second);
            }
        }
    }
}

}
