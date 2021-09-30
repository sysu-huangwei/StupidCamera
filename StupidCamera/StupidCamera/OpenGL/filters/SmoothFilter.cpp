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
        std::shared_ptr<BaseFilter> mixFilter = getFilterByNodeID("mix");
        if (mixFilter) {
            mixFilter->setParams({{FilterParam_Mix_Alpha, param.at(FilterParam_Blur_Alpha)}});
        }
    }
}

}
