//
//  SCFilterFaceBase.hpp
//
//  Created by rayyy on 2021/6/16.
//

#ifndef SCFilterFaceBase_hpp
#define SCFilterFaceBase_hpp

#include "SCFaceData.hpp"

/// 需要用到人脸数据的所有滤镜的基类
class SCFilterFaceBase {
public:

    ~SCFilterFaceBase();
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) = 0;
    
protected:
    SCFaceData *faceData = NULL;
};

#endif /* SCFilterFaceBase_hpp */
