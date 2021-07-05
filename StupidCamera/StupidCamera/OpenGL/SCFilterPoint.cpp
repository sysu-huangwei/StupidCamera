//
//  SCFilterPoint.cpp
//
//  Created by rayyy on 2021/4/16.
//

#include "SCFilterPoint.hpp"
#include <string.h>
#include "DelaunayTriangle.hpp"

const char *kSCFilterPointVertexShaderString = SHADER_STRING_CPP
(
 attribute vec2 a_position;
 
 void main()
 {
    gl_PointSize = 5.0;
    gl_Position = vec4(a_position * 2.0 - 1.0, 0.0, 1.0);
 }
);

const char *kSCFilterPointFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 void main()
 {
    gl_FragColor = vec4(1,0,0,1);
 }
);

SCFilterPoint::SCFilterPoint():SCFilterBase() {
    
}

SCFilterPoint::~SCFilterPoint() {
    if (this->points) {
        delete [] this->points;
        this->points = nullptr;
    }
}

void SCFilterPoint::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterPointVertexShaderString, kSCFilterPointFragmentShaderString);
}

void SCFilterPoint::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!this->points) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    program->use();
    
    program->setVertexAttribPointer("a_position", points);
    
    glDrawArrays(GL_POINTS, 0, pointsCount);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
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
