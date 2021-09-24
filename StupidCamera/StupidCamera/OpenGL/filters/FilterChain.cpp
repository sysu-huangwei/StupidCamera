//
//  FilterChain.cpp
//  StupidCamera
//
//  Created by rayyy on 2021/9/23.
//

#include "FilterChain.hpp"
#include "FilterFactory.hpp"

namespace effect {

using namespace std;

FilterChain::FilterChain(const std::vector<FilterNodeDescription> nodeDescriptions) {
    map<string, vector<string>> nodeIDToNextIDs;
    map<string, vector<int>> nodeIDToNextIndices;
    map<string, shared_ptr<FilterNode>> nodeIDToNode;
    
    for (const FilterNodeDescription &nodeDescription : nodeDescriptions) {
        nodeIDToNextIDs[nodeDescription.id] = nodeDescription.nextIDs;
        nodeIDToNextIndices[nodeDescription.id] = nodeDescription.nextTextureIndices;
        
        if (nodeDescription.id != defaultBeginID) {
            shared_ptr<SCFilterBase> filter = FilterFactory::createFilter(nodeDescription.filterDesc);
            shared_ptr<FilterNode> filterNode = make_shared<FilterNode>(nodeDescription.id, filter);
            allFilterNodes.push_back(filterNode);
            nodeIDToNode[nodeDescription.id] = filterNode;
            
            if (nodeDescription.nextIDs.empty()) {
                lastNode = filterNode;
            }
        } else {
            beginVirtualNode = make_shared<FilterNode>();
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

void FilterChain::setInputFrameBuffer(std::shared_ptr<FrameBuffer> inputFrameBuffer) {
    for (std::shared_ptr<FilterNode> filterNode : beginVirtualNode->nextNodes) {
        filterNode->filter->setInputFrameBufferAtIndex(inputFrameBuffer, 0);
    }
}

void FilterChain::renderToFrameBuffer(std::shared_ptr<FrameBuffer> outputFrameBuffer) {
    lastNode->setOutputFrameBuffer(outputFrameBuffer);
    for (const shared_ptr<FilterNode> &filterNode : allFilterNodes) {
        filterNode->filter->render();
    }
}

}
