//
//  SCEffectEngine.cpp
//
//  Created by rayyyhuang on 2021/6/30.
//

#include "SCEffectEngine.hpp"
#include "BaseDefine.h"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"

SCEffectEngine::SCEffectEngine() {
    lutFilter = new SCFilterLut();
    smallHeadFilter = new SCFilterSmallHead();
    smoothFilter = new SCFilterSmooth();
    sharpenFilter = new SCFilterSharpenUSM();
    currentFilters.push_back(lutFilter);
    currentFilters.push_back(smallHeadFilter);
    currentFilters.push_back(smoothFilter);
    currentFilters.push_back(sharpenFilter);
}

SCEffectEngine::~SCEffectEngine() {
    SAFE_DELETE(lutFilter);
    SAFE_DELETE(smallHeadFilter);
    SAFE_DELETE(smoothFilter);
    SAFE_DELETE(sharpenFilter);
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

void SCEffectEngine::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    lutFilter->setInputFrameBuffer(inputFrameBuffer);
}

FrameBuffer *SCEffectEngine::render() {
    return sharpenFilter->render();
//    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
//    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
//    lutResultFrameBuffer->unlock();
//    return smallHeadFilter->render();
}

void SCEffectEngine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    FrameBuffer *lutResult = lutFilter->render();
    smallHeadFilter->setInputFrameBuffer(lutResult);
    lutResult->unlock();
    
    FrameBuffer *smallHeadResult = smallHeadFilter->render();
    smoothFilter->setInputFrameBuffer(smallHeadResult);
    smallHeadResult->unlock();
    
    FrameBuffer *smoothResult = smoothFilter->render();
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
        for (SCFilterBase *filter : currentFilters) {
            if (filter->filterName() == (*it).first) {
                filter->setParams((*it).second);
            }
        }
    }
}
