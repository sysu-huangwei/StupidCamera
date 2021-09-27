//
//  SCFilterBackgroundMesh.cpp
//
//  Created by rayyyhuang on 2021/6/7.
//

#include "SCFilterBackgroundMesh.hpp"
#include "FilterFactory.hpp"
#include "SCFilterMesh.hpp"

namespace effect {

SCFilterBackgroundMesh::SCFilterBackgroundMesh() : FilterChain(FilterFactory::getChainDescByType("BackgroundMeshFilter")){
    
}

void SCFilterBackgroundMesh::setMesh(std::vector<BasePoint> mesh, std::vector<BasePoint> meshStd, unsigned int *meshIndex, int indexArrayCount) {
    for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        if (filterNode->id == "SCFilterMesh") {
            std::shared_ptr<SCFilterMesh> meshFilter = std::static_pointer_cast<SCFilterMesh>(filterNode->filter);
            meshFilter->setMesh(mesh, meshStd, meshIndex, indexArrayCount);
        }
    }
}

}
