//
//  BlurFilter.cpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#include "BlurFilter.hpp"
#include "FilterFactory.hpp"

namespace effect {

BlurFilter::BlurFilter() : FilterChain(FilterFactory::getChainDescByType("BlurFilter")) {
    
}

void BlurFilter::resize(int width, int height) {
    scaleWH(width, height);
    FilterChain::resize(width, height);
    for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->resize(width, height);
    }
}

void BlurFilter::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}

}
