//
//  SCFilterLine.cpp
//
//  Created by rayyy on 2021/4/20.
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

SCFilterLine::SCFilterLine():SCFilterBase() {
    
}

SCFilterLine::~SCFilterLine() {
    if (this->lines) {
        delete [] this->lines;
        this->lines = nullptr;
    }
}

void SCFilterLine::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterLineVertexShaderString, kSCFilterLineFragmentShaderString);
//    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
//    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

FrameBuffer *SCFilterLine::render() {
    if (!this->lines) {
        return frameBuffer;
    }
    
    frameBuffer->activeFrameBuffer();
    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
    
    program->setVertexAttribPointer("a_position", lines);
    
//    glEnableVertexAttribArray(textureCoordinateAttribute);
//    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
    
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, srcTextureID);
//    glUniform1i(inputImageTextureUniform, 2);
    
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, linesCount * 2);
    
    afterDraw();
    return SCFilterBase::render();
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
