//
//  FaceLineFilter.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef FaceLineFilter_hpp
#define FaceLineFilter_hpp

#include "BackgroundLineFilter.hpp"
#include "FaceBaseFilter.hpp"

namespace effect {

/// 画人脸Mesh线的滤镜
class FaceLineFilter : public BackgroundLineFilter, FaceBaseFilter {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_FaceLine; }
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
};

}

#endif /* FaceLineFilter_hpp */
