//
//  SCFilterBaseTwoInput.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/8/20.
//

#include "SCFilterBaseTwoInput.hpp"

void SCFilterBaseTwoInput::setSecondInputFrameBuffer(FrameBuffer *secondInputFrameBuffer) {
    this->secondInputFrameBuffer = secondInputFrameBuffer;
    this->secondInputFrameBuffer->lock();
}
