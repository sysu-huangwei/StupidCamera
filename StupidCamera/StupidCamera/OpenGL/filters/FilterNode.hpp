//
//  FilterNode.hpp
//
//  Created by rayyy on 2021/9/24.
//

#ifndef FilterNode_hpp
#define FilterNode_hpp

#include <vector>
#include "FilterNodeDescription.hpp"
#include "BaseFilter.hpp"

namespace effect {

/// 滤镜节点
class FilterNode {
public:
    
    FilterNode(const FilterNodeDescription &nodeDesc);
    
    std::string getID();
    
    /// 设置绘制尺寸
    /// @param outputWidth 宽
    /// @param outputHeight 高
    virtual void setOutputSize(int outputWidth, int outputHeight);
    
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
    
    std::shared_ptr<BaseFilter> filter = nullptr;
    
    friend class FilterChain;
    friend class BackgroundMeshFilter;
    std::vector<std::shared_ptr<FilterNode>> nextNodes;
    std::vector<int> nextIndices;
    
    std::shared_ptr<FrameBuffer> outputFrameBuffer = nullptr;
    
    void setResultFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output);
    
    void informNextNodesToRender();
};

}

#endif /* FilterNode_hpp */
