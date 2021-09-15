//
//  SCFilterBackgroundLine.cpp
//
//  Created by rayyyhuang on 2021/6/11.
//

#include "SCFilterBackgroundLine.hpp"

namespace effect {

void SCFilterBackgroundLine::init() {
    copyFilter.init();
    lineFilter.init();
}

void SCFilterBackgroundLine::release() {
    copyFilter.release();
    lineFilter.release();
}

void SCFilterBackgroundLine::resize(int width, int height) {
    copyFilter.resize(width, height);
    lineFilter.resize(width, height);
}

void SCFilterBackgroundLine::setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer) {
    copyFilter.setInputFrameBuffer(inputFrameBuffer);
    lineFilter.setInputFrameBuffer(inputFrameBuffer);
}

void SCFilterBackgroundLine::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    lineFilter.renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBackgroundLine::setLines(std::vector<BaseLine> lines) {
    lineFilter.setLines(lines);
}

}
