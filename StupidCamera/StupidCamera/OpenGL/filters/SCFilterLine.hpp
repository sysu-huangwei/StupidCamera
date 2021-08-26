//
//  SCFilterLine.hpp
//
//  Created by rayyyhuang on 2021/4/20.
//

#ifndef SCFilterLine_hpp
#define SCFilterLine_hpp

#include "SCFilterBase.hpp"
#include <vector>
#include "SCBaseDefine.h"

/// 画线的滤镜
class SCFilterLine : public SCFilterBase {
public:
    ~SCFilterLine();
    
    /// 滤镜的唯一ID
    std::string filterName() override { return SCFilterType_Line; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(FrameBuffer *outputFrameBuffer) override;
    
    /// 设置需要画的线【此接口和render并行调用会有线程问题，需要保证先后顺序】
    /// @param lines 线信息，需要归一化到0到1的点
    virtual void setLines(std::vector<SCLine> lines);
    
protected:
    float *lines = nullptr;
    int linesCount = 0;
};

#endif /* SCFilterLine_hpp */
