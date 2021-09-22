//
//  FaceData.hpp
//
//  Created by rayyy on 2021/9/22.
//

#ifndef FaceData_hpp
#define FaceData_hpp

#include "BaseDefine.h"

#define MAX_FACE_COUNT 5
#define FACE_POINT_COUNT 68

typedef struct {
    BaseRect faceRect;
    BasePoint facePoints[FACE_POINT_COUNT];
} Face;

typedef struct {
    float detectWidth, detectHeight;
    int faceCount;
    Face faces[MAX_FACE_COUNT];
} FaceData;


#endif /* FaceData_hpp */
