//
//  SCFilterSmooth.cpp
//
//  Created by Ray on 2021/8/22.
//

#include "SCFilterSmooth.hpp"

namespace effect {

void SCFilterSmooth::init() {
    blurFilter.init();
    SCFilterBase::initWithVertexStringAndFragmentString("simple", "mix");
}

void SCFilterSmooth::release() {
    blurFilter.release();
    SCFilterBase::release();
}

void SCFilterSmooth::resize(int width, int height) {
    blurFilter.resize(width, height);
    SCFilterBase::resize(width, height);
}

void SCFilterSmooth::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    blurFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
    SCFilterBase::setInputFrameBufferAtIndex(inputFrameBuffer, index);
}

void SCFilterSmooth::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (!isNeedRender() || !outputFrameBuffer) {
        return;
    }
    
    std::shared_ptr<FrameBuffer> resultFrameBufferInternal = blurFilter.render();
    
    outputFrameBuffer->activeFrameBuffer();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    program->use();
    
    program->setVertexAttribPointer("a_position", imageVertices);
    program->setVertexAttribPointer("a_texCoord", textureCoordinates);
    
    program->setTextureAtIndex("u_texture", inputFrameBuffers.begin()->first->getTextureID(), 2 + inputFrameBuffers.begin()->second);
    program->setTextureAtIndex("u_texture1", resultFrameBufferInternal->getTextureID(), 3);
    program->setUniform1f("alpha", alpha);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
    resultFrameBufferInternal->unlock();
}

void SCFilterSmooth::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_BlurAlpha) {
            alpha = std::stof((*it).second);
        }
    }
}

}
