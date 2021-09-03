//
//  SCFilterSmallHead.hpp
//
//  Created by rayyyhuang on 2021/6/16.
//

#ifndef SCFilterSmallHead_hpp
#define SCFilterSmallHead_hpp

#include "SCFilterBackgroundMesh.hpp"
#include "SCFilterFaceBase.hpp"

namespace effect {

/// 画背景+三角网格的滤镜
class SCFilterSmallHead : public SCFilterBackgroundMesh, SCFilterFaceBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_SmallHead; }
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    float smallHeadDegree = 0.0f;
    
    void changeSmallFacePoint(BasePoint *facePoint);
    
    /// 设置小头程度
    /// @param smallHeadDegree 小头程度，0~1
    virtual void setSmallHeadDegree(float smallHeadDegree);
};

}

#endif /* SCFilterSmallHead_hpp */
