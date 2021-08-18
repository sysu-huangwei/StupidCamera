//
//  GLUtilsForIOS.mm
//
//  Created by rayyy on 2021/8/18.
//

#import "GLUtilsForIOS.h"

FrameBuffer getCPPFrameBufferFromGPUImageFrameBuffer(GPUImageFramebuffer *frameBuffer) {
    TextureOptions textureOptions;
    textureOptions.minFilter = frameBuffer.textureOptions.minFilter;
    textureOptions.magFilter = frameBuffer.textureOptions.magFilter;
    textureOptions.wrapS = frameBuffer.textureOptions.wrapS;
    textureOptions.wrapT = frameBuffer.textureOptions.wrapT;
    textureOptions.internalFormat = frameBuffer.textureOptions.internalFormat;
    textureOptions.format = frameBuffer.textureOptions.format;
    textureOptions.type = frameBuffer.textureOptions.type;
    FrameBuffer frameBufferCPP;
    frameBufferCPP.init(frameBuffer.size.width, frameBuffer.size.height, false, textureOptions, frameBuffer.texture, frameBuffer.framebuffer);
    return frameBufferCPP;
}
