//
//  FrameBufferPool.cpp
//
//  Created by Ray on 2021/7/3.
//

#include "FrameBufferPool.hpp"

static std::shared_ptr<FrameBufferPool> sharedInstance;
static std::mutex sharedInstanceLock;

std::shared_ptr<FrameBufferPool> FrameBufferPool::getSharedInstance() {
    if (sharedInstance == nullptr) {
        std::lock_guard<std::mutex> lock(sharedInstanceLock);
        if (sharedInstance == nullptr) {
            sharedInstance = std::make_shared<FrameBufferPool>();
        }
    }
    return sharedInstance;
}

FrameBuffer *FrameBufferPool::fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture, GLuint textureID, GLuint frameBufferID) {
    std::string key = std::to_string(width) + "_" + std::to_string(height) + "_" + std::to_string(isOnlyTexture) + "_" + std::to_string(textureID) + "_" + std::to_string(frameBufferID);
    if (frameBufferCache.find(key) != frameBufferCache.end()) {
        frameBufferCache.at(key)->lock();
        return frameBufferCache.at(key);
    } else {
        FrameBuffer *frameBuffer = new FrameBuffer();
        frameBuffer->init(width, height, isOnlyTexture, textureID, frameBufferID);
        frameBuffer->lock();
        frameBufferCache[key] = frameBuffer;
        return frameBuffer;
    }
}

void FrameBufferPool::returnFrameBufferToPool(FrameBuffer *frameBuffer) {
    if (frameBuffer) {
        frameBuffer->unlock();
    }
}

void FrameBufferPool::clearFrameBufferPool() {
    std::map<std::string, FrameBuffer *>::iterator it;
    for (it = frameBufferCache.begin(); it != frameBufferCache.end();) {
        if ((*it).second->referenceCount == 0) {
            (*it).second->release();
            SAFE_DELETE((*it).second);
            frameBufferCache.erase(it++);
        } else {
            it++;
        }
    }
}
