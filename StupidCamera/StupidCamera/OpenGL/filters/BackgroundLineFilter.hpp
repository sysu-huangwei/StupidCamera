//
//  BackgroundLineFilter.hpp
//
//  Created by rayyyhuang on 2021/6/11.
//

#ifndef BackgroundLineFilter_hpp
#define BackgroundLineFilter_hpp

#include "CopyFilter.hpp"
#include "LineFilter.hpp"

namespace effect {

/// 画背景+线格的滤镜
class BackgroundLineFilter : public BaseFilter {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return FilterType_BackgroundLine; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    /// @param index 这个输入的FBO纹理应该设置到当前滤镜shader的第几个位置，从0开始（通常用于多路输入的滤镜）
    virtual void setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index = 0) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
    /// 设置需要画的线【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param lines 线信息，需要归一化到0到1的点
    virtual void setLines(std::vector<BaseLine> lines);
    
protected:
    CopyFilter copyFilter;
    LineFilter lineFilter;
    
    /// 在最终渲染之前判断是否需要渲染
    virtual bool isNeedRender() override { return true; }
};

}

#endif /* BackgroundLineFilter_hpp */
