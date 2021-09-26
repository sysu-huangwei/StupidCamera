//
//  SCFilterBlur.cpp
//
//  Created by rayyyhuang on 2021/8/16.
//

#include "SCFilterBlur.hpp"
#include "SCFilterBlurSub.hpp"

namespace effect {

FilterDescription defaultBlurSubFilterDescription { "SCFilterBlurSub", 0, 0, true };
FilterNodeDescription defaultBlurSubVNodeDescription { "SCFilterBlurSubV", {}, {}, defaultBlurSubFilterDescription };
FilterNodeDescription defaultBlurSubHNodeDescription { "SCFilterBlurSubH", { "SCFilterBlurSubV" }, { 0 }, defaultBlurSubFilterDescription };
FilterNodeDescription defaultBlurSubBeginNodeDescription { defaultBeginID, { "SCFilterBlurSubH" }, { 0 } };
std::vector<FilterNodeDescription> defaultBlurNodeDescriptions = { defaultBlurSubBeginNodeDescription, defaultBlurSubHNodeDescription, defaultBlurSubVNodeDescription };

SCFilterBlur::SCFilterBlur() : FilterChain(defaultBlurNodeDescriptions) {
}

void SCFilterBlur::resize(int width, int height) {
    scaleWH(width, height);
    FilterChain::resize(width, height);
    for (const std::shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->filter->resize(width, height);
        if (filterNode->id == "SCFilterBlurSubH") {
            std::shared_ptr<SCFilterBlurSub> blurFilterH = std::static_pointer_cast<SCFilterBlurSub>(filterNode->filter);
            blurFilterH->setOffset(1.0f / (float)width, 0);
        }
        if (filterNode->id == "SCFilterBlurSubV") {
            std::shared_ptr<SCFilterBlurSub> blurFilterV = std::static_pointer_cast<SCFilterBlurSub>(filterNode->filter);
            blurFilterV->setOffset(0, 1.0f / (float)height);
        }
    }
}

void SCFilterBlur::scaleWH(int &width, int &height, int maxLength) {
    int shortEdge = std::min(width, height);
    float scale = (float)maxLength / (float)shortEdge;
    width = (int)((float)width * scale);
    height = (int)((float)height * scale);
}

}
