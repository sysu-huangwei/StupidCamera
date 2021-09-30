//
//  SmallHeadFilter.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef SmallHeadFilter_hpp
#define SmallHeadFilter_hpp

#include "BackgroundMeshFilter.hpp"
#include "FaceBaseFilter.hpp"

namespace effect {

/// 小头效果
class SmallHeadFilter : public BackgroundMeshFilter, FaceBaseFilter {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_SmallHead; }
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(std::shared_ptr<FaceData> faceData) override;
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    float smallHeadDegree = 0.0f;
    
    void changeSmallFacePoint(BasePoint *facePoint);
    
    /// 设置小头程度
    /// @param smallHeadDegree 小头程度，0~1
    virtual void setSmallHeadDegree(float smallHeadDegree);
    
    /// 在最终渲染之前判断是否需要渲染
    virtual bool isNeedRender() override { return true; }
};

}

#endif /* SmallHeadFilter_hpp */
