//
//  SCFilterBlur.hpp
//
//  Created by rayyy on 2021/8/16.
//

#ifndef SCFilterBlur_hpp
#define SCFilterBlur_hpp

#include "SCFilterBase.hpp"

/// 模糊
class SCFilterBlur : public SCFilterBase {
public:
    SCFilterBlur();
    ~SCFilterBlur();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Blur; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
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
    int alphaUniform = -1, offsetUniform = -1;
    float alpha = 1.0f, widthOffset = 0.0f, heightOffset = 0.0f;
    
    /// 设置滤镜程度
    /// @param alpha 滤镜程度，0.0 ~ 1.0
    void setAlpha(float alpha);
};

#endif /* SCFilterBlur_hpp */
