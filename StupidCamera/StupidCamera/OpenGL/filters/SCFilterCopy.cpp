//
//  SCFilterCopy.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "SCFilterCopy.hpp"
#include "FrameBufferPool.hpp"

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


void SCFilterCopy::init() {
    SCFilterBase::initWithVertexStringAndFragmentString(kSCFilterCopyVertexShaderString, kSCFilterCopyFragmentShaderString);
}

void SCFilterCopy::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!enableRender || !inputFrameBuffer || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
    
    program->setVertexAttribPointer("a_position", imageVertices);
    program->setVertexAttribPointer("a_texCoord", textureCoordinates);
    
    program->setTextureAtIndex("u_texture", inputFrameBuffer->getTextureID(), 2);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}
