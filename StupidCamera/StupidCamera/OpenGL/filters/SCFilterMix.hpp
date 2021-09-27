//
//  SCFilterMix.hpp
//
//  Created by rayyy on 2021/9/27.
//

#ifndef SCFilterMix_hpp
#define SCFilterMix_hpp

#include "SCFilterBase.hpp"

namespace effect {

/// 模糊
class SCFilterMix : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return "SCFilterMix"; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
    /// 设置混合程度，0.0：第一个输入   1.0：第二个输入   0.5：各一半
    /// @param alpha 混合程度
    void setAlpha(float alpha);
    
protected:
    
    float alpha = 0.0f;
    
    /// 是否所有输入已就绪
    virtual bool isAllInputReady() override;
};

}

#endif /* SCFilterMix_hpp */
