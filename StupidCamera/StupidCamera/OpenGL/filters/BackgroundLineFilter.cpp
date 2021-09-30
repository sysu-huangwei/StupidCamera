//
//  BackgroundLineFilter.cpp
//
//  Created by rayyyhuang on 2021/6/11.
//

#include "BackgroundLineFilter.hpp"

namespace effect {

void BackgroundLineFilter::init() {
    copyFilter.init();
    lineFilter.init();
}

void BackgroundLineFilter::release() {
    copyFilter.release();
    lineFilter.release();
}

void BackgroundLineFilter::setOutputSize(int outputWidth, int outputHeight) {
    copyFilter.setOutputSize(outputWidth, outputHeight);
    lineFilter.setOutputSize(outputWidth, outputHeight);
}

void BackgroundLineFilter::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    copyFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
    lineFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
}

void BackgroundLineFilter::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    lineFilter.renderToFrameBuffer(outputFrameBuffer);
}

void BackgroundLineFilter::setLines(std::vector<BaseLine> lines) {
    lineFilter.setLines(lines);
}

}
