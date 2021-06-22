//
//  SCFilterDrawAlpha.cpp
//
//  Created by rayyy on 2021/6/21.
//

#include "SCFilterDrawAlpha.hpp"

const char *kSCFilterDrawAlphaVertexShaderString = SHADER_STRING_CPP
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

const char *kSCFilterDrawAlphaFragmentShaderString = SHADER_STRING_CPP
(
 precision highp float;
 
 uniform sampler2D u_texture;
 varying vec2 texcoordOut;
 
 uniform float alpha;
 
 void main()
 {
    float alpha = texture2D(u_texture, texcoordOut).a;
    gl_FragColor = vec4(alpha, alpha, alpha, 1.0);
}
 );

SCFilterDrawAlpha::SCFilterDrawAlpha():SCFilterBase() {
    
}

SCFilterDrawAlpha::~SCFilterDrawAlpha() {
    
}

void SCFilterDrawAlpha::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterDrawAlphaVertexShaderString, kSCFilterDrawAlphaFragmentShaderString);
    positionAttribute = glGetAttribLocation(programID, "a_position");
    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

void SCFilterDrawAlpha::release() {
    SCFilterBase::release();
}

unsigned SCFilterDrawAlpha::render() {
    beforeDraw();
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    afterDraw();
    return SCFilterBase::render();
}
