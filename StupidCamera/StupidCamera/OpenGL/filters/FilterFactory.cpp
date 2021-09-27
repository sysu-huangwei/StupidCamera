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
#include "SCFilterMesh.hpp"
#include "SCFilterMix.hpp"
#include "SCFilterSmooth.hpp"

namespace effect {
    
std::shared_ptr<SCFilterBase> FilterFactory::createFilter(const FilterDescription &filterDesc) {
    std::shared_ptr<SCFilterBase> filter = nullptr;
    
    if (filterDesc.type == "SCFilterCopy") {
        filter = std::make_shared<SCFilterCopy>();
    } else if (filterDesc.type == "SCFilterBlurSub") {
        filter = std::make_shared<SCFilterBlurSub>();
    } else if (filterDesc.type == "SCFilterBlur") {
        filter = std::make_shared<SCFilterBlur>();
    } else if (filterDesc.type == "SCFilterMesh") {
        filter = std::make_shared<SCFilterMesh>();
    } else if (filterDesc.type == "SCFilterMix") {
        filter = std::make_shared<SCFilterMix>();
    } else if (filterDesc.type == "SCFilterSmooth") {
        filter = std::make_shared<SCFilterSmooth>();
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
        begin.nextIDs.push_back("blurH");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blurH;
        blurH.id = "blurH";
        blurH.nextIDs.push_back("blurV");
        blurH.nextTextureIndices.push_back(0);
        blurH.filterDesc.type = "SCFilterBlurSub";
        
        FilterNodeDescription blurV;
        blurV.id = "blurV";
        blurV.filterDesc.type = "SCFilterBlurSub";
        
        chainDesc.push_back(begin);
        chainDesc.push_back(blurH);
        chainDesc.push_back(blurV);
        
    } else if (type == "BackgroundMeshFilter") {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("copy");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("mesh");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription copy;
        copy.id = "copy";
        copy.filterDesc.type = "SCFilterCopy";
        
        FilterNodeDescription mesh;
        mesh.id = "mesh";
        mesh.filterDesc.type = "SCFilterMesh";
        
        chainDesc.push_back(begin);
        chainDesc.push_back(copy);
        chainDesc.push_back(mesh);
        
    } else if (type == "SmoothFilter") {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("mix");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("blur");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blur;
        blur.id = "blur";
        blur.nextIDs.push_back("mix");
        blur.nextTextureIndices.push_back(1);
        blur.filterDesc.type = "SCFilterBlur";
        
        FilterNodeDescription mix;
        mix.id = "mix";
        mix.filterDesc.type = "SCFilterMix";
        
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
