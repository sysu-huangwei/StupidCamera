//
//  GLUtilsForIOSGPUImage.mm
//
//  Created by rayyyhuang on 2021/8/18.
//

#import "GLUtilsForIOSGPUImage.h"

effect::FrameBuffer getCPPFrameBufferFromGPUImageFrameBuffer(GPUImageFramebuffer *frameBuffer) {
    effect::TextureOptions textureOptions;
    textureOptions.minFilter = frameBuffer.textureOptions.minFilter;
    textureOptions.magFilter = frameBuffer.textureOptions.magFilter;
    textureOptions.wrapS = frameBuffer.textureOptions.wrapS;
    textureOptions.wrapT = frameBuffer.textureOptions.wrapT;
    textureOptions.internalFormat = frameBuffer.textureOptions.internalFormat;
    textureOptions.format = frameBuffer.textureOptions.format;
    textureOptions.type = frameBuffer.textureOptions.type;
    effect::FrameBuffer frameBufferCPP;
    frameBufferCPP.init(frameBuffer.size.width, frameBuffer.size.height, false, textureOptions, frameBuffer.texture, frameBuffer.framebuffer);
    return frameBufferCPP;
}
