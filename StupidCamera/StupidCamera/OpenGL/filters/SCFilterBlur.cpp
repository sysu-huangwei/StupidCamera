//
//  SCFilterBlur.cpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#include "SCFilterBlur.hpp"


void SCFilterBlur::init() {
    blurFilterH.init();
    blurFilterV.init();
}

void SCFilterBlur::release() {
    blurFilterH.release();
    blurFilterV.release();
}

void SCFilterBlur::resize(int width, int height) {
    SCFilterBase::resize(width, height);
    scaleWH(width, height);
    blurFilterH.resize(width, height);
    blurFilterV.resize(width, height);
    blurFilterH.setOffset(1.0f / (float)width, 0);
    blurFilterV.setOffset(0, 1.0f / (float)height);
}

void SCFilterBlur::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    blurFilterH.setInputFrameBuffer(inputFrameBuffer);
}


//FrameBuffer *SCFilterBlur::render() {
//    FrameBuffer *resultFrameBufferInternal = blurFilterH.render();
//    blurFilterV.setInputFrameBuffer(resultFrameBufferInternal);
//    blurFilterV.renderToFrameBuffer(outputFrameBuffer);
//    resultFrameBufferInternal->unlock();
//}

void SCFilterBlur::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    FrameBuffer *resultFrameBufferInternal = blurFilterH.render();
    blurFilterV.setInputFrameBuffer(resultFrameBufferInternal);
    blurFilterV.renderToFrameBuffer(outputFrameBuffer);
    resultFrameBufferInternal->unlock();
}

void SCFilterBlur::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}
