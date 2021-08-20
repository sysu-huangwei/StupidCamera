//
//  SCFilterPoint.cpp
//
//  Created by rayyyhuang on 2021/4/16.
//

#include "SCFilterPoint.hpp"
#include <string.h>
#include "DelaunayTriangle.hpp"

SCFilterPoint::~SCFilterPoint() {
    if (this->points) {
        delete [] this->points;
        this->points = nullptr;
    }
}

void SCFilterPoint::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("point", "point");
}

void SCFilterPoint::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!enableRender || !this->points || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    program->use();
    
    program->setVertexAttribPointer("a_position", points);
    
    glDrawArrays(GL_POINTS, 0, pointsCount);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}


void SCFilterPoint::setPoints(float *points, int pointsCount) {
    if (pointsCount != this->pointsCount) {
        if (this->points) {
            delete [] this->points;
            this->points = nullptr;
        }
        this->pointsCount = pointsCount;
        this->points = new float[pointsCount * 2];
    }
    if (points && pointsCount > 0) {
        memcpy(this->points, points, sizeof(float) * pointsCount * 2);
    }
}
