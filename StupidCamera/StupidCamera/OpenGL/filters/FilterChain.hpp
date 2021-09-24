//
//  FilterChain.hpp
//  StupidCamera
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterChain_hpp
#define FilterChain_hpp

#include <vector>
#include <map>
#include "FilterNode.hpp"
#include "FilterNodeDescription.hpp"

namespace effect {

class FilterChain {
public:
    
    FilterChain(const std::vector<FilterNodeDescription> nodeDescriptions);
    
    /// 设置输入图像的FBO
    /// @param inputFrameBuffer 输入图像的FBO
    virtual void setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer);
    
    /// 渲染，必须在GL线程
    /// @param outputFrameBuffer 目标FBO
    virtual void renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer);
    
private:
    
    std::shared_ptr<FilterNode> beginVirtualNode;
    std::shared_ptr<FilterNode> lastNode;
    std::vector<std::shared_ptr<FilterNode>> allFilterNodes;
};

}

#endif /* FilterChain_hpp */
