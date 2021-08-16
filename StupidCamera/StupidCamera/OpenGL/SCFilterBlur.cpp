//
//  SCFilterBlur.cpp
//
//  Created by rayyy on 2021/8/16.
//

#include "SCFilterBlur.hpp"

const char *kSCFilter3x3SampleVertexShaderString = SHADER_STRING_CPP
(
 attribute vec2 a_position;
 attribute vec2 a_texCoord;
 varying vec2 texcoordOut;
 uniform vec2 offset;
 
 varying vec2 texcoordOutNear[8];
 
 void main()
 {
    texcoordOut = a_texCoord;
    gl_Position = vec4(a_position,0.0,1.0);
    
    texcoordOutNear[0] = a_texCoord + vec2(offset.x, 0.0);
    texcoordOutNear[1] = a_texCoord + vec2(-offset.x, 0.0);
    texcoordOutNear[2] = a_texCoord + vec2(0.0, offset.y);
    texcoordOutNear[3] = a_texCoord + vec2(0.0, -offset.y);
    
    texcoordOutNear[4] = a_texCoord + vec2(offset.x, offset.y);
    texcoordOutNear[5] = a_texCoord + vec2(-offset.x, offset.y);
    texcoordOutNear[6] = a_texCoord + vec2(offset.x, -offset.y);
    texcoordOutNear[7] = a_texCoord + vec2(-offset.x, -offset.y);
}
 );

const char *kSCFilter3x3AverageBlurFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D u_texture;
 varying vec2 texcoordOut;
 varying vec2 texcoordOutNear[8];
 
 uniform float alpha;
 
 void main()
 {
    vec4 srcColor = texture2D(u_texture, texcoordOut);
    
    vec4 sum = srcColor.rgb;
    for (int i = 0; i < 8; i++) {
        sum += texture2D(u_texture, texcoordOutNear[i]);
    }
    sum *= 0.1111111;
    
    gl_FragColor = vec4(mix(srcColor, sum, alpha).rgb, srcColor.a);
}
 );

const char *kSCFilter3x3GaussianBlurFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D u_texture;
 varying vec2 texcoordOut;
 varying vec2 texcoordOutNear[8];
 
 uniform float alpha;
 
 void main()
 {
    vec4 srcColor = texture2D(u_texture, texcoordOut);
    
    vec4 sum = srcColor * 0.147761;
    sum += texture2D(u_texture, texcoordOutNear[0]) * 0.118318;
    sum += texture2D(u_texture, texcoordOutNear[1]) * 0.118318;
    sum += texture2D(u_texture, texcoordOutNear[2]) * 0.118318;
    sum += texture2D(u_texture, texcoordOutNear[3]) * 0.118318;
    sum += texture2D(u_texture, texcoordOutNear[4]) * 0.094742;
    sum += texture2D(u_texture, texcoordOutNear[5]) * 0.094742;
    sum += texture2D(u_texture, texcoordOutNear[6]) * 0.094742;
    sum += texture2D(u_texture, texcoordOutNear[7]) * 0.094742;
    
    gl_FragColor = vec4(mix(srcColor, sum, alpha).rgb, srcColor.a);
}
 );

SCFilterBlur::SCFilterBlur():SCFilterBase() {
    
}

SCFilterBlur::~SCFilterBlur() {
    
}

void SCFilterBlur::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilter3x3SampleVertexShaderString, kSCFilter3x3GaussianBlurFragmentShaderString);
}

void SCFilterBlur::release() {
    SCFilterBase::release();
}

void SCFilterBlur::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    SCFilterBase::setInputFrameBuffer(inputFrameBuffer);
    if (inputFrameBuffer) {
        widthOffset = 5.0f / inputFrameBuffer->getWidth();
        heightOffset = 5.0f / inputFrameBuffer->getHeight();
    }
}

void SCFilterBlur::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
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
    program->setUniform2f("offset", widthOffset, heightOffset);
    program->setUniform1f("alpha", alpha);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}

void SCFilterBlur::setAlpha(float alpha) {
    this->alpha = alpha;
}

void SCFilterBlur::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_BlurAlpha) {
            setAlpha(std::stof((*it).second));
        }
    }
}
