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
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData);
};

#endif /* SCFilterFaceLine_hpp */
