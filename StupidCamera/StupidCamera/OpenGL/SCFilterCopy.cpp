//
//  SCFilterCopy.cpp
//
//  Created by rayyy on 2020/11/26.
//

#include "SCFilterCopy.hpp"

const char *kSCFilterCopyVertexShaderString = SHADER_STRING_CPP
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

const char *kSCFilterCopyFragmentShaderString = SHADER_STRING_CPP
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


void SCFilterCopy::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
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
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}
