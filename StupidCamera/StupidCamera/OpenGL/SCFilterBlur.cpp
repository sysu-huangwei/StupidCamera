//
//  SCFilterBlur.cpp
//
//  Created by rayyy on 2021/8/16.
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
    scaleWH(width, height);
    blurFilterH.resize(width, height);
    blurFilterV.resize(width, height);
}

void SCFilterBlur::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    blurFilterH.setInputFrameBuffer(inputFrameBuffer);
}

void SCFilterBlur::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    FrameBuffer *resultFrameBufferInternal = blurFilterH.render();
    blurFilterV.setInputFrameBuffer(resultFrameBufferInternal);
    blurFilterV.renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBlur::setAlpha(float alpha) {
    blurFilterH.setAlpha(alpha);
    blurFilterV.setAlpha(alpha);
}

void SCFilterBlur::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_BlurAlpha) {
            setAlpha(std::stof((*it).second));
        }
    }
}


void SCFilterBlur::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}
