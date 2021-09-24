//
//  FilterNode.cpp
//
//  Created by rayyy on 2021/9/24.
//

#include "FilterNode.hpp"

namespace effect {

void FilterNode::setInputFrameBufferAtIndex(std::shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    filter->setInputFrameBufferAtIndex(inputFrameBuffer, index);
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
    informNextNodesToRender();
}

void FilterNode::setOutputFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    this->outputFrameBuffer = outputFrameBuffer;
}

void FilterNode::setOutputFrameBufferToNextNodes(std::shared_ptr<FrameBuffer> output) {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->setInputFrameBufferAtIndex(output, nextIndices[i]);
    }
}

void FilterNode::informNextNodesToRender() {
    for (size_t i = 0; i < nextNodes.size(); i++) {
        nextNodes[i]->render();
    }
}

}