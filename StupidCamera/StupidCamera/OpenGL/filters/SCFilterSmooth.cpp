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
    std::map<std::string, std::string>::const_iterator it;
    for (it = param.begin(); it != param.end(); it++) {
        if ((*it).first == SCFilterParam_BlurAlpha) {
            alpha = std::stof((*it).second);
            for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
                if (filterNode->id == "mix") {
                    std::shared_ptr<SCFilterMix> mixFilter = std::static_pointer_cast<SCFilterMix>(filterNode->filter);
                    mixFilter->setAlpha(alpha);
                }
            }
        }
    }
}

}
