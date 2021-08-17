//
//  SCFilterFaceLine.cpp
//
//  Created by rayyy on 2021/6/16.
//

#include "SCFilterFaceLine.hpp"

void SCFilterFaceLine::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (this->faceData) {
        int lineIndex[56] = {
            0,1,  0,2,  0,3,  0,4,
            1,2,  2,4,  4,3,  3,1,
            5,10, 10,6, 6,11, 11,8, 8,12, 12,7, 7,9, 9,5,
            1,5,  1,10, 10,2, 2,6,  2,11, 4,11, 4,8, 4,12, 3,12, 3,7, 3,9, 1,9
        };
        float lines[112];
        for (int i = 0; i < 112; i += 4) {
            int currentIndex = i / 4;
            lines[i] = this->faceData->faces[0].facePoints[2 * lineIndex[2 * currentIndex]];
            lines[i + 1] = this->faceData->faces[0].facePoints[2 * lineIndex[2 * currentIndex] + 1];
            lines[i + 2] = this->faceData->faces[0].facePoints[2 * lineIndex[2 * currentIndex + 1]];
            lines[i + 3] = this->faceData->faces[0].facePoints[2 * lineIndex[2 * currentIndex + 1] + 1];
        }
        lineFilter.setLines(lines, 28);
    }
}
