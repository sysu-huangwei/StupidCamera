//
//  SCFilterBlurSub.hpp
//
//  Created by rayyy on 2021/8/17.
//

#ifndef SCFilterBlurSub_hpp
#define SCFilterBlurSub_hpp

#include "SCFilterBase.hpp"

/// 模糊
class SCFilterBlurSub : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Blur; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置滤镜程度
    /// @param alpha 滤镜程度，0.0 ~ 1.0
    void setAlpha(float alpha);
    
protected:
    int alphaUniform = -1, offsetUniform = -1;
    float alpha = 1.0f, widthOffset = 0.0f, heightOffset = 0.0f;
};

#endif /* SCFilterBlurSub_hpp */
