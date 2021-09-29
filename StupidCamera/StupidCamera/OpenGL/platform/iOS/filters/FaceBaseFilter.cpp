//
//  FaceBaseFilter.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "FaceBaseFilter.hpp"

namespace effect {

FaceBaseFilter::~FaceBaseFilter() {
    if (faceData) {
        freeSCFaceData(&faceData);
    }
}

void FaceBaseFilter::setFaceData(SCFaceData *faceData) {
    if (faceData) {
        if (!this->faceData) {
            this->faceData = newAndCopySCFaceData(faceData);
        } else {
            copySCFaceData(faceData, this->faceData);
        }
    }
}

}
