//
//  SCFilterFaceLine.hpp
//
//  Created by rayyy on 2021/6/16.
//

#ifndef SCFilterFaceLine_hpp
#define SCFilterFaceLine_hpp

#include "SCFilterBackgroundLine.hpp"
#include "SCFilterFaceBase.hpp"

/// 画人脸Mesh线的滤镜
class SCFilterFaceLine : public SCFilterBackgroundLine, SCFilterFaceBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_FaceLine; }
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
};

#endif /* SCFilterFaceLine_hpp */
