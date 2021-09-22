//
//  FaceDetector.hpp
//  StupidCamera
//
//  Created by rayyy on 2021/9/22.
//

#ifndef FaceDetector_hpp
#define FaceDetector_hpp

#include <string>
#include <vector>
#include "FaceData.hpp"

class FaceDetector {
public:
    
    explicit FaceDetector(std::string modelFolderPath);
    ~FaceDetector();
    
    FaceData detect(unsigned char *data, int width, int height, std::vector<BaseRect> faceRects);
    
private:
    
    void* faceLandmarker;
    
    FaceDetector(const FaceDetector &) = delete;
    const FaceDetector &operator =(const FaceDetector &) = delete;
    
};

#endif /* FaceDetector_hpp */
