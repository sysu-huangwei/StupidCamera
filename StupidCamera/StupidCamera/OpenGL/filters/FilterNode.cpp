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

void FilterNode::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    filter->setInputFrameBufferAtIndex(inputFrameBuffer, index);
}

void FilterNode::render() {
    std::shared_ptr<FrameBuffer> output;
    if (outputFrameBuffer) {
        output = outputFrameBuffer;
        filter->renderToFrameBuffer(output);
    } else {
        output = filter->render();
        output->unlock();
    }
    setOutputFrameBufferToNextNodes(output);
    informNextNodesToRender();
}

void FilterNode::setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    this->outputFrameBuffer = outputFrameBuffer;
}

void FilterNode::setOutputFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output) {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->setInputFrameBufferAtIndex(output, nextIndices[i]);
        nextNodes[i]->filter->resize(output->getWidth(), output->getHeight());
    }
}

void FilterNode::informNextNodesToRender() {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->render();
    }
}

}
