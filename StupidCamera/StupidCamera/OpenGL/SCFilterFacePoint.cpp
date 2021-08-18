//
//  SCFilterFacePoint.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "SCFilterFacePoint.hpp"

void SCFilterFacePoint::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (this->faceData) {
        pointFilter.setPoints(this->faceData->faces[0].facePoints, FACE_POINT_COUNT);
    }
}
