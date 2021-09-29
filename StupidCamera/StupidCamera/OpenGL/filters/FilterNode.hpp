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
    
    std::string getID();
    
    /// 设置绘制尺寸
    /// @param width 宽
    /// @param height 高
    virtual void resize(int width, int height);
    
    /// 如果需要绘制到特定的FBO上，那么通过这个接口设置。通常滤镜链的最后一个节点需要设置
    /// @param outputFrameBuffer 目标FBO
    void setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer);
    
    /// 渲染，必须在GL线程
    void render();
    
    /// 设置参数
    /// @param param 参数
    virtual void setParams(const std::map<std::string, std::string> &param);
    
protected:
    
    std::string id = "";
    
    std::shared_ptr<SCFilterBase> filter = nullptr;
    
    friend class FilterChain;
    friend class SCFilterBackgroundMesh;
    std::vector<std::shared_ptr<FilterNode>> nextNodes;
    std::vector<int> nextIndices;
    
    std::shared_ptr<FrameBuffer> outputFrameBuffer = nullptr;
    
    void setOutputFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output);
};

}

#endif /* FilterNode_hpp */
