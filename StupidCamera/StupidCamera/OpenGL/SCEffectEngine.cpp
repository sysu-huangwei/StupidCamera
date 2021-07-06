//
//  SCEffectEngine.cpp
//
//  Created by rayyy on 2021/6/30.
//

#include "SCEffectEngine.hpp"
#include "FrameBufferPool.hpp"
#include "ProgramPool.hpp"

SCEffectEngine::SCEffectEngine() {
    lutFilter = new SCFilterLut();
    smallHeadFilter = new SCFilterSmallHead();
}

SCEffectEngine::~SCEffectEngine() {
    SAFE_DELETE(lutFilter);
    SAFE_DELETE(smallHeadFilter);
}

/// 初始化，必须在GL线程
void SCEffectEngine::init() {
    lutFilter->init();
    smallHeadFilter->init();
}

/// 释放资源，必须在GL线程
void SCEffectEngine::release() {
    lutFilter->release();
    smallHeadFilter->release();
    FrameBufferPool::getSharedInstance()->clearFrameBufferPool();
    ProgramPool::getSharedInstance()->clearProgramFromPool();
}

/// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
/// @param width 宽
/// @param height 高
void SCEffectEngine::resize(int width, int height) {
    lutFilter->resize(width, height);
    smallHeadFilter->resize(width, height);
}

/// 设置输入图像的纹理ID
/// @param inputFrameBuffer 输入图像的FBO
void SCEffectEngine::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    lutFilter->setInputFrameBuffer(inputFrameBuffer);
}

FrameBuffer *SCEffectEngine::render() {
    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
    return smallHeadFilter->render();
}

/// 设置人脸数据
/// @param faceData 人脸数据
void SCEffectEngine::setFaceData(SCFaceData *faceData) {
    smallHeadFilter->setFaceData(faceData);
}

/// 替换Lut图，切换滤镜用
/// @param path LUT图的路径
void SCEffectEngine::replaceLutImagePath(const char *path) {
    lutFilter->setLutImagePath(path);
}

void SCEffectEngine::setLutDegree(float degree) {
    lutFilter->setAlpha(degree);
}

void SCEffectEngine::setSmallHeadDegree(float degree) {
    smallHeadFilter->setSmallHeadDegree(degree);
}

void SCEffectEngine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    FrameBuffer *lutResultFrameBuffer = lutFilter->render();
    smallHeadFilter->setInputFrameBuffer(lutResultFrameBuffer);
    smallHeadFilter->renderToFrameBuffer(outputFrameBuffer);
}
