//
//  FilterFactory.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterFactory.hpp"

#include "BaseLog.h"

#include "CopyFilter.hpp"
#include "BlurSubFilter.hpp"
#include "BlurFilter.hpp"
#include "MixFilter.hpp"
#include "SmoothFilter.hpp"
#include "MeshFilter.hpp"
#include "BackgroundMeshFilter.hpp"

namespace effect {
    
std::shared_ptr<BaseFilter> FilterFactory::createFilter(const FilterDescription &filterDesc) {
    std::shared_ptr<BaseFilter> filter = nullptr;
    
    if (filterDesc.type == FilterType_Copy) {
        filter = std::make_shared<CopyFilter>();
    } else if (filterDesc.type == FilterType_BlurSub) {
        filter = std::make_shared<BlurSubFilter>();
    } else if (filterDesc.type == FilterType_Blur) {
        filter = std::make_shared<BlurFilter>();
    } else if (filterDesc.type == FilterType_Mix) {
        filter = std::make_shared<MixFilter>();
    } else if (filterDesc.type == FilterType_Smooth) {
        filter = std::make_shared<SmoothFilter>();
    } else if (filterDesc.type == FilterType_Mesh) {
        filter = std::make_shared<MeshFilter>();
    } else if (filterDesc.type == FilterType_BackgroundMesh) {
        filter = std::make_shared<BackgroundMeshFilter>();
    } else {
        LOGE("Error: FilterFactory::createFilter: invalid filter type = %s", filterDesc.type.c_str());
        assert(false);
    }
    
    filter->setEnableRender(filterDesc.enable);
    filter->setOutputSize(filterDesc.outputWidth, filterDesc.outputHeight);
    filter->setParams(filterDesc.params);
    
    return filter;
}

std::vector<FilterNodeDescription> FilterFactory::getChainDescByType(const std::string &type) {
    std::vector<FilterNodeDescription> chainDesc;
    
    if (type == FilterType_Blur) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("blurH");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blurH;
        blurH.id = "blurH";
        blurH.nextIDs.push_back("blurV");
        blurH.nextTextureIndices.push_back(0);
        blurH.filterDesc.type = FilterType_BlurSub;
        blurH.filterDesc.params = {{FilterParam_BlurSub_Direction, std::to_string(BlurSubFilter::BlurDirection_Horizontal)}};
        
        FilterNodeDescription blurV;
        blurV.id = "blurV";
        blurV.filterDesc.type = FilterType_BlurSub;
        blurH.filterDesc.params = {{FilterParam_BlurSub_Direction, std::to_string(BlurSubFilter::BlurDirection_Vertical)}};
        
        chainDesc.push_back(begin);
        chainDesc.push_back(blurH);
        chainDesc.push_back(blurV);
        
    } else if (type == FilterType_BackgroundMesh) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("copy");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("mesh");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription copy;
        copy.id = "copy";
        copy.filterDesc.type = FilterType_Copy;
        
        FilterNodeDescription mesh;
        mesh.id = "mesh";
        mesh.filterDesc.type = FilterType_Mesh;
        
        chainDesc.push_back(begin);
        chainDesc.push_back(copy);
        chainDesc.push_back(mesh);
        
    } else if (type == FilterType_Smooth) {
        FilterNodeDescription begin = defaultBeginNodeDescription;
        begin.nextIDs.push_back("mix");
        begin.nextTextureIndices.push_back(0);
        begin.nextIDs.push_back("blur");
        begin.nextTextureIndices.push_back(0);
        
        FilterNodeDescription blur;
        blur.id = "blur";
        blur.nextIDs.push_back("mix");
        blur.nextTextureIndices.push_back(1);
        blur.filterDesc.type = FilterType_Blur;
        
        FilterNodeDescription mix;
        mix.id = "mix";
        mix.filterDesc.type = FilterType_Mix;
        
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
