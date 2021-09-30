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

void BlurFilter::setOutputSize(int outputWidth, int outputHeight) {
    scaleWH(outputWidth, outputHeight);
    FilterChain::setOutputSize(outputWidth, outputHeight);
    for (const std::shared_ptr<FilterNode> &node : allNodes) {
        node->setOutputSize(outputWidth, outputHeight);
    }
}

void BlurFilter::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}

}
