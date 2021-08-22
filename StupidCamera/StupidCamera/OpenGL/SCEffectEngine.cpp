//
//  SCEffectEngine.cpp
//
//  Created by rayyyhuang on 2021/6/30.
//

#include "SCEffectEngine.hpp"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"

SCEffectEngine::SCEffectEngine() {
    lutFilter = new SCFilterLut();
    smallHeadFilter = new SCFilterSmallHead();
    smoothFilter = new SCFilterSmooth();
    currentFilters.push_back(lutFilter);
    currentFilters.push_back(smallHeadFilter);
    currentFilters.push_back(smoothFilter);
}

SCEffectEngine::~SCEffectEngine() {
    SAFE_DELETE(lutFilter);
    SAFE_DELETE(smallHeadFilter);
    SAFE_DELETE(smoothFilter);
}

/// 初始化，必须在GL线程
void SCEffectEngine::init() {
    lutFilter->init();
    smallHeadFilter->init();
    smoothFilter->init();
}

/// 释放资源，必须在GL线程
void SCEffectEngine::release() {
    lutFilter->release();
    smallHeadFilter->release();
    smoothFilter->release();
    FrameBufferPool::getSharedInstance()->clearFrameBufferPool();
    ProgramPool::getSharedInstance()->clearProgramFromPool();
}

/// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
/// @param width 宽
/// @param height 高
void SCEffectEngine::resize(int width, int height) {
    lutFilter->resize(width, height);
    smallHeadFilter->resize(width, height);
    smoothFilter->resize(width, height);
}

/// 设置输入图像的纹理ID
/// @param inputFrameBuffer 输入图像的FBO
void SCEffectEngine::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
//    lutFilter->setInputFrameBuffer(inputFrameBuffer);
    smoothFilter->setInputFrameBuffer(inputFrameBuffer);
}

FrameBuffer *SCEffectEngine::render() {
    return smoothFilter->render();
//    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
//    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
//    lutResultFrameBuffer->unlock();
//    return smallHeadFilter->render();
}

void SCEffectEngine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    smoothFilter->renderToFrameBuffer(outputFrameBuffer);
//    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
//    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
//    lutResultFrameBuffer->unlock();
//    smallHeadFilter->renderToFrameBuffer(outputFrameBuffer);
}

/// 设置人脸数据
/// @param faceData 人脸数据
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
