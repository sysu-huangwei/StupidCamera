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


void FilterNode::render() {
    if (outputFrameBuffer) {
        filter->renderToFrameBuffer(outputFrameBuffer);
        setOutputFrameBufferToNextNodes(outputFrameBuffer);
    } else {
        std::shared_ptr<FrameBuffer> output = filter->render();
        setOutputFrameBufferToNextNodes(output);
        output->unlock();
    }
}

void FilterNode::setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    this->outputFrameBuffer = outputFrameBuffer;
}

void FilterNode::setOutputFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output) {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->filter->setInputFrameBufferAtIndex(output, nextIndices[i]);
        nextNodes[i]->filter->resize(output->getWidth(), output->getHeight());
        if (nextNodes[i]->filter->isAllInputReady()) {
            nextNodes[i]->render();
        }
    }
}

}
