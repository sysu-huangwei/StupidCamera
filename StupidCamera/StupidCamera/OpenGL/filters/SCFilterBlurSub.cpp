//
//  SCFilterBlurSub.cpp
//
//  Created by rayyyhuang on 2021/8/17.
//

#include "SCFilterBlurSub.hpp"

void SCFilterBlurSub::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("sample_3x3", "blur_gaussian_3x3");
}

void SCFilterBlurSub::resize(int width, int height) {
    SCFilterBase::resize(width, height);
    if (width > 0 && height > 0) {
        widthOffset = 1.0f / width;
        heightOffset = 1.0f / height;
    }
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
    program->setUniform1f("alpha", alpha);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}

void SCFilterBlurSub::setAlpha(float alpha) {
    this->alpha = alpha;
}