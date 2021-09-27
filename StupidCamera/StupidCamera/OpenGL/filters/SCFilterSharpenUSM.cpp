//
//  SCFilterSharpenUSM.cpp
//
//  Created by rayyy on 2021/8/23.
//

#include "SCFilterSharpenUSM.hpp"

namespace effect {

void SCFilterSharpenUSM::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("sharpen_USM", "sharpen_USM");
}

void SCFilterSharpenUSM::resize(int width, int height) {
    SCFilterBase::resize(width, height);
    widthOffset = 1.0f / (float)width;
    heightOffset = 1.0f / (float)height;
}

void SCFilterSharpenUSM::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        outputFrameBuffer->activeFrameBuffer();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        
        program->use();
        
        program->setVertexAttribPointer("a_position", imageVertices);
        program->setVertexAttribPointer("a_texCoord", textureCoordinates);
        
        program->setTextureAtIndex("u_texture", inputFrameBuffers.begin()->first->getTextureID(), 2 + inputFrameBuffers.begin()->second);
        program->setUniform2f("offset", widthOffset, heightOffset);
        program->setUniform1f("alpha", alpha);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    }
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
}

void SCFilterSharpenUSM::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_SharpenAlpha) {
            alpha = std::stof((*it).second);
        }
    }
}

}
