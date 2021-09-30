//
//  SmoothFilter.cpp
//
//  Created by Ray on 2021/8/22.
//

#include "SmoothFilter.hpp"
#include "FilterFactory.hpp"
#include "MixFilter.hpp"

namespace effect {

SmoothFilter::SmoothFilter() : FilterChain(FilterFactory::getChainDescByType("SmoothFilter")) {
    
}

void SmoothFilter::setParams(const std::map<std::string, std::string> &param) {
    if (param.find(FilterParam_Blur_Alpha) != param.end()) {
        for (const std::shared_ptr<FilterNode> &node : allNodes) {
            if (node->getID() == "mix") {
                node->setParams({{FilterParam_Mix_Alpha, param.at(FilterParam_Blur_Alpha)}});
            }
        }
    }
}

}
