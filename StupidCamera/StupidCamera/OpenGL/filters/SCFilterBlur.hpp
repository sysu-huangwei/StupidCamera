//
//  SCFilterBlur.hpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#ifndef SCFilterBlur_hpp
#define SCFilterBlur_hpp

#define DEFAULT_MAX_LENGTH 180

#include "SCFilterBlurSub.hpp"

/// 模糊封装
class SCFilterBlur : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Blur; }
    
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
    virtual void setInputFrameBuffer(FrameBuffer *inputFrameBuffer) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
protected:
    SCFilterBlurSub blurFilterH;
    SCFilterBlurSub blurFilterV;
    
    /// 对宽高进行缩放，把短边控制在最大maxLength内
    /// @param width 宽，输入和输出
    /// @param height  高，输入和输出
    /// @param maxLength 短边最大的长度
    void scaleWH(int &width, int &height, int maxLength = DEFAULT_MAX_LENGTH);
};

#endif /* SCFilterBlur_hpp */
