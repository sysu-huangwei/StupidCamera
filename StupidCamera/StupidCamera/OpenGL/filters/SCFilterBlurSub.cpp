//
//  SCFilterBlurSub.cpp
//
//  Created by rayyyhuang on 2021/8/17.
//

#include "SCFilterBlurSub.hpp"

namespace effect {

void SCFilterBlurSub::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("sample_9x9", "blur_surface_9x9");
}

void SCFilterBlurSub::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (!isNeedRender() || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
    
    program->setVertexAttribPointer("a_position", imageVertices);
    program->setVertexAttribPointer("a_texCoord", textureCoordinates);
    
    program->setTextureAtIndex("u_texture", inputFrameBuffers.begin()->first->getTextureID(), 2 + inputFrameBuffers.begin()->second);
    program->setUniform2f("offset", widthOffset, heightOffset);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
}

void SCFilterBlurSub::setOffset(float widthOffset, float heightOffset) {
    this->widthOffset = widthOffset;
    this->heightOffset = heightOffset;
}

}
