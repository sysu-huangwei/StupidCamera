//
//  SCFilterBlur.cpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#include "SCFilterBlur.hpp"
#include "SCFilterBlurSub.hpp"
#include "FilterFactory.hpp"

namespace effect {

SCFilterBlur::SCFilterBlur() : FilterChain(FilterFactory::getChainDescByType("BlurFilter")) {
    
}

void SCFilterBlur::resize(int width, int height) {
    scaleWH(width, height);
    FilterChain::resize(width, height);
    for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->filter->resize(width, height);
        if (filterNode->id == "blurH") {
            std::shared_ptr<SCFilterBlurSub> blurFilterH = std::static_pointer_cast<SCFilterBlurSub>(filterNode->filter);
            blurFilterH->setOffset(1.0f / (float)width, 0);
        }
        if (filterNode->id == "blurV") {
            std::shared_ptr<SCFilterBlurSub> blurFilterV = std::static_pointer_cast<SCFilterBlurSub>(filterNode->filter);
            blurFilterV->setOffset(0, 1.0f / (float)height);
        }
    }
}

void SCFilterBlur::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}

}
