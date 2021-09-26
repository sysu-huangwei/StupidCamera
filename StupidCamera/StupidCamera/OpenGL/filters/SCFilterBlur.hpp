//
//  SCFilterBlur.hpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#ifndef SCFilterBlur_hpp
#define SCFilterBlur_hpp

#define DEFAULT_MAX_LENGTH 180

#include "FilterChain.hpp"

namespace effect {

/// 模糊封装
class SCFilterBlur : public FilterChain {
public:
    
    SCFilterBlur();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Blur; }
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    
protected:
    
    /// 对宽高进行缩放，把短边控制在最大maxLength内
    /// @param width 宽，输入和输出
    /// @param height  高，输入和输出
    /// @param maxLength 短边最大的长度
    void scaleWH(int &width, int &height, int maxLength = DEFAULT_MAX_LENGTH);
    
    /// 在最终渲染之前判断是否需要渲染
    virtual bool isNeedRender() override { return true; }
};

}

#endif /* SCFilterBlur_hpp */
