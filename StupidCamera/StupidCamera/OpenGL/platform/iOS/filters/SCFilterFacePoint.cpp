//
//  SCFilterFacePoint.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "SCFilterFacePoint.hpp"

namespace effect {

void SCFilterFacePoint::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (faceData) {
        pointFilter.setPoints(std::vector<BasePoint>(faceData->faces[0].facePoints, faceData->faces[0].facePoints + sizeof(faceData->faces[0].facePoints) / sizeof(BasePoint)));
    }
}

}
