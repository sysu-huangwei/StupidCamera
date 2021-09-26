//
//  FilterFactory.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterFactory_hpp
#define FilterFactory_hpp

#include <memory>
#include "SCFilterBase.hpp"
#include "FilterDescription.hpp"
#include "FilterChain.hpp"

namespace effect {

/// 滤镜构造
class FilterFactory {
public:
    
    static std::shared_ptr<SCFilterBase> createFilter(const FilterDescription &filterDesc);
    
    static std::vector<FilterNodeDescription> getChainDescByType(const std::string &type);
    
};

}

#endif /* FilterFactory_hpp */
