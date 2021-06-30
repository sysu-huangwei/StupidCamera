//
//  SCEffectEngine.cpp
//
//  Created by rayyy on 2021/6/30.
//

#include "SCEffectEngine.hpp"

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
    lutFilter->init();
    smallHeadFilter->init();
}

/// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
/// @param width 宽
/// @param height 高
void SCEffectEngine::resize(int width, int height) {
    lutFilter->resize(width, height);
    smallHeadFilter->resize(width, height);
}

/// 设置输入图像的纹理ID
/// @param srcTextureID 输入图像的纹理ID
void SCEffectEngine::setSrcTextureID(unsigned srcTextureID) {
    lutFilter->setSrcTextureID(srcTextureID);
}

unsigned SCEffectEngine::render() {
    unsigned lutResultTexture = lutFilter->render();
    smallHeadFilter->setSrcTextureID(lutResultTexture);
    return smallHeadFilter->render();
}

/// 设置外部的纹理ID和FBO，如果都设置了>0的合法值，渲染的时候会绘制到这个buffer上，如果需要重新绘制到内置的FBO，设置0, 0
/// @param textureIDOutside 外部的纹理ID
/// @param fboIDOutside 外部的FBO
void SCEffectEngine::setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside) {
    smallHeadFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
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
