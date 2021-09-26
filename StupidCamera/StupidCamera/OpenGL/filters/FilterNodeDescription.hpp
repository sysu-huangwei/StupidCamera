//
//  FilterNodeDescription.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterNodeDescription_hpp
#define FilterNodeDescription_hpp

#include <vector>
#include "FilterDescription.hpp"

namespace effect {

typedef struct {
    
    // 当前节点的ID
    std::string id = "";

    // 后继节点的ID
    std::vector<std::string> nextIDs;
    // 输入到后继节点的下标，与 nextIDs 一一对应
    std::vector<int> nextTextureIndices;
    
    // 当前滤镜的描述
    FilterDescription filterDesc;
    
} FilterNodeDescription;

const std::string defaultBeginID = "begin";
extern const FilterNodeDescription defaultBeginNodeDescription;

}

#endif /* FilterNodeDescription_hpp */
