//
//  GLUtilsForIOSGPUImage.h
//
//  Created by rayyyhuang on 2021/8/18.
//

#import <Foundation/Foundation.h>

#if __cplusplus
extern "C" {
#endif
#import <GPUImage/GPUImage.h>
#if __cplusplus
}
#endif

#import "FrameBuffer.hpp"
#import <memory>

NS_ASSUME_NONNULL_BEGIN

std::shared_ptr<effect::FrameBuffer> getCPPFrameBufferFromGPUImageFrameBuffer(GPUImageFramebuffer *frameBuffer);

NS_ASSUME_NONNULL_END
