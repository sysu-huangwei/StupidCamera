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
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Lut; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param) override;
    
protected:
    int lutTextureUniform = -1, alphaUniform = -1;
    unsigned lutTextureID = 0;
    float alpha = 1.0f;
    
    /// 设置LUT图路径，底层加载
    /// @param path LUT图的路径
    void setLutImagePath(const char *path);
    
    /// 设置滤镜程度
    /// @param alpha 滤镜程度，0.0 ~ 1.0
    void setAlpha(float alpha);
};

#endif /* SCFilterLut_hpp */
