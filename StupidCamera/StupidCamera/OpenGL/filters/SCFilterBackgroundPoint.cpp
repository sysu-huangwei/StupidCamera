//
//  SCFilterBackgroundPoint.cpp
//
//  Created by rayyyhuang on 2021/6/15.
//

#include "SCFilterBackgroundPoint.hpp"

namespace effect {

void SCFilterBackgroundPoint::init() {
    copyFilter.init();
    pointFilter.init();
}

void SCFilterBackgroundPoint::release() {
    copyFilter.release();
    pointFilter.release();
}

void SCFilterBackgroundPoint::resize(int width, int height) {
    copyFilter.resize(width, height);
    pointFilter.resize(width, height);
}

void SCFilterBackgroundPoint::setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer) {
    copyFilter.setInputFrameBuffer(inputFrameBuffer);
    pointFilter.setInputFrameBuffer(inputFrameBuffer);
}

void SCFilterBackgroundPoint::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    pointFilter.renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBackgroundPoint::setPoints(std::vector<BasePoint> points) {
    pointFilter.setPoints(points);
}

}
