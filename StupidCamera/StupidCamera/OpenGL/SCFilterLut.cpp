//
//  SCFilterLut.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#include "SCFilterLut.hpp"
#include <stdio.h>

const char *kSCFilterLutVertexShaderString = SHADER_STRING_CPP
(
 attribute vec2 a_position;
 attribute vec2 a_texCoord;
 varying vec2 texcoordOut;
 
 void main()
 {
    texcoordOut = a_texCoord;
    gl_Position = vec4(a_position,0.0,1.0);
}
 );

const char *kSCFilterLutFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D u_texture;
 uniform sampler2D u_lut;
 varying vec2 texcoordOut;
 
 uniform float alpha;
 
 void main()
 {
    vec4 textureColor = texture2D(u_texture, texcoordOut);
    
    float blueColor = textureColor.b * 63.0;
    
    vec2 quad1;
    quad1.y = floor(floor(blueColor) / 8.0);
    quad1.x = floor(blueColor) - (quad1.y * 8.0);
    
    vec2 quad2;
    quad2.y = floor(ceil(blueColor) / 8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);
    
    vec2 texPos1;
    texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);
    
    vec2 texPos2;
    texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
    texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);
    
    vec4 newColor1 = texture2D(u_lut, texPos1);
    vec4 newColor2 = texture2D(u_lut, texPos2);
    
    vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
    gl_FragColor = mix(textureColor, vec4(newColor.rgb, textureColor.w), alpha);
}
 );

SCFilterLut::SCFilterLut():SCFilterBase() {
    
}

SCFilterLut::~SCFilterLut() {
    
}

void SCFilterLut::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterLutVertexShaderString, kSCFilterLutFragmentShaderString);
    positionAttribute = glGetAttribLocation(programID, "a_position");
    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
    lutTextureUniform = glGetUniformLocation(programID, "u_lut");
    alphaUniform = glGetUniformLocation(programID, "alpha");
}

void SCFilterLut::release() {
    SCFilterBase::release();
    if (lutTextureID > 0) {
        glDeleteTextures(1, &lutTextureID);
        lutTextureID = 0;
    }
}

unsigned SCFilterLut::render() {
    beforeDraw();
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, lutTextureID);
    glUniform1i(lutTextureUniform, 3);
    
    if (lutTextureID > 0) {
        glUniform1f(alphaUniform, alpha);
    } else {
        glUniform1f(alphaUniform, 0.0f);
    }
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    afterDraw();
    return SCFilterBase::render();
}

void SCFilterLut::setLutImagePath(const char *path) {
    int width, height;
    if (lutTextureID > 0) {
        glDeleteTextures(1, &lutTextureID);
        lutTextureID = 0;
    }
    this->lutTextureID = BaseGLUtils::LoadTexture_File(path, &width, &height);
}

void SCFilterLut::setAlpha(float alpha) {
    this->alpha = alpha;
}

void SCFilterLut::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    outputFrameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    glUseProgram(programID);
    
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, false, 0, imageVertices);
    
    glEnableVertexAttribArray(textureCoordinateAttribute);
    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, false, 0, textureCoordinates);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, lutTextureID);
    glUniform1i(lutTextureUniform, 3);
    
    if (lutTextureID > 0) {
        glUniform1f(alphaUniform, alpha);
    } else {
        glUniform1f(alphaUniform, 0.0f);
    }
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}
