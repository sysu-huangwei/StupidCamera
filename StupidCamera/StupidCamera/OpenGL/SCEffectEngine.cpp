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

/// 初始化，必须在GL线程
void SCEffectEngine::init() {
    lutFilter->init();
    smallHeadFilter->init();
    smoothFilter->init();
    sharpenFilter->init();
}

/// 释放资源，必须在GL线程
void SCEffectEngine::release() {
    lutFilter->release();
    smallHeadFilter->release();
    smoothFilter->release();
    sharpenFilter->release();
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
    sharpenFilter->resize(width, height);
}

/// 设置输入图像的纹理ID
/// @param inputFrameBuffer 输入图像的FBO
void SCEffectEngine::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
//    lutFilter->setInputFrameBuffer(inputFrameBuffer);
    sharpenFilter->setInputFrameBuffer(inputFrameBuffer);
}

FrameBuffer *SCEffectEngine::render() {
    return sharpenFilter->render();
//    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
//    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
//    lutResultFrameBuffer->unlock();
//    return smallHeadFilter->render();
}

void SCEffectEngine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    sharpenFilter->renderToFrameBuffer(outputFrameBuffer);
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
