//
//  FrameBufferPool.hpp
//
//  Created by Ray on 2021/7/3.
//

#ifndef FrameBufferPool_hpp
#define FrameBufferPool_hpp

#include <string>
#include <map>
#include "FrameBuffer.hpp"

/// 全局FBO缓存池
class FrameBufferPool {
public:
    
    /// 获取全局单例
    static std::shared_ptr<FrameBufferPool> getSharedInstance();
    
    /// 从缓存池获取一个FBO，需要在GL线程
    /// @param width 宽
    /// @param height 高
    /// @param isOnlyTexture 是否只生成纹理，不生成FrameBuffer
    /// @param textureID 外部指定的纹理ID，若>0，则内部不会生成纹理
    /// @param frameBufferID 外部指定的FBO，若>0，则内部不会生成FBO
    FrameBuffer *fetchFrameBufferFromPool(int width, int height, bool isOnlyTexture = false, GLuint textureID = 0, GLuint frameBufferID = 0);
    
    /// 把一个FBO放回缓存池
    /// @param frameBuffer FBO
    void returnFrameBufferToPool(FrameBuffer *frameBuffer);
    
    /// 清空缓存池，需要在GL线程
    void clearFrameBufferPool();
    
private:
    
    std::map<std::string, FrameBuffer *> frameBufferCache;
};

#endif /* FrameBufferPool_hpp */
