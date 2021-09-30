//
//  BackgroundMeshFilter.cpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#include "BackgroundMeshFilter.hpp"
#include "FilterFactory.hpp"
#include "MeshFilter.hpp"

namespace effect {

BackgroundMeshFilter::BackgroundMeshFilter() : FilterChain(FilterFactory::getChainDescByType("BackgroundMeshFilter")){
    
}

void BackgroundMeshFilter::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    for (const std::shared_ptr<FilterNode> &node : allNodes) {
        if (node->getID() == "mesh") {
            std::shared_ptr<MeshFilter> meshFilter = std::static_pointer_cast<MeshFilter>(node->filter);
            meshFilter->setMesh(mesh, meshStd, meshIndex, indexArrayCount);
        }
    }
}

}
