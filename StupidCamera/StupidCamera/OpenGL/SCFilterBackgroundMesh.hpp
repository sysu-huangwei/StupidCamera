//
//  SCFilterBackgroundMesh.hpp
//
//  Created by rayyy on 2021/6/7.
//

#ifndef SCFilterBackgroundMesh_hpp
#define SCFilterBackgroundMesh_hpp

#include "SCFilterCopy.hpp"
#include "SCFilterMesh.hpp"

/// 画背景+三角网格的滤镜
class SCFilterBackgroundMesh : public SCFilterBase {
public:
    SCFilterBackgroundMesh();
    ~SCFilterBackgroundMesh();
    
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
    virtual unsigned render();
    
    /// 设置外部的纹理ID和FBO，如果都设置了>0的合法值，渲染的时候会绘制到这个buffer上，如果需要重新绘制到内置的FBO，设置0, 0
    /// @param textureIDOutside 外部的纹理ID
    /// @param fboIDOutside 外部的FBO
    virtual void setOutsideTextureAndFbo(unsigned textureIDOutside, unsigned fboIDOutside);
    
    /// 设置需要画的网格，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param mesh 点位信息，{x1, y1, x2, y2……}
    /// @param meshArrayCount mesh数组长度
    /// @param meshIndex 下标索引数组
    /// @param indexArrayCount meshIndex数组长度
    void setMesh(float *mesh, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount);
    
protected:
    SCFilterCopy *copyFilter;
    SCFilterMesh *meshFilter;
};

#endif /* SCFilterBackgroundMesh_hpp */
