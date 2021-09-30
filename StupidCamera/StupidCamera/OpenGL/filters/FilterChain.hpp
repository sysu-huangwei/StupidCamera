//
//  FilterChain.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterChain_hpp
#define FilterChain_hpp

#include "FilterNode.hpp"
#include "FilterNodeDescription.hpp"
#include <vector>
#include <map>

namespace effect {

class FilterChain : public BaseFilter {
public:
    
    FilterChain(const std::vector<FilterNodeDescription> &nodeDescriptions);
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    virtual void setOutputSize(int outputWidth, int outputHeight) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
protected:
    
    std::vector<FilterNodeDescription> nodeDescriptions;
    
    std::shared_ptr<FilterNode> beginVirtualNode;
    std::vector<std::shared_ptr<FilterNode>> lastNodes;
    std::vector<std::shared_ptr<FilterNode>> allNodes;
    
    /// 是否所有输入已就绪
    virtual bool isAllInputReady() override;
};

}

#endif /* FilterChain_hpp */
