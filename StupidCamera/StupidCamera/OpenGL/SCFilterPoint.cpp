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
    gl_Position = vec4(a_position,0.0,1.0);
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
    positionAttribute = glGetAttribLocation(programID, "a_position");
//    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
//    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

unsigned SCFilterPoint::render() {
    if (!this->points) {
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
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, points);
    
//    glEnableVertexAttribArray(textureCoordinateAttribute);
//    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
    
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, srcTextureID);
//    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    afterDraw();
    return SCFilterBase::render();
}

void SCFilterPoint::setSrcTextureID(unsigned srcTextureID) {
    this->srcTextureID = srcTextureID;
}


void SCFilterPoint::setPoints(float *points, int pointsCount) {
    if (this->points) {
        delete [] this->points;
        this->points = nullptr;
    }
    for (int i = 0; i < pointsCount * 2; i++) {
        points[i] = points[i] * 2.0f - 1.0f;
    }
    
    this->pointsCount = pointsCount;
    this->points = DelaunayTriangle::getTriangles(points, pointsCount, this->trianglesCount);
}
