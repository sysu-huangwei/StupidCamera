//
//  FrameBufferPool.cpp
//
//  Created by Ray on 2021/7/3.
//

#include "FrameBufferPool.hpp"
#include <mutex>
#include "SCBaseLog.h"

static std::shared_ptr<FrameBufferPool> frameBufferPoolSharedInstance;
static std::mutex frameBufferPoolSharedInstanceLock;

std::shared_ptr<FrameBufferPool> FrameBufferPool::getSharedInstance() {
    if (frameBufferPoolSharedInstance == nullptr) {
        std::lock_guard<std::mutex> lock(frameBufferPoolSharedInstanceLock);
        if (frameBufferPoolSharedInstance == nullptr) {
            frameBufferPoolSharedInstance = std::make_shared<FrameBufferPool>();
        }
    }
    return frameBufferPoolSharedInstance;
}

FrameBuffer *FrameBufferPool::fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture, GLuint textureID, GLuint frameBufferID) {
    std::string key =
            std::to_string(width)
            + "_" + std::to_string(height)
            + "_" + std::to_string(isOnlyTexture)
            + "_" + std::to_string(textureID)
            + "_" + std::to_string(frameBufferID);
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
        std::string key =
                std::to_string(frameBuffer->getWidth())
                + "_" + std::to_string(frameBuffer->getHeight())
                + "_" + std::to_string(frameBuffer->getIsOnlyTexture())
                + "_" + std::to_string(frameBuffer->getTextureID())
                + "_" + std::to_string(frameBuffer->getFrameBufferID());
        if (frameBufferCache.find(key) != frameBufferCache.end()) {
            frameBuffer->unlock();
        } else {
            LOGE("Error: FrameBufferPool::returnFrameBufferToPool  frameBuffer not exist in pool key = %s", key.c_str());
        }
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
