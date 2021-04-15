//
//  SCFilterCopy.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCFilterCopy.hpp"

const char *kSCFilterCopyVertexShaderString = SHADER_STRING
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

const char *kSCFilterCopyFragmentShaderString = SHADER_STRING
(
 precision highp float;
 
 uniform sampler2D  u_texture;
 varying vec2 texcoordOut;
 void main()
 {
    vec4 srcColor = texture2D(u_texture,texcoordOut);
    gl_FragColor = srcColor;
}
 );

SCFilterCopy::SCFilterCopy():SCFilterBase() {
    
}

SCFilterCopy::~SCFilterCopy() {
    
}

void SCFilterCopy::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterCopyVertexShaderString, kSCFilterCopyFragmentShaderString);
    positionAttribute = glGetAttribLocation(programID, "a_position");
    textureCoordinateAttribute = glGetAttribLocation(programID, "a_texCoord");
    inputImageTextureUniform = glGetUniformLocation(programID, "u_texture");
}

unsigned SCFilterCopy::render() {
    beforeDraw();
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, srcTextureID);
    glUniform1i(inputImageTextureUniform, 2);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    afterDraw();
    return SCFilterBase::render();
}

void SCFilterCopy::setSrcTextureID(unsigned srcTextureID) {
    this->srcTextureID = srcTextureID;
}
