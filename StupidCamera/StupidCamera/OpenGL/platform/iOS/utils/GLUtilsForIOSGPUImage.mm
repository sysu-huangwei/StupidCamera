//
//  GLUtilsForIOSGPUImage.mm
//
//  Created by rayyyhuang on 2021/8/18.
//

#import "GLUtilsForIOSGPUImage.h"

std::shared_ptr<effect::FrameBuffer> getCPPFrameBufferFromGPUImageFrameBuffer(GPUImageFramebuffer *frameBuffer) {
    effect::TextureOptions textureOptions;
    textureOptions.minFilter = frameBuffer.textureOptions.minFilter;
    textureOptions.magFilter = frameBuffer.textureOptions.magFilter;
    textureOptions.wrapS = frameBuffer.textureOptions.wrapS;
    textureOptions.wrapT = frameBuffer.textureOptions.wrapT;
    textureOptions.internalFormat = frameBuffer.textureOptions.internalFormat;
    textureOptions.format = frameBuffer.textureOptions.format;
    textureOptions.type = frameBuffer.textureOptions.type;
    std::shared_ptr<effect::FrameBuffer> frameBufferCPP = std::make_shared<effect::FrameBuffer>();
    frameBufferCPP->init(frameBuffer.size.width, frameBuffer.size.height, false, textureOptions, frameBuffer.texture, frameBuffer.framebuffer);
    return frameBufferCPP;
}
