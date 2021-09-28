//
//  SCFilterSmallHead.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "SCFilterSmallHead.hpp"
#include <algorithm>

#define MAX_SMALL_FACE_DEGREE 0.03

namespace effect {

void SCFilterSmallHead::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (faceData) {
        BasePoint facePointChanged[FACE_POINT_COUNT];
        memcpy(facePointChanged, faceData->faces[0].facePoints, sizeof(BasePoint) * FACE_POINT_COUNT);
        changeSmallFacePoint(facePointChanged);
        setMesh(std::vector<BasePoint>(facePointChanged, facePointChanged + sizeof(facePointChanged) / sizeof(BasePoint)),
                           std::vector<BasePoint>(faceData->faces[0].facePoints, faceData->faces[0].facePoints + sizeof(faceData->faces[0].facePoints) / sizeof(BasePoint)),
                           FaceTriangleIndex,
                           FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE);
    }
}

void SCFilterSmallHead::setParams(const std::map<std::string, std::string> &param) {
    if (param.find(SCFilterParam_SmallHead_Degree) != param.end()) {
        setSmallHeadDegree(std::stof(param.at(SCFilterParam_SmallHead_Degree)));
    }
}

void SCFilterSmallHead::setSmallHeadDegree(float smallHeadDegree) {
    this->smallHeadDegree = std::max(0.0f, std::min(1.0f, smallHeadDegree));
}

void SCFilterSmallHead::changeSmallFacePoint(BasePoint *facePoint) {
    facePoint[1].x += (facePoint[0].x - facePoint[1].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[1].y += (facePoint[0].y - facePoint[1].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[2].x -= (facePoint[2].x - facePoint[0].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[2].y += (facePoint[0].y - facePoint[2].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[3].x += (facePoint[0].x - facePoint[3].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[3].y -= (facePoint[3].y - facePoint[0].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    
    facePoint[4].x -= (facePoint[4].x - facePoint[0].x) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
    facePoint[4].y -= (facePoint[4].y - facePoint[0].y) * MAX_SMALL_FACE_DEGREE * smallHeadDegree;
}

}
