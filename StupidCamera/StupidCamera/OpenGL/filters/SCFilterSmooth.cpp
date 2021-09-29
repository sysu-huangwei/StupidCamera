//
//  SCFilterSmooth.cpp
//
//  Created by Ray on 2021/8/22.
//

#include "SCFilterSmooth.hpp"
#include "FilterFactory.hpp"
#include "SCFilterMix.hpp"

namespace effect {

SCFilterSmooth::SCFilterSmooth() : FilterChain(FilterFactory::getChainDescByType("SmoothFilter")) {
    
}

void SCFilterSmooth::setParams(const std::map<std::string, std::string> &param) {
    if (param.find(SCFilterParam_Blur_Alpha) != param.end()) {
        for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
            if (filterNode->getID() == "mix") {
                filterNode->setParams({{SCFilterParam_Mix_Alpha, param.at(SCFilterParam_Blur_Alpha)}});
            }
        }
    }
}

}
