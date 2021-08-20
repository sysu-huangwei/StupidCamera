//
//  SCFilterMesh.cpp
//
//  Created by rayyyhuang on 2021/4/22.
//

#include "SCFilterMesh.hpp"
#include <string.h>

SCFilterMesh::~SCFilterMesh() {
    if (this->mesh) {
        delete [] this->mesh;
        this->mesh = nullptr;
    }
    if (this->meshIndex) {
        delete [] this->meshIndex;
        this->meshIndex = nullptr;
    }
}

void SCFilterMesh::init() {
    SCFilterBase::initWithVertexStringAndFragmentString("mesh", "mesh");
}

void SCFilterMesh::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    if (!enableRender || !inputFrameBuffer || !outputFrameBuffer) {
        return;
    }
    
    outputFrameBuffer->activeFrameBuffer();
    
    program->use();
    
    program->setVertexAttribPointer("a_position", mesh);
    program->setVertexAttribPointer("a_position_std", meshStd);
    
    program->setTextureAtIndex("u_texture", inputFrameBuffer->getTextureID(), 2);
    
    glDrawElements(GL_TRIANGLES, indexArrayCount, GL_UNSIGNED_INT, (void *)meshIndex);
    
    glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
    
    inputFrameBuffer->unlock();
}

void SCFilterMesh::setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    if (meshArrayCount != this->meshArrayCount) {
        if (this->mesh) {
            delete [] this->mesh;
            this->mesh = nullptr;
        }
        if (this->meshStd) {
            delete [] this->meshStd;
            this->meshStd = nullptr;
        }
        this->meshArrayCount = meshArrayCount;
        this->mesh = new float[meshArrayCount];
        this->meshStd = new float[meshArrayCount];
    }
    if (indexArrayCount != this->indexArrayCount) {
        if (this->meshIndex) {
            delete [] this->meshIndex;
            this->meshIndex = nullptr;
        }
        this->indexArrayCount = indexArrayCount;
        this->meshIndex = new unsigned int[indexArrayCount];
    }
    if (mesh && meshArrayCount > 0) {
        memcpy(this->mesh, mesh, sizeof(float) * meshArrayCount);
    }
    if (meshStd && meshArrayCount > 0) {
        memcpy(this->meshStd, meshStd, sizeof(float) * meshArrayCount);
    }
    if (meshIndex && meshArrayCount > 0) {
        memcpy(this->meshIndex, meshIndex, sizeof(unsigned int) * indexArrayCount);
    }
}
