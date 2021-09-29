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

void SCFilterBlurSub::resize(int width, int height) {
    if (direction == BlurDirection_Horizontal) {
        widthOffset = 1.0f / (float)width;
        heightOffset = 0.0f;
    } else if (direction == BlurDirection_Vertical) {
        widthOffset = 0.0f;
        heightOffset = 1.0f / (float)height;
    }
}

void SCFilterBlurSub::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        outputFrameBuffer->activeFrameBuffer();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        
        program->use();
        
        program->setVertexAttribPointer("a_position", imageVertices);
        program->setVertexAttribPointer("a_texCoord", textureCoordinates);
        
        program->setTextureAtIndex("u_texture", inputFrameBuffers[0]->getTextureID(), 2 + inputFrameBufferIndices[0]);
        program->setUniform2f("offset", widthOffset, heightOffset);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    }
    
    unlockAndClearAllInputFrameBuffers();
}

void SCFilterBlurSub::setParams(const std::map<std::string, std::string> &param) {
    if (param.find(SCFilterParam_BlurSub_Direction) != param.end()) {
        direction = (BlurDirection)std::stoi(param.at(SCFilterParam_BlurSub_Direction));
    }
}

}
