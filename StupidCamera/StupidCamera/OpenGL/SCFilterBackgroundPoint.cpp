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

unsigned SCFilterBackgroundPoint::render() {
    copyFilter->render();
    return pointFilter->render();
}

void SCFilterBackgroundPoint::setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside) {
    copyFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
    pointFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
}

void SCFilterBackgroundPoint::setPoints(float *points, int pointsCount, float r, float g, float b) {
    pointFilter->setPoints(points, pointsCount, r, g, b);
}
