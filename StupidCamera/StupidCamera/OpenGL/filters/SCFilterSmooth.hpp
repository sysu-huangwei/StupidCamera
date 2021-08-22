//
//  SCFilterSmooth.hpp
//
//  Created by Ray on 2021/8/22.
//

#ifndef SCFilterSmooth_hpp
#define SCFilterSmooth_hpp

#include "SCFilterBlur.hpp"

/// 模糊
class SCFilterSmooth : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Smooth; }
    
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
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    int alphaUniform = -1;
    float alpha = 1.0f;
    
    SCFilterBlur blurFilter;
};

#endif /* SCFilterSmooth_hpp */
