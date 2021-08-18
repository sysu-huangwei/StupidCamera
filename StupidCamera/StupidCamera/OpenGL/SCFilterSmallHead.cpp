//
//  SCFilterSmallHead.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "SCFilterSmallHead.hpp"
#include <algorithm>

#define MAX_SMALL_FACE_DEGREE 0.03

void SCFilterSmallHead::renderToFrameBuffer(FrameBuffer *outputFrameBuffer) {
    SCFilterBackgroundMesh::renderToFrameBuffer(outputFrameBuffer);
}

void SCFilterSmallHead::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (this->faceData) {
        float facePointFloatChanged[FACE_POINT_FLOAT_ARRAY_SIZE];
        memcpy(facePointFloatChanged, this->faceData->faces[0].facePoints, sizeof(float) * FACE_POINT_FLOAT_ARRAY_SIZE);
        changeSmallFacePoint(facePointFloatChanged);
        meshFilter.setMesh(facePointFloatChanged, this->faceData->faces[0].facePoints, FACE_POINT_FLOAT_ARRAY_SIZE, FaceTriangleIndex, FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE);
    }
}

void SCFilterSmallHead::setParams(const std::map<std::string, std::string> &param) {
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_SmallHeadDegree) {
            setSmallHeadDegree(std::stof((*it).second));
        }
    }
}

void SCFilterSmallHead::setSmallHeadDegree(float smallHeadDegree) {
    this->smallHeadDegree = std::max(0.0f, std::min(1.0f, smallHeadDegree));
}

void SCFilterSmallHead::changeSmallFacePoint(float *facePointFloat) {
    facePointFloat[2] += (facePointFloat[0] - facePointFloat[2]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePointFloat[3] += (facePointFloat[1] - facePointFloat[3]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePointFloat[4] -= (facePointFloat[4] - facePointFloat[0]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePointFloat[5] += (facePointFloat[1] - facePointFloat[5]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePointFloat[6] += (facePointFloat[0] - facePointFloat[6]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePointFloat[7] -= (facePointFloat[7] - facePointFloat[1]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePointFloat[8] -= (facePointFloat[8] - facePointFloat[0]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePointFloat[9] -= (facePointFloat[9] - facePointFloat[1]) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
}

