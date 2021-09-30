//
//  FaceBaseFilter.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "FaceBaseFilter.hpp"

namespace effect {

void FaceBaseFilter::setFaceData(std::shared_ptr<FaceData> faceData) {
    this->faceData = faceData;
}

}
