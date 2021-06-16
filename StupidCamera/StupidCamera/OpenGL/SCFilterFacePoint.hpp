//
//  SCFilterFacePoint.hpp
//
//  Created by rayyy on 2021/6/16.
//

#ifndef SCFilterFacePoint_hpp
#define SCFilterFacePoint_hpp

#include "SCFilterBackgroundPoint.hpp"
#include "SCFilterFaceBase.hpp"

/// 画人脸点的滤镜
class SCFilterFacePoint : public SCFilterBackgroundPoint, SCFilterFaceBase {
public:
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData);
};

#endif /* SCFilterFacePoint_hpp */
