//
//  BackgroundPointFilter.cpp
//
//  Created by rayyyhuang on 2021/6/15.
//

#include "BackgroundPointFilter.hpp"

namespace effect {

void BackgroundPointFilter::init() {
    copyFilter.init();
    pointFilter.init();
}

void BackgroundPointFilter::release() {
    copyFilter.release();
    pointFilter.release();
}

void BackgroundPointFilter::setOutputSize(int outputWidth, int outputHeight) {
    copyFilter.setOutputSize(outputWidth, outputHeight);
    pointFilter.setOutputSize(outputWidth, outputHeight);
}

void BackgroundPointFilter::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    copyFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
    pointFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
}

void BackgroundPointFilter::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    pointFilter.renderToFrameBuffer(outputFrameBuffer);
}

void BackgroundPointFilter::setPoints(std::vector<BasePoint> points) {
    pointFilter.setPoints(points);
}

}
