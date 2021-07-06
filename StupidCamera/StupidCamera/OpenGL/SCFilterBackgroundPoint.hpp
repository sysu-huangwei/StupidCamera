//
//  SCFilterBackgroundPoint.hpp
//  StupidCamera
//
//  Created by rayyy on 2021/6/15.
//

#ifndef SCFilterBackgroundPoint_hpp
#define SCFilterBackgroundPoint_hpp

#include "SCFilterCopy.hpp"
#include "SCFilterPoint.hpp"

/// 画背景+点的滤镜
class SCFilterBackgroundPoint : public SCFilterBase {
public:
    SCFilterBackgroundPoint();
    ~SCFilterBackgroundPoint();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_BackgroundPoint; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    virtual void setInputFrameBuffer(FrameBuffer *inputFrameBuffer) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置需要画的点，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param points 点位信息，{x1,y1,x2,y2……}  需要归一化到0到1的点
    /// @param pointsCount 点的数量，一般是points的长度/2
    virtual void setPoints(float *points, int pointsCount);
    
protected:
    SCFilterCopy *copyFilter;
    SCFilterPoint *pointFilter;
};


#endif /* SCFilterBackgroundPoint_hpp */
