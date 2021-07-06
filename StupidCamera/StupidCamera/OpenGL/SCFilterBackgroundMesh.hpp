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
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_BackgroundMesh; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置绘制尺寸，必须在GL线程，内部会创建对应尺寸的FBO
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    virtual void setInputFrameBuffer(FrameBuffer *inputFrameBuffer) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置需要画的网格，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param mesh 点位信息，{x1, y1, x2, y2……}
    /// @param meshStd 标准点位信息，{x1, y1, x2, y2……}
    /// @param meshArrayCount mesh数组长度
    /// @param meshIndex 下标索引数组
    /// @param indexArrayCount meshIndex数组长度
    virtual void setMesh(float *mesh, float *meshStd, int meshArrayCount, unsigned int *meshIndex, int indexArrayCount);
    
protected:
    SCFilterCopy *copyFilter;
    SCFilterMesh *meshFilter;
};

#endif /* SCFilterBackgroundMesh_hpp */
