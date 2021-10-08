//
//  FaceDetector.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/9/22.
//

#include "FaceDetector.hpp"
#include <SeetaFaceLandmarker600/seeta/FaceLandmarker.h>
#include <SeetaFaceTracking600/seeta/FaceTracker.h>

FaceDetector::FaceDetector(std::string modelFolderPath) {
    std::string faceLandmarkerModelPath = modelFolderPath + "/face_landmarker_pts68.csta";
    seeta::ModelSetting faceLandmarkerModel(faceLandmarkerModelPath);
    faceLandmarker = new seeta::FaceLandmarker(faceLandmarkerModel);
    std::string faceTrackerModelPath = modelFolderPath + "/face_detector.csta";
    seeta::ModelSetting faceTrackerModel(faceTrackerModelPath);
    faceTracker = new seeta::FaceTracker(faceTrackerModel, 1536, 1128);
}

FaceDetector::~FaceDetector() {
    delete (seeta::FaceTracker *)faceLandmarker;
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
        
//        SeetaTrackingFaceInfoArray faces = ((seeta::FaceTracker *)faceTracker)->Track(seetaImage);
//        if (faces.size > 0) {
//            SeetaRect r = faces.data[0].pos;
//            printf("seeta track!!!! (%d,  %d)  %d  %d\n", r.x, r.y, r.width, r.height);
//            printf("iOS track!!!! (%d,  %d)  %d  %d\n", rect.x, rect.y, rect.width, rect.height);
//        }
        
        std::vector<SeetaPointF> points = ((seeta::FaceLandmarker *)faceLandmarker)->mark(seetaImage, rect);
        
        for (size_t j = 0; j < points.size(); j++) {
            facedata.faces[i].faceRect.x = faceRect.y;
            facedata.faces[i].faceRect.y = faceRect.x;
            facedata.faces[i].faceRect.width = faceRect.height;
            facedata.faces[i].faceRect.height = faceRect.width;
            facedata.faces[i].facePoints[j].y = points[j].x / (float)width;
            facedata.faces[i].facePoints[j].x = points[j].y / (float)height;
        }
    }
    
    return facedata;
}
