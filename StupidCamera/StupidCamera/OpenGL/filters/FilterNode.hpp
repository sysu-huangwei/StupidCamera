//
//  FilterNode.hpp
//
//  Created by rayyy on 2021/9/24.
//

#ifndef FilterNode_hpp
#define FilterNode_hpp

#include <vector>
#include "FilterNodeDescription.hpp"
#include "SCFilterBase.hpp"

namespace effect {

class FilterNode {
public:
    
    FilterNode(const FilterNodeDescription &nodeDesc);
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    /// @param index 这个输入的FBO纹理应该设置到当前滤镜shader的第几个位置，从0开始（通常用于多路输入的滤镜）
    void setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index = 0);
    
    /// 如果需要绘制到特定的FBO上，那么通过这个接口设置。通常滤镜链的最后一个节点需要设置
    /// @param outputFrameBuffer 目标FBO
    void setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer);
    
    /// 渲染，必须在GL线程
    void render();
    
    
    std::string id = "";
    
    std::shared_ptr<SCFilterBase> filter = nullptr;
    
protected:
    
    friend class FilterChain;
    std::vector<std::shared_ptr<FilterNode>> nextNodes;
    std::vector<int> nextIndices;
    
    std::shared_ptr<FrameBuffer> outputFrameBuffer = nullptr;
    
    void setOutputFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output);
};

}

#endif /* FilterNode_hpp */
