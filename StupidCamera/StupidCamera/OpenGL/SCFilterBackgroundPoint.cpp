//
//  SCFilterBackgroundPoint.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/6/15.
//

#include "SCFilterBackgroundPoint.hpp"

SCFilterBackgroundPoint::SCFilterBackgroundPoint():SCFilterBase() {
    copyFilter = new SCFilterCopy();
    pointFilter = new SCFilterPoint();
}

SCFilterBackgroundPoint::~SCFilterBackgroundPoint() {
    SAFE_DELETE(copyFilter);
    SAFE_DELETE(pointFilter);
}

void SCFilterBackgroundPoint::init() {
    copyFilter->init();
    pointFilter->init();
}

void SCFilterBackgroundPoint::release() {
    copyFilter->release();
    pointFilter->release();
}

void SCFilterBackgroundPoint::resize(int width, int height) {
    copyFilter->resize(width, height);
    pointFilter->resize(width, height);
}

void SCFilterBackgroundPoint::setSrcTextureID(unsigned srcTextureID) {
    copyFilter->setSrcTextureID(srcTextureID);
    pointFilter->setSrcTextureID(srcTextureID);
}

void SCFilterBackgroundPoint::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    copyFilter->renderToFrameBuffer(outputFrameBuffer);
    pointFilter->renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBackgroundPoint::setPoints(float *points, int pointsCount) {
    pointFilter->setPoints(points, pointsCount);
}
