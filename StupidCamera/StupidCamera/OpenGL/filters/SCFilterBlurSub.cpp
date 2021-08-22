//
//  SCFilterBlurSub.cpp
//
//  Created by rayyyhuang on 2021/8/17.
//

#include "SCFilterBlurSub.hpp"

void SCFilterBlurSub::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("sample_3x3", "blur_bilatera_3x3");
}

void SCFilterBlurSub::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
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
    program->setUniform2f("offset", widthOffset, heightOffset);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}

void SCFilterBlurSub::setOffset(float widthOffset, float heightOffset) {
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;
}
