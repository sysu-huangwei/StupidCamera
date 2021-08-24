//
//  SCFilterBackgroundMesh.cpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#include "SCFilterBackgroundMesh.hpp"


void SCFilterBackgroundMesh::init() {
    copyFilter.init();
    meshFilter.init();
}

void SCFilterBackgroundMesh::release() {
    copyFilter.release();
    meshFilter.release();
}

void SCFilterBackgroundMesh::resize(int width, int height) {
    SCFilterBase::resize(width, height);
    copyFilter.resize(width, height);
    meshFilter.resize(width, height);
}

void SCFilterBackgroundMesh::setInputFrameBuffer(FrameBuffer *inputFrameBuffer) {
    copyFilter.setInputFrameBuffer(inputFrameBuffer);
    meshFilter.setInputFrameBuffer(inputFrameBuffer);
}

void SCFilterBackgroundMesh::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    meshFilter.renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBackgroundMesh::setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    meshFilter.setMesh(mesh, meshStd, meshArrayCount, meshIndex, indexArrayCount);
}
