//
//  FilterChain.cpp
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterChain.hpp"
#include "FilterFactory.hpp"

namespace effect {

using namespace std;

FilterChain::FilterChain(const std::vector<FilterNodeDescription> &nodeDescriptions) : nodeDescriptions(nodeDescriptions) {
    
}

void FilterChain::init() {
    map<string, vector<string>> nodeIDToNextIDs;
    map<string, vector<int>> nodeIDToNextIndices;
    map<string, shared_ptr<FilterNode>> nodeIDToNode;
    
    for (size_t i = 0; i < nodeDescriptions.size(); i++) {
        const FilterNodeDescription &nodeDescription = nodeDescriptions[i];
        nodeIDToNextIDs[nodeDescription.id] = nodeDescription.nextIDs;
        nodeIDToNextIndices[nodeDescription.id] = nodeDescription.nextTextureIndices;
        
        shared_ptr<FilterNode> filterNode = make_shared<FilterNode>(nodeDescription);
        
        if (nodeDescription.id != defaultBeginID) {
            filterNode->filter->init();
            allNodes.push_back(filterNode);
        } else {
            beginVirtualNode = filterNode;
        }
        
        if (nodeDescription.nextIDs.empty()) {
            lastNodes.push_back(filterNode);
        }
        
        nodeIDToNode[nodeDescription.id] = filterNode;
    }
    
    for (auto it = nodeIDToNextIDs.begin(); it != nodeIDToNextIDs.end(); it++) {
        const string &nodeID = (*it).first;
        const vector<string> &nextIDs = (*it).second;
        for (const string &nextID : nextIDs) {
            nodeIDToNode[nodeID]->nextNodes.push_back(nodeIDToNode[nextID]);
            nodeIDToNode[nodeID]->nextIndices = nodeIDToNextIndices[nodeID];
        }
    }
    
}

void FilterChain::release() {
    for (size_t i = 0; i < allNodes.size(); i++) {
        allNodes[i]->filter->release();
    }
}

void FilterChain::setOutputSize(int outputWidth, int outputHeight) {
    BaseFilter::setOutputSize(outputWidth, outputHeight);
    for (size_t i = 0; i < lastNodes.size(); i++) {
        lastNodes[i]->filter->setOutputSize(outputWidth, outputHeight);
    }
}

void FilterChain::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (isNeedRender() && outputFrameBuffer) {
        for (size_t i = 0; i < lastNodes.size(); i++) {
            lastNodes[i]->setOutputFrameBuffer(outputFrameBuffer);
        }
        
        for (size_t j = 0; j < inputFrameBuffers.size(); j++) {
            beginVirtualNode->setResultFrameBufferToNextNodes(inputFrameBuffers[j]);
        }
        
        beginVirtualNode->render();
    }
    
    unlockAndClearAllInputFrameBuffers();
}

bool FilterChain::isAllInputReady() {
    return true;
}

}
