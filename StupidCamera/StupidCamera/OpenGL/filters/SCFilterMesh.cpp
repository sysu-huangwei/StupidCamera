//
//  SCFilterMesh.cpp
//
//  Created by rayyyhuang on 2021/4/22.
//

#include "SCFilterMesh.hpp"
#include <string.h>
#include "BaseLog.h"

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

void SCFilterMesh::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    if (mesh.size() != meshStd.size() || mesh.empty()) {
        LOGE("Error: SCFilterMesh::setMesh: mesh.size() != meshStd.size(), %lud != %lud", mesh.size(), meshStd.size());
        return;
    }
    
    int meshArrayCountNew = (int)mesh.size() * 2;
    if (meshArrayCountNew != this->meshArrayCount) {
        SAFE_DELETE_ARRAY(this->mesh);
        SAFE_DELETE_ARRAY(this->meshStd);
        this->meshArrayCount = meshArrayCountNew;
        this->mesh = new float[meshArrayCountNew];
        this->meshStd = new float[meshArrayCountNew];
    }
    if (meshArrayCountNew > 0) {
        memcpy(this->mesh, &mesh[0], sizeof(BasePoint) * mesh.size());
    }
    if (meshArrayCountNew > 0) {
        memcpy(this->meshStd, &meshStd[0], sizeof(BasePoint) * meshStd.size());
    }
    
    if (indexArrayCount != this->indexArrayCount) {
        SAFE_DELETE_ARRAY(this->meshIndex);
        this->indexArrayCount = indexArrayCount;
        this->meshIndex = new unsigned int[indexArrayCount];
    }
    
    if (meshIndex && meshArrayCount > 0) {
        memcpy(this->meshIndex, meshIndex, sizeof(unsigned int) * indexArrayCount);
    }
}
