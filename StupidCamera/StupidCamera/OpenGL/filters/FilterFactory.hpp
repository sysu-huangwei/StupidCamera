//
//  FilterFactory.hpp
//
//  Created by rayyy on 2021/9/23.
//

#ifndef FilterFactory_hpp
#define FilterFactory_hpp

#include <memory>
#include "BaseFilter.hpp"
#include "FilterDescription.hpp"
#include "FilterChain.hpp"

namespace effect {

/// 滤镜构造
class FilterFactory {
public:
    
    /// 根据滤镜描述，创建滤镜
    /// @param filterDesc 滤镜的描述
    static std::shared_ptr<BaseFilter> createFilter(const FilterDescription &filterDesc);
    
    /// 根据滤镜链类型，返回滤镜链的完整描述（主要用于内置的滤镜链）
    /// @param type 滤镜类型
    static std::vector<FilterNodeDescription> getChainDescByType(const std::string &type);
    
};

}

#endif /* FilterFactory_hpp */
