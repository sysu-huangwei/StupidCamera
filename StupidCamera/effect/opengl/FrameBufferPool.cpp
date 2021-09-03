//
//  FrameBufferPool.cpp
//
//  Created by rayyyhuang on 2021/7/3.
//

#include "FrameBufferPool.hpp"
#include <mutex>
#include "BaseDefine.h"

namespace effect {

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

FrameBuffer *FrameBufferPool::fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture, TextureOptions textureOptions) {
    FrameBuffer *frameBuffer = nullptr;
    std::string key = getTextureKey(width, height, isOnlyTexture, textureOptions);
    if (frameBufferCache.find(key) != frameBufferCache.end()) {
        std::vector<FrameBuffer *> &frameBuffers = frameBufferCache.at(key);
        if (!frameBuffers.empty()) {
            frameBuffer = frameBuffers.back();
            frameBuffers.pop_back();
            if (frameBuffers.empty()) {
                frameBufferCache.erase(key);
            }
        }
    } else {
        frameBuffer = new FrameBuffer();
        frameBuffer->init(width, height, isOnlyTexture, textureOptions);
        frameBuffer->setEnableReferenceCount(true);
    }
    frameBuffer->lock();
    return frameBuffer;
}

void FrameBufferPool::returnFrameBufferToPool(FrameBuffer *frameBuffer) {
    if (frameBuffer) {
        frameBuffer->referenceCount = 0;
        std::string key = getTextureKey(frameBuffer->getWidth(), frameBuffer->getHeight(), frameBuffer->getIsOnlyTexture(), frameBuffer->getTextureOptions());
        if (frameBufferCache.find(key) != frameBufferCache.end()) {
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


std::string FrameBufferPool::getTextureKey(int width, int height, bool isOnlyTexture, TextureOptions textureOptions) {
    std::string key;
    key += std::to_string(width) + "_";
    key += std::to_string(height) + "_";
    key += std::to_string(isOnlyTexture) + "_";
    key += std::to_string(textureOptions.minFilter) + "_";
    key += std::to_string(textureOptions.magFilter) + "_";
    key += std::to_string(textureOptions.wrapS) + "_";
    key += std::to_string(textureOptions.wrapT) + "_";
    key += std::to_string(textureOptions.internalFormat) + "_";
    key += std::to_string(textureOptions.format) + "_";
    key += std::to_string(textureOptions.type) + "_";
    return key;
}

}
