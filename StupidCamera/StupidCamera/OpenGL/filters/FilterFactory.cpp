//
//  FilterFactory.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterFactory.hpp"

#include "BaseLog.h"

#include "SCFilterCopy.hpp"
#include "SCFilterBlurSub.hpp"
#include "SCFilterBlur.hpp"

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

std::vector<FilterNodeDescription> FilterFactory::getChainDescByType(const std::string &type) {
    std::vector<FilterNodeDescription> chainDesc;
    
    if (type == "BlurFilter") {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("SCFilterBlurSubH");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blurSubH;
        blurSubH.id = "SCFilterBlurSubH";
        blurSubH.filterDesc.type = "SCFilterBlurSub";
        blurSubH.nextIDs.push_back("SCFilterBlurSubV");
        blurSubH.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blurSubV;
        blurSubV.filterDesc.type = "SCFilterBlurSub";
        blurSubV.id = "SCFilterBlurSubV";
        
        chainDesc.push_back(begin);
        chainDesc.push_back(blurSubH);
        chainDesc.push_back(blurSubV);
    } else {
        LOGE("Error: FilterFactory::getChainDescByType: invalid chain type = %s", type.c_str());
        assert(false);
    }
    
    return chainDesc;
}

}
