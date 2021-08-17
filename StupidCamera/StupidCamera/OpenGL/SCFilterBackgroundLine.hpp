//
//  SCFilterBackgroundLine.hpp
//  StupidCamera
//
//  Created by rayyy on 2021/6/11.
//

#ifndef SCFilterBackgroundLine_hpp
#define SCFilterBackgroundLine_hpp

#include "SCFilterCopy.hpp"
#include "SCFilterLine.hpp"

/// 画背景+线格的滤镜
class SCFilterBackgroundLine : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_BackgroundLine; }
    
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
    
    /// 设置需要画的线，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param lines 线信息，每个线2个顶点(4个float) {line1.A.x, line1.A.y, line1.B.x, line1.B.y, line2.A.x, line2.A.y, line2.B.x……}  需要归一化到0到1的点
    /// @param linesCount 线的数量，一般是points的长度/4
    virtual void setLines(float *lines, int linesCount);
    
protected:
    SCFilterCopy copyFilter;
    SCFilterLine lineFilter;
};

#endif /* SCFilterBackgroundLine_hpp */
