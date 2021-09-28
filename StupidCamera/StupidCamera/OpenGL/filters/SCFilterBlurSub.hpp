//
//  SCFilterBlurSub.hpp
//
//  Created by rayyyhuang on 2021/8/17.
//

#ifndef SCFilterBlurSub_hpp
#define SCFilterBlurSub_hpp

#include "SCFilterBase.hpp"

namespace effect {

/// 模糊
class SCFilterBlurSub : public SCFilterBase {
public:
    
    /// 滤镜的类型
    std::string filterType() override { return SCFilterType_BlurSub; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
    /// 设置采样步长
    /// @param widthOffset x方向步长
    /// @param heightOffset y方向步长
    virtual void setOffset(float widthOffset, float heightOffset);
    
protected:
    
    float widthOffset = 0.0f, heightOffset = 0.0f;
};

}

#endif /* SCFilterBlurSub_hpp */
