//
//  SCFilterCopy.cpp
//
//  Created by rayyyhuang on 2020/11/26.
//

#include "SCFilterCopy.hpp"
#include "FrameBufferPool.hpp"

namespace effect {

void SCFilterCopy::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("simple", "simple");
}

void SCFilterCopy::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
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
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
}

}
