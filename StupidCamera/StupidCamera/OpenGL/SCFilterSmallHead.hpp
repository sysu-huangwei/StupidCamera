//
//  SCFilterSmallHead.hpp
//
//  Created by rayyy on 2021/6/16.
//

#ifndef SCFilterSmallHead_hpp
#define SCFilterSmallHead_hpp

#include "SCFilterBackgroundMesh.hpp"
#include "SCFilterFaceBase.hpp"

/// 画背景+三角网格的滤镜
class SCFilterSmallHead : public SCFilterBackgroundMesh, SCFilterFaceBase {
public:
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置人脸数据
    /// @param faceData 人脸数据
    virtual void setFaceData(SCFaceData *faceData) override;
    
    /// 设置小头程度
    /// @param smallHeadDegree 小头程度，0~1
    virtual void setSmallHeadDegree(float smallHeadDegree);
    
protected:
    float smallHeadDegree = 0.0f;
    
    void changeSmallFacePoint(float *facePointFloat);
};

#endif /* SCFilterSmallHead_hpp */
