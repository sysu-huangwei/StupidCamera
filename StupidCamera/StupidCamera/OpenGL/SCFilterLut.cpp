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
}

void SCFilterLut::release() {
    SCFilterBase::release();
    if (lutTextureID > 0) {
        glDeleteTextures(1, &lutTextureID);
        lutTextureID = 0;
    }
}

void SCFilterLut::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!inputFrameBuffer || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
    
    program->setVertexAttribPointer("a_position", imageVertices);
    program->setVertexAttribPointer("a_texCoord", textureCoordinates);
    
    program->setTextureAtIndex("u_texture", inputFrameBuffer->getTextureID(), 2);
    program->setTextureAtIndex("u_lut", lutTextureID, 3);
    
    if (lutTextureID > 0) {
        program->setUniform1f("alpha", alpha);
    } else {
        program->setUniform1f("alpha", 0.0f);
    }
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
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
