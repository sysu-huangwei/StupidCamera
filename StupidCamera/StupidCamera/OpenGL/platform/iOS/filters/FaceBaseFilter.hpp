//
//  FaceBaseFilter.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef FaceBaseFilter_hpp
#define FaceBaseFilter_hpp

#include <memory>
#include "FaceData.hpp"

namespace effect {

/// 需要用到人脸数据的所有滤镜的基类
class FaceBaseFilter {
public:

    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(std::shared_ptr<FaceData> faceData) = 0;
    
protected:
    
    // 人脸数据
    std::shared_ptr<FaceData> faceData = nullptr;
};

}

#endif /* FaceBaseFilter_hpp */
