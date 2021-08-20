//
//  SCFilterLine.cpp
//
//  Created by rayyyhuang on 2021/4/20.
//

#include "SCFilterLine.hpp"
#include <string.h>

void SCFilterLine::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("line", "line");
}

void SCFilterLine::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!enableRender || !this->lines || !outputFrameBuffer) {
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
