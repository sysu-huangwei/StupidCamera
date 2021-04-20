//
//  SCFilterPoint.hpp
//
//  Created by rayyy on 2021/4/16.
//

#ifndef SCFilterPoint_hpp
#define SCFilterPoint_hpp

#include "SCFilterBase.hpp"

/// 画点的滤镜
class SCFilterPoint : public SCFilterBase {
public:
    SCFilterPoint();
    ~SCFilterPoint();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果纹理ID
    virtual unsigned render() override;
    
    /// 设置输入图像的纹理ID
    /// @param srcTextureID 输入图像的纹理ID
    void setSrcTextureID(unsigned srcTextureID);
    
    /// 设置需要画的点，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param points 点位信息，{x1,y1,x2,y2……}  需要归一化到0到1的点
    /// @param pointsCount 点的数量，一般是points的长度/2
    void setPoints(float *points, int pointsCount);
    
private:
    int inputImageTextureUniform = -1;
    unsigned srcTextureID = 0;
    float *points = nullptr;
    int pointsCount = 0;
};
#endif /* SCFilterPoint_hpp */
