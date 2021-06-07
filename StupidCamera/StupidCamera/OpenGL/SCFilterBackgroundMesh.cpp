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
}

unsigned SCFilterBackgroundMesh::render() {
    GLuint backgroundTextureID = copyFilter->render();
    meshFilter->setSrcTextureID(backgroundTextureID);
    return meshFilter->render();
}

void SCFilterBackgroundMesh::setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside) {
    meshFilter->setOutsideTextureAndFbo(textureIDOutside, fboIDOutside);
}

void SCFilterBackgroundMesh::setMesh(float *mesh, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount) {
    meshFilter->setMesh(mesh, meshArrayCount, meshIndex, indexArrayCount);
}
