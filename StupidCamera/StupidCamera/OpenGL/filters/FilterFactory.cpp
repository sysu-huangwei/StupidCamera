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
#include "SCFilterMix.hpp"
#include "SCFilterSmooth.hpp"
#include "SCFilterMesh.hpp"
#include "SCFilterBackgroundMesh.hpp"

namespace effect {
    
std::shared_ptr<SCFilterBase> FilterFactory::createFilter(const FilterDescription &filterDesc) {
    std::shared_ptr<SCFilterBase> filter = nullptr;
    
    if (filterDesc.type == SCFilterType_Copy) {
        filter = std::make_shared<SCFilterCopy>();
    } else if (filterDesc.type == SCFilterType_BlurSub) {
        filter = std::make_shared<SCFilterBlurSub>();
    } else if (filterDesc.type == SCFilterType_Blur) {
        filter = std::make_shared<SCFilterBlur>();
    } else if (filterDesc.type == SCFilterType_Mix) {
        filter = std::make_shared<SCFilterMix>();
    } else if (filterDesc.type == SCFilterType_Smooth) {
        filter = std::make_shared<SCFilterSmooth>();
    } else if (filterDesc.type == SCFilterType_Mesh) {
        filter = std::make_shared<SCFilterMesh>();
    } else if (filterDesc.type == SCFilterType_BackgroundMesh) {
        filter = std::make_shared<SCFilterBackgroundMesh>();
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
    
    if (type == SCFilterType_Blur) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("blurH");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blurH;
        blurH.id = "blurH";
        blurH.nextIDs.push_back("blurV");
        blurH.nextTextureIndices.push_back(0);
        blurH.filterDesc.type = SCFilterType_BlurSub;
        
        FilterNodeDescription blurV;
        blurV.id = "blurV";
        blurV.filterDesc.type = SCFilterType_BlurSub;
        
        chainDesc.push_back(begin);
        chainDesc.push_back(blurH);
        chainDesc.push_back(blurV);
        
    } else if (type == SCFilterType_BackgroundMesh) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("copy");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("mesh");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription copy;
        copy.id = "copy";
        copy.filterDesc.type = SCFilterType_Copy;
        
        FilterNodeDescription mesh;
        mesh.id = "mesh";
        mesh.filterDesc.type = SCFilterType_Mesh;
        
        chainDesc.push_back(begin);
        chainDesc.push_back(copy);
        chainDesc.push_back(mesh);
        
    } else if (type == SCFilterType_Smooth) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("mix");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("blur");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blur;
        blur.id = "blur";
        blur.nextIDs.push_back("mix");
        blur.nextTextureIndices.push_back(1);
        blur.filterDesc.type = SCFilterType_Blur;
        
        FilterNodeDescription mix;
        mix.id = "mix";
        mix.filterDesc.type = SCFilterType_Mix;
        
        chainDesc.push_back(begin);
        chainDesc.push_back(blur);
        chainDesc.push_back(mix);
        
    } else {
        LOGE("Error: FilterFactory::getChainDescByType: invalid chain type = %s", type.c_str());
        assert(false);
    }
    
    return chainDesc;
}

}
