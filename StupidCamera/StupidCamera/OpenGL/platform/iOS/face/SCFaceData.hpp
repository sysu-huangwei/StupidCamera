//
//  SCFaceData.hpp
//
//  Created by rayyyhuang on 2021/4/16.
//

#ifndef SCFaceData_h
#define SCFaceData_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FACE_COUNT 5

#define FACE_POINT_COUNT 13
#define FACE_POINT_FLOAT_ARRAY_SIZE FACE_POINT_COUNT << 1

#define FACE_TRIANGLE_COUNT 16
#define FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE FACE_TRIANGLE_COUNT * 3
#define FACE_TRIANGLE_FLOAT_ARRAY_SIZE FACE_TRIANGLE_COUNT * 6

extern unsigned int FaceTriangleIndex[FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE];

typedef struct {
    int faceID;
    
    float rectOriginX, rectOriginY;
    float rectWidth, rectHeight;
    
    float facePoints[FACE_POINT_FLOAT_ARRAY_SIZE];
    float faceTrianlges[FACE_TRIANGLE_FLOAT_ARRAY_SIZE];
    
    bool hasRollAngle;
    float rollAngle;
    bool hasPitchlAngle;
    float pitchlAngle;
    bool hasYawlAngle;
    float yawAngle;
} SCFace;

typedef struct {
    float detectWidth, detectHeight;
    int faceCount;
    SCFace faces[MAX_FACE_COUNT];
} SCFaceData;

static SCFaceData* createSCFaceData() {
    SCFaceData *faceData = (SCFaceData *)malloc(sizeof(SCFaceData));
    memset(faceData, 0, sizeof(SCFaceData));
    return faceData;
}

static SCFaceData* newAndCopySCFaceData(const SCFaceData *srcFaceData) {
    SCFaceData *faceData = NULL;
    if (srcFaceData) {
        faceData = (SCFaceData *)malloc(sizeof(SCFaceData));
        memcpy(faceData, srcFaceData, sizeof(SCFaceData));
    }
    return faceData;
}

static void copySCFaceData(const SCFaceData *srcFaceData, SCFaceData *dstFaceData) {
    if (srcFaceData && dstFaceData) {
        memcpy(dstFaceData, srcFaceData, sizeof(SCFaceData));
    }
}

static void freeSCFaceData(SCFaceData **faceData) {
    if(*faceData) {
        free(*faceData);
        *faceData = NULL;
    }
}

#endif /* SCFaceData_h */
