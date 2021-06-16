//
//  SCFilterFaceBase.cpp
//
//  Created by rayyy on 2021/6/16.
//

#include "SCFilterFaceBase.hpp"


SCFilterFaceBase::SCFilterFaceBase() {
    
}

SCFilterFaceBase::~SCFilterFaceBase() {
    if (faceData) {
        freeSCFaceData(&faceData);
    }
}

void SCFilterFaceBase::setFaceData(SCFaceData *faceData) {
    if (faceData) {
        if (!this->faceData) {
            this->faceData = newAndCopySCFaceData(faceData);
        } else {
            copySCFaceData(faceData, this->faceData);
        }
    }
}
