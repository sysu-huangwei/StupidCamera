//
//  FrameBufferPool.hpp
//
//  Created by Ray on 2021/7/3.
//

#ifndef FrameBufferPool_hpp
#define FrameBufferPool_hpp

#include <string>
#include <map>
#include <mutex>
#include "FrameBuffer.hpp"

class FrameBufferPool {
public:
    
    static std::shared_ptr<FrameBufferPool> getSharedInstance();
    
    FrameBuffer *fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture = false, GLuint textureID = 0, GLuint frameBufferID = 0);
    
    void returnFrameBufferToPool(FrameBuffer *frameBuffer);
    
    void clearFrameBufferPool();
    
private:
    
    std::map<std::string, FrameBuffer *> frameBufferCache;
};

#endif /* FrameBufferPool_hpp */
