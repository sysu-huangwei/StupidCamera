//
//  SCFilterBackgroundPoint.hpp
//  StupidCamera
//
//  Created by rayyy on 2021/6/15.
//

#ifndef SCFilterBackgroundPoint_hpp
#define SCFilterBackgroundPoint_hpp

#include "SCFilterCopy.hpp"
#include "SCFilterPoint.hpp"

/// 画背景+点的滤镜
class SCFilterBackgroundPoint : public SCFilterBase {
public:
    SCFilterBackgroundPoint();
    ~SCFilterBackgroundPoint();
    
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
    
    /// 设置需要画的点，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param points 点位信息，{x1,y1,x2,y2……}  需要归一化到0到1的点
    /// @param pointsCount 点的数量，一般是points的长度/2
    void setPoints(float *points, int pointsCount);
    
protected:
    SCFilterCopy *copyFilter;
    SCFilterPoint *pointFilter;
};


#endif /* SCFilterBackgroundPoint_hpp */
