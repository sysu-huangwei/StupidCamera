//
//  SCFilterFaceLine.cpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#include "SCFilterFaceLine.hpp"

void SCFilterFaceLine::setFaceData(SCFaceData *faceData) {
    SCFilterFaceBase::setFaceData(faceData);
    if (faceData) {
        int lineIndex[56] = {
            0,1,  0,2,  0,3,  0,4,
            1,2,  2,4,  4,3,  3,1,
            5,10, 10,6, 6,11, 11,8, 8,12, 12,7, 7,9, 9,5,
            1,5,  1,10, 10,2, 2,6,  2,11, 4,11, 4,8, 4,12, 3,12, 3,7, 3,9, 1,9
        };
        SCLine lines[28];
        for (int i = 0; i < 28; i++) {
            lines[i].p0.x = faceData->faces[0].facePoints[lineIndex[2 * i]].x;
            lines[i].p0.y = faceData->faces[0].facePoints[lineIndex[2 * i]].y;
            lines[i].p1.x = faceData->faces[0].facePoints[lineIndex[2 * i + 1]].x;
            lines[i].p1.y = faceData->faces[0].facePoints[lineIndex[2 * i + 1]].y;
        }
        lineFilter.setLines(std::vector<SCLine>(lines, lines + sizeof(lines) / sizeof(SCLine)));
    }
}
