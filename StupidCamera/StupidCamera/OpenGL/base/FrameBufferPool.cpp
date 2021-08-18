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
    FrameBuffer *frameBuffer = nullptr;
    std::string key =
            std::to_string(width)
            + "_" + std::to_string(height)
            + "_" + std::to_string(isOnlyTexture)
            + "_" + std::to_string(textureID)
            + "_" + std::to_string(frameBufferID);
    if (frameBufferCache.find(key) != frameBufferCache.end()) {
        std::vector<FrameBuffer *> frameBuffers = frameBufferCache.at(key);
        if (!frameBuffers.empty()) {
            frameBuffer = frameBuffers.back();
            frameBuffers.pop_back();
            if (frameBuffers.empty()) {
                frameBufferCache.erase(key);
            }
        }
    } else {
        frameBuffer = new FrameBuffer();
        frameBuffer->init(width, height, isOnlyTexture, textureID, frameBufferID);
        frameBuffer->setEnableReferenceCount(true);
    }
    frameBuffer->lock();
    return frameBuffer;
}

void FrameBufferPool::returnFrameBufferToPool(FrameBuffer *frameBuffer) {
    if (frameBuffer) {
        frameBuffer->referenceCount = 0;
        std::string key =
                std::to_string(frameBuffer->getWidth())
                + "_" + std::to_string(frameBuffer->getHeight())
                + "_" + std::to_string(frameBuffer->getIsOnlyTexture())
                + "_" + std::to_string(frameBuffer->getTextureID())
                + "_" + std::to_string(frameBuffer->getFrameBufferID());
        if (frameBufferCache.find(key) != frameBufferCache.end()) {
            std::vector<FrameBuffer *> frameBuffers = frameBufferCache.at(key);
            frameBufferCache.at(key).push_back(frameBuffer);
        } else {
            std::vector<FrameBuffer *> frameBuffers {frameBuffer};
            frameBufferCache[key] = frameBuffers;
        }
    }
}

void FrameBufferPool::clearFrameBufferPool() {
    std::map<std::string, std::vector<FrameBuffer *> >::iterator it;
    for (it = frameBufferCache.begin(); it != frameBufferCache.end(); it++) {
        std::vector<FrameBuffer *> frameBuffers = (*it).second;
        for (FrameBuffer *frameBuffer : frameBuffers) {
            frameBuffer->release();
            SAFE_DELETE(frameBuffer);
        }
    }
    frameBufferCache.clear();
}
