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

namespace effect {

/// 滤镜构造
class FilterFactory {
public:
    
    static std::shared_ptr<SCFilterBase> createFilter(const FilterDescription &filterDesc);
};

}

#endif /* FilterFactory_hpp */
