//
//  SCFilterBackgroundLine.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/6/11.
//

#include "SCFilterBackgroundLine.hpp"

SCFilterBackgroundLine::SCFilterBackgroundLine():SCFilterBase() {
    copyFilter = new SCFilterCopy();
    lineFilter = new SCFilterLine();
}

SCFilterBackgroundLine::~SCFilterBackgroundLine() {
    SAFE_DELETE(copyFilter);
    SAFE_DELETE(lineFilter);
}

void SCFilterBackgroundLine::init() {
    copyFilter->init();
    lineFilter->init();
}

void SCFilterBackgroundLine::release() {
    copyFilter->release();
    lineFilter->release();
}

void SCFilterBackgroundLine::resize(int width, int height) {
    copyFilter->resize(width, height);
    lineFilter->resize(width, height);
}

void SCFilterBackgroundLine::setSrcTextureID(unsigned srcTextureID) {
    copyFilter->setSrcTextureID(srcTextureID);
}

unsigned SCFilterBackgroundLine::render() {
    GLuint backgroundTextureID = copyFilter->render();
    lineFilter->setSrcTextureID(backgroundTextureID);
    return lineFilter->render();
}

void SCFilterBackgroundLine::setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside) {
    copyFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
    lineFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
}

void SCFilterBackgroundLine::setLines(float *lines, int linesCount) {
    lineFilter->setLines(lines, linesCount);
}
