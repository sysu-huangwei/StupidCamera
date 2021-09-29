//
//  FacePointFilter.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef FacePointFilter_hpp
#define FacePointFilter_hpp

#include "BackgroundPointFilter.hpp"
#include "FaceBaseFilter.hpp"

namespace effect {

/// 画人脸点的滤镜
class FacePointFilter : public BackgroundPointFilter, FaceBaseFilter {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_FacePoint; }
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
};

}

#endif /* FacePointFilter_hpp */
