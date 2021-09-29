//
//  FaceBaseFilter.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef FaceBaseFilter_hpp
#define FaceBaseFilter_hpp

#include "SCFaceData.hpp"

namespace effect {

/// 需要用到人脸数据的所有滤镜的基类
class FaceBaseFilter {
public:

    ~FaceBaseFilter();
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) = 0;
    
protected:
    SCFaceData *faceData = NULL;
};

}

#endif /* FaceBaseFilter_hpp */
