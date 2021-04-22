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
    positionAttribute = glGetAttribLocation(programID, "a_position");
//    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
//    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

unsigned SCFilterLine::render() {
    if (!this->lines) {
        return isRenderToOutside ? textureIDOutside : srcTextureID;
    }
    
    if (isRenderToOutside) {
        glBindFramebuffer(GL_FRAMEBUFFER, fboIDOutside);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureIDOutside, 0);
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    }
    
    glViewport(0, 0, width, height);
    
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, lines);
    
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