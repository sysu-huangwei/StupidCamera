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
    if (faceData) {
        SCPoint facePointChanged[FACE_POINT_COUNT];
        memcpy(facePointChanged, faceData->faces[0].facePoints, sizeof(SCPoint) * FACE_POINT_COUNT);
        changeSmallFacePoint(facePointChanged);
        meshFilter.setMesh(std::vector<SCPoint>(facePointChanged, facePointChanged + sizeof(facePointChanged) / sizeof(SCPoint)),
                           std::vector<SCPoint>(faceData->faces[0].facePoints, faceData->faces[0].facePoints + sizeof(faceData->faces[0].facePoints) / sizeof(SCPoint)),
                           FaceTriangleIndex,
                           FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE);
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

void SCFilterSmallHead::changeSmallFacePoint(SCPoint *facePoint) {
    facePoint[1].x += (facePoint[0].x - facePoint[1].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[1].y += (facePoint[0].y - facePoint[1].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[2].x -= (facePoint[2].x - facePoint[0].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[2].y += (facePoint[0].y - facePoint[2].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[3].x += (facePoint[0].x - facePoint[3].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[3].y -= (facePoint[3].y - facePoint[0].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[4].x -= (facePoint[4].x - facePoint[0].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[4].y -= (facePoint[4].y - facePoint[0].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
}

