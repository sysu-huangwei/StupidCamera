//
//  SCFilterMix.cpp
//
//  Created by rayyy on 2021/9/27.
//

#include "SCFilterMix.hpp"

namespace effect {

void SCFilterMix::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("simple", "mix");
}

void SCFilterMix::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        outputFrameBuffer->activeFrameBuffer();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        
        program->use();
        
        program->setVertexAttribPointer("a_position", imageVertices);
        program->setVertexAttribPointer("a_texCoord", textureCoordinates);
        
        program->setTextureAtIndex("u_texture", inputFrameBuffers.begin()->first->getTextureID(), 2 + inputFrameBuffers.begin()->second);
        program->setTextureAtIndex("u_texture1", (inputFrameBuffers.begin()++)->first->getTextureID(), 2 + (inputFrameBuffers.begin()++)->second);
        program->setUniform1f("alpha", alpha);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    }
    
    inputFrameBuffers.begin()->first->unlock();
    (inputFrameBuffers.begin()++)->first->unlock();
    inputFrameBuffers.clear();
}

void SCFilterMix::setAlpha(float alpha) {
    this->alpha = alpha;
}

bool SCFilterMix::isAllInputReady() {
    return inputFrameBuffers.size() == 2;
}

}
