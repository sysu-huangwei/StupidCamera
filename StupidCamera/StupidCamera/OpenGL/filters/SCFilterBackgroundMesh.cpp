//
//  SCFilterBackgroundMesh.cpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#include "SCFilterBackgroundMesh.hpp"

namespace effect {

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

void SCFilterBackgroundMesh::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    copyFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
    meshFilter.setInputFrameBufferAtIndex(inputFrameBuffer, index);
}

void SCFilterBackgroundMesh::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    copyFilter.renderToFrameBuffer(outputFrameBuffer);
    meshFilter.renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterBackgroundMesh::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    meshFilter.setMesh(mesh, meshStd, meshIndex, indexArrayCount);
}

}
