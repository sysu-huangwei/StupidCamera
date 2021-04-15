//
//  SCFilterLut.hpp
//
//  Created by rayyy on 2021/4/14.
//

#ifndef SCFilterLut_hpp
#define SCFilterLut_hpp

#include "SCFilterBase.hpp"

/// LUT
class SCFilterLut : public SCFilterBase {
public:
    SCFilterLut();
    ~SCFilterLut();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() override;
    
    /// 设置输入图像的纹理ID
    /// @param srcTextureID 输入图像的纹理ID
    void setSrcTextureID(unsigned srcTextureID);
    
    void setLutImagePath(const char *path);
    
    /// 设置滤镜程度
    /// @param alpha 滤镜程度，0.0 ~ 1.0
    void setAlpha(float alpha);
    
private:
    int inputImageTextureUniform = -1, lutTextureUniform = -1, alphaUniform = -1;
    unsigned srcTextureID = 0, lutTextureID = 0;
    float alpha = 1.0f;
};

#endif /* SCFilterLut_hpp */
