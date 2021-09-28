//
//  SCFilterFacePoint.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef SCFilterFacePoint_hpp
#define SCFilterFacePoint_hpp

#include "SCFilterBackgroundPoint.hpp"
#include "SCFilterFaceBase.hpp"

namespace effect {

/// 画人脸点的滤镜
class SCFilterFacePoint : public SCFilterBackgroundPoint, SCFilterFaceBase {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return SCFilterType_FacePoint; }
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
};

}

#endif /* SCFilterFacePoint_hpp */
