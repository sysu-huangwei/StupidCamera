//
//  FilterNode.cpp
//
//  Created by rayyy on 2021/9/24.
//

#include "FilterNode.hpp"
#include "FilterFactory.hpp"

namespace effect {

FilterNode::FilterNode(const FilterNodeDescription &nodeDesc) {
    id = nodeDesc.id;
    if (nodeDesc.id != defaultBeginID) {
        filter = FilterFactory::createFilter(nodeDesc.filterDesc);
    }
}

std::string FilterNode::getID() {
    return id;
}

void FilterNode::resize(int width, int height) {
    filter->resize(width, height);
}

void FilterNode::render() {
    if (id == defaultBeginID) {
        informNextNodesToRender();
        return;
    }
    if (outputFrameBuffer) {
        filter->renderToFrameBuffer(outputFrameBuffer);
        setResultFrameBufferToNextNodes(outputFrameBuffer);
    } else {
        std::shared_ptr<FrameBuffer> output = filter->render();
        setResultFrameBufferToNextNodes(output);
        output->unlock();
    }
    informNextNodesToRender();
}

void FilterNode::setParams(const std::map<std::string, std::string> &param) {
    filter->setParams(param);
}

void FilterNode::setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    this->outputFrameBuffer = outputFrameBuffer;
}

void FilterNode::setResultFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output) {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->filter->setInputFrameBufferAtIndex(output, nextIndices[i]);
    }
}

void FilterNode::informNextNodesToRender() {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        if (nextNodes[i]->filter->isAllInputReady()) {
            nextNodes[i]->render();
        }
    }
}

}
