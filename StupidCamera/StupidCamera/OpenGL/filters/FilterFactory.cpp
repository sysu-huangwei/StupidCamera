//
//  FilterFactory.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterFactory.hpp"

#include "BaseLog.h"

#include "SCFilterCopy.hpp"
#include "SCFilterBlurSub.hpp"

namespace effect {
    
std::shared_ptr<SCFilterBase> FilterFactory::createFilter(const FilterDescription &filterDesc) {
    std::shared_ptr<SCFilterBase> filter = nullptr;
    
    if (filterDesc.type == "SCFilterType_Copy") {
        filter = std::make_shared<SCFilterCopy>();
    } else if (filterDesc.type == "SCFilterBlurSub") {
        filter = std::make_shared<SCFilterBlurSub>();
    } else {
        LOGE("Error: FilterFactory::createFilter: invalid filter type = %s", filterDesc.type.c_str());
        assert(false);
    }
    
    filter->setEnableRender(filterDesc.enable);
    filter->resize(filterDesc.outputWidth, filterDesc.outputHeight);
    filter->setParams(filterDesc.params);
    
    return filter;
}

}
