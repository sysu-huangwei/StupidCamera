//
//  SCFilterLut.cpp
//
//  Created by rayyyhuang on 2021/4/14.
//

#include "SCFilterLut.hpp"
#include "SCBaseGLUtils.hpp"

namespace effect {

void SCFilterLut::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("simple", "lut");
}

void SCFilterLut::release() {
    SCFilterBase::release();
    if (lutTextureID > 0) {
        glDeleteTextures(1, &lutTextureID);
        lutTextureID = 0;
    }
}

void SCFilterLut::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        outputFrameBuffer->activeFrameBuffer();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        
        program->use();
        
        program->setVertexAttribPointer("a_position", imageVertices);
        program->setVertexAttribPointer("a_texCoord", textureCoordinates);
        
        program->setTextureAtIndex("u_texture", inputFrameBuffers.begin()->first->getTextureID(), 2 + inputFrameBuffers.begin()->second);
        program->setTextureAtIndex("u_lut", lutTextureID, 3);
        
        if (lutTextureID > 0) {
            program->setUniform1f("alpha", alpha);
        } else {
            program->setUniform1f("alpha", 0.0f);
        }
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    }
    
    inputFrameBuffers.begin()->first->unlock();
    inputFrameBuffers.clear();
}

void SCFilterLut::setLutImagePath(const char *path) {
    if (lutTextureID > 0) {
        glDeleteTextures(1, &lutTextureID);
        lutTextureID = 0;
    }
    int width, height;
    this->lutTextureID = BaseGLUtils::loadImageFileToTexture(path, width, height);
}

void SCFilterLut::setAlpha(float alpha) {
    this->alpha = alpha;
}

void SCFilterLut::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_LutPath) {
            setLutImagePath((*it).second.c_str());
        } else if ((*it).first == SCFilterParam_LutAlpha) {
            setAlpha(std::stof((*it).second));
        }
    }
}

}
