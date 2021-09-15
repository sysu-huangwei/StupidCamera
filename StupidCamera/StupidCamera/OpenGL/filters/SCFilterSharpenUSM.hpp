//
//  SCFilterSharpen.hpp
//
//  Created by rayyy on 2021/8/23.
//

#ifndef SCFilterSharpen_hpp
#define SCFilterSharpen_hpp

#include "SCFilterBase.hpp"

namespace effect {

/// 模糊
class SCFilterSharpenUSM : public SCFilterBase {
public:
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_SharpenUSM; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    float widthOffset = 0.0f, heightOffset = 0.0f;
    float alpha = 1.0f;
};

}

#endif /* SCFilterSharpen_hpp */
