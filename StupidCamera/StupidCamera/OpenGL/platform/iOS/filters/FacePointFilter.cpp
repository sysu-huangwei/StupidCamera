//
//  FacePointFilter.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "FacePointFilter.hpp"

namespace effect {

void FacePointFilter::setFaceData(std::shared_ptr<FaceData> faceData) {
    FaceBaseFilter::setFaceData(faceData);
//    if (faceData) {
//        pointFilter.setPoints(std::vector<BasePoint>(faceData->faces[0].facePoints, faceData->faces[0].facePoints + sizeof(faceData->faces[0].facePoints) / sizeof(BasePoint)));
//    }
}

}
