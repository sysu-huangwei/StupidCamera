//
//  SCFilterBackgroundMesh.cpp
//
//  Created by rayyy on 2021/6/7.
//

#include "SCFilterBackgroundMesh.hpp"

SCFilterBackgroundMesh::SCFilterBackgroundMesh():SCFilterBase() {
    copyFilter = new SCFilterCopy();
    meshFilter = new SCFilterMesh();
}

SCFilterBackgroundMesh::~SCFilterBackgroundMesh() {
    SAFE_DELETE(copyFilter);
    SAFE_DELETE(meshFilter);
}

void SCFilterBackgroundMesh::init() {
    copyFilter->init();
    meshFilter->init();
}

void SCFilterBackgroundMesh::release() {
    copyFilter->release();
    meshFilter->release();
}

void SCFilterBackgroundMesh::resize(int width, int height) {
    copyFilter->resize(width, height);
    meshFilter->resize(width, height);
}

void SCFilterBackgroundMesh::setSrcTextureID(unsigned srcTextureID) {
    copyFilter->setSrcTextureID(srcTextureID);
    meshFilter->setSrcTextureID(srcTextureID);
}

void SCFilterBackgroundMesh::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    copyFilter->renderToFrameBuffer(outputFrameBuffer);
    meshFilter->renderToFrameBuffer(outputFrameBuffer);
}

FrameBuffer *SCFilterBackgroundMesh::render() {
    copyFilter->render();
    return meshFilter->render();
}

void SCFilterBackgroundMesh::setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    meshFilter->setMesh(mesh, meshStd, meshArrayCount, meshIndex, indexArrayCount);
}
