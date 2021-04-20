//
//  SCFilterBase.hpp
//
//  Created by rayyy on 2020/11/26.
//

#ifndef SCFilterBase_hpp
#define SCFilterBase_hpp

#include "SCBaseGLUtils.hpp"

// 顶点坐标
const static float imageVertices[8] = {
    -1.0f, 1.0f, // top left
    1.0f, 1.0f,  // top right
    -1.0f, -1.0f, // bottom left
    1.0f, -1.0f, // bottom right
};

// 纹理坐标
const static float textureCoordinates[8] = {
    0.0f, 1.0f, // bottom left
    1.0f, 1.0f, // bottom right
    0.0f, 0.0f, // top left
    1.0f, 0.0f, // top right
};

/// 滤镜基类
class SCFilterBase {
public:
    SCFilterBase();
    ~SCFilterBase();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init();
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release();
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height);
    
    /// 设置输入图像的纹理ID
    /// @param srcTextureID 输入图像的纹理ID
    virtual void setSrcTextureID(unsigned srcTextureID);
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() = 0;
    
    /// 设置外部的纹理ID和FBO，如果都设置了>0的合法值，渲染的时候会绘制到这个buffer上，如果需要重新绘制到内置的FBO，设置0, 0
    /// @param textureIDOutside 外部的纹理ID
    /// @param fboIDOutside 外部的FBO
    virtual void setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside);
    
protected:
    int width = 0, height = 0;
    unsigned textureID = 0, fboID = 0, programID = 0;
    int positionAttribute = -1, textureCoordinateAttribute = -1;
    
    int inputImageTextureUniform = -1;
    unsigned srcTextureID = 0;
    
    virtual void initWithVertexStringAndFragmentString(const char* vs, const char* fs);
    virtual void beforeDraw();
    virtual void afterDraw();
    
    unsigned textureIDOutside = 0, fboIDOutside = 0;
    bool isRenderToOutside = false;
};

#endif /* SCFilterBase_hpp */
