//
//  FaceDetector.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/9/22.
//

#include "FaceDetector.hpp"
#import <SeetaFaceLandmarker600/seeta/FaceLandmarker.h>

FaceDetector::FaceDetector(std::string modelFolderPath) {
    std::string faceLandmarkerModelPath = modelFolderPath + "/face_landmarker_pts68.csta";
    seeta::ModelSetting faceLandmarkerModel(faceLandmarkerModelPath);
    faceLandmarker = new seeta::FaceLandmarker(faceLandmarkerModel);
}

FaceDetector::~FaceDetector() {
    delete (seeta::FaceLandmarker *)faceLandmarker;
}

FaceData FaceDetector::detect(unsigned char *data, int width, int height, std::vector<BaseRect> faceRects) {
    FaceData facedata;
    facedata.faceCount = (int)faceRects.size();
    facedata.detectWidth = width;
    facedata.detectHeight = height;
    
    for (size_t i = 0; i < faceRects.size(); i++) {
        BaseRect faceRect = faceRects[i];
        struct SeetaRect rect = {(int)(faceRect.x * width), (int)(faceRect.y * height), (int)(faceRect.width * width), (int)(faceRect.height * height)};
        seeta::ImageData seetaImage(data, width, height, 1);
        std::vector<SeetaPointF> points = ((seeta::FaceLandmarker *)faceLandmarker)->mark(seetaImage, rect);
        
        for (size_t j = 0; j < points.size(); j++) {
            facedata.faces[i].faceRect = faceRect;
            facedata.faces[i].facePoints[j].x = points[j].x / (float)width;
            facedata.faces[i].facePoints[j].y = points[j].y / (float)height;
        }
    }
    
    return facedata;
}
