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
    facePointFilter = std::make_shared<FacePointFilter>();
    lineFilter = std::make_shared<BackgroundLineFilter>();
    currentFilters.push_back(lutFilter);
    currentFilters.push_back(smallHeadFilter);
    currentFilters.push_back(smoothFilter);
    currentFilters.push_back(sharpenFilter);
    currentFilters.push_back(facePointFilter);
    currentFilters.push_back(lineFilter);
}

SCEffectEngine::~SCEffectEngine() {
    
}

void SCEffectEngine::init() {
    lutFilter->init();
    smallHeadFilter->init();
    smoothFilter->init();
    sharpenFilter->init();
    facePointFilter->init();
    lineFilter->init();
}

void SCEffectEngine::release() {
    lutFilter->release();
    smallHeadFilter->release();
    smoothFilter->release();
    sharpenFilter->release();
    facePointFilter->release();
    lineFilter->release();
    FrameBufferPool::getSharedInstance()->clearFrameBufferPool();
    ProgramPool::getSharedInstance()->clearProgramFromPool();
}

void SCEffectEngine::resize(int width, int height) {
    lutFilter->setOutputSize(width, height);
    smallHeadFilter->setOutputSize(width, height);
    smoothFilter->setOutputSize(width, height);
    sharpenFilter->setOutputSize(width, height);
    facePointFilter->setOutputSize(width, height);
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
    
    std::shared_ptr<FrameBuffer> sharpenResult = sharpenFilter->render();
    facePointFilter->setInputFrameBufferAtIndex(sharpenResult);
    sharpenResult->unlock();
    
    std::shared_ptr<FrameBuffer> pointResult = facePointFilter->render();
    lineFilter->setInputFrameBufferAtIndex(pointResult);
    pointResult->unlock();
    
    lineFilter->renderToFrameBuffer(outputFrameBuffer);
}

void SCEffectEngine::setFaceData(std::shared_ptr<FaceData> faceData) {
    smallHeadFilter->setFaceData(faceData);
    facePointFilter->setFaceData(faceData);
    if (faceData->faceCount > 0) {
        std::vector<BaseLine> lines;
        BasePoint topLeft, topRight, bottomLeft, bottomRight;
        topLeft.x = faceData->faces[0].faceRect.x;
        topLeft.y = faceData->faces[0].faceRect.y;
        topRight.x = faceData->faces[0].faceRect.x + faceData->faces[0].faceRect.width;
        topRight.y = faceData->faces[0].faceRect.y;
        bottomLeft.x = faceData->faces[0].faceRect.x;
        bottomLeft.y = faceData->faces[0].faceRect.y + faceData->faces[0].faceRect.height;
        bottomRight.x = faceData->faces[0].faceRect.x + faceData->faces[0].faceRect.width;
        bottomRight.y = faceData->faces[0].faceRect.y + faceData->faces[0].faceRect.height;
        BaseLine leftLight, topLine, rightLine, bottomLine;
        leftLight.p0 = topLeft;
        leftLight.p1 = bottomLeft;
        topLine.p0 = topLeft;
        topLine.p1 = topRight;
        rightLine.p0 = topRight;
        rightLine.p1 = bottomRight;
        bottomLine.p0 = bottomLeft;
        bottomLine.p1 = bottomRight;
        lines.push_back(leftLight);
        lines.push_back(topLine);
        lines.push_back(rightLine);
        lines.push_back(bottomLine);
        
        lineFilter->setLines(lines);
    }
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
