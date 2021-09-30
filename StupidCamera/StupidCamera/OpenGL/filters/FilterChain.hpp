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

/// 滤镜链，是多个滤镜效果的组合
class FilterChain : public BaseFilter {
public:
    
    FilterChain(const std::vector<FilterNodeDescription> &nodeDescriptions);
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    /// @param index 这个输入的FBO纹理应该设置到当前滤镜shader的第几个位置，从0开始（通常用于多路输入的滤镜）
    virtual void setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index = 0) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
protected:
    
    // 滤镜链描述
    std::vector<FilterNodeDescription> nodeDescriptions;
    
    // 标记滤镜链开始的节点。这是一个虚拟节点，里面并没有真正的滤镜，只是用来标记这个渲染链的开端是哪几个。
    std::shared_ptr<FilterNode> beginVirtualNode;
    // 滤镜链最后的节点。滤镜链最终绘制的结果由这些滤镜来绘制。
    std::vector<std::shared_ptr<FilterNode>> lastNodes;
    // 滤镜链中所有的节点
    std::vector<std::shared_ptr<FilterNode>> allNodes;
    
    /// 是否所有输入已就绪
    virtual bool isAllInputReady() override;
};

}

#endif /* FilterChain_hpp */
