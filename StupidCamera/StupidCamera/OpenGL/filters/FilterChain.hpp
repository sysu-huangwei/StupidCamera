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

class FilterChain : public SCFilterBase {
public:
    
    FilterChain(const std::vector<FilterNodeDescription> &nodeDescriptions);
    
    /// 滤镜的唯一ID
    virtual std::string filterName() override { return "FilterChain"; }
    
    /// 初始化，必须在GL线程，子类实现这个方法去做GL相关的初始化操作
    virtual void init() override;
    
    /// 释放资源，必须在GL线程，子类实现这个方法去做GL相关的释放操作
    virtual void release() override;
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height) override;
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    /// @param index 这个输入的FBO纹理应该设置到当前滤镜shader的第几个位置，从0开始（通常用于多路输入的滤镜）
    virtual void setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index = 0) override;
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) override;
    
protected:
    
    std::vector<FilterNodeDescription> nodeDescriptions;
    
    std::shared_ptr<FilterNode> beginVirtualNode;
    std::shared_ptr<FilterNode> lastNode;
    std::vector<std::shared_ptr<FilterNode>> allFilterNodes;
};

}

#endif /* FilterChain_hpp */
