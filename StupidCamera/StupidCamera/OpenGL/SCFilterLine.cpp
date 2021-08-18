//
//  SCFilterLine.cpp
//
//  Created by rayyyhuang on 2021/4/20.
//

#include "SCFilterLine.hpp"
#include <string.h>

const char *kSCFilterLineVertexShaderString = SHADER_STRING_CPP
(
 attribute vec2 a_position;
 
 void main()
 {
    gl_PointSize = 5.0;
    gl_Position = vec4(a_position * 2.0 - 1.0, 0.0, 1.0);
 }
);

const char *kSCFilterLineFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 void main()
 {
    gl_FragColor = vec4(1,0,0,1);
 }
);


SCFilterLine::~SCFilterLine() {
    if (this->lines) {
        delete [] this->lines;
        this->lines = nullptr;
    }
}

void SCFilterLine::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterLineVertexShaderString, kSCFilterLineFragmentShaderString);
}

void SCFilterLine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!this->lines || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    program->use();
    
    program->setVertexAttribPointer("a_position", lines);
    
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, linesCount * 2);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}


void SCFilterLine::setLines(float *lines, int linesCount) {
    if (linesCount != this->linesCount) {
        if (this->lines) {
            delete [] this->lines;
            this->lines = nullptr;
        }
        this->linesCount = linesCount;
        this->lines = new float[linesCount * 4];
    }
    if (lines && linesCount > 0) {
        memcpy(this->lines, lines, sizeof(float) * linesCount * 4);
    }
}
