//
//  SCFilterLine.hpp
//
//  Created by rayyy on 2021/4/20.
//

#ifndef SCFilterLine_hpp
#define SCFilterLine_hpp

#include "SCFilterBase.hpp"

/// 画线的滤镜
class SCFilterLine : public SCFilterBase {
public:
    SCFilterLine();
    ~SCFilterLine();
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @return 结果FrameBuffer
    virtual FrameBuffer *render() override;
    
    /// 设置需要画的线，内部会做拷贝【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param lines 线信息，每个线2个顶点(4个float) {line1.A.x, line1.A.y, line1.B.x, line1.B.y, line2.A.x, line2.A.y, line2.B.x……}  需要归一化到0到1的点
    /// @param linesCount 线的数量，一般是points的长度/4
    virtual void setLines(float *lines, int linesCount);
    
protected:
    float *lines = nullptr;
    int linesCount = 0;
};

#endif /* SCFilterLine_hpp */
