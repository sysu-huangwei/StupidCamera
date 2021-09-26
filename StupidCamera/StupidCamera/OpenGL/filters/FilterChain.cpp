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
    
    for (const FilterNodeDescription &nodeDescription : nodeDescriptions) {
        nodeIDToNextIDs[nodeDescription.id] = nodeDescription.nextIDs;
        nodeIDToNextIndices[nodeDescription.id] = nodeDescription.nextTextureIndices;
        
        if (nodeDescription.id != defaultBeginID) {
            shared_ptr<FilterNode> filterNode = make_shared<FilterNode>(nodeDescription);
            allFilterNodes.push_back(filterNode);
            nodeIDToNode[nodeDescription.id] = filterNode;
            
            if (nodeDescription.nextIDs.empty()) {
                lastNode = filterNode;
            }
        } else {
            beginVirtualNode = make_shared<FilterNode>(defaultBeginNodeDescription);
            nodeIDToNode[defaultBeginID] = beginVirtualNode;
        }
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
    for (const shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->filter->release();
    }
}

void FilterChain::resize(int width, int height) {
    lastNode->filter->resize(width, height);
}

void FilterChain::setInputFrameBufferAtIndex(shared_ptr<FrameBuffer> inputFrameBuffer, int index) {
    for (std::shared_ptr<FilterNode> filterNode : beginVirtualNode->nextNodes) {
        filterNode->filter->setInputFrameBufferAtIndex(inputFrameBuffer, index);
    }
}

void FilterChain::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    if (!isNeedRender() || !outputFrameBuffer) {
        return;
    }
    
    lastNode->setOutputFrameBuffer(outputFrameBuffer);
    for (const shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->filter->render();
    }
}

}
