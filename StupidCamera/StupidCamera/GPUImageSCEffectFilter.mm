//
//  GPUImageSCEffectFilter.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/30.
//

#import "GPUImageSCEffectFilter.h"
#import "SCEffectEngine.hpp"
#import "FrameBufferPool.hpp"

@interface GPUImageSCEffectFilter()
{
    SCEffectEngine *effectEngine;
}
@end

@implementation GPUImageSCEffectFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            [GPUImageContext useImageProcessingContext];
            self->effectEngine = new SCEffectEngine();
            self->effectEngine->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->effectEngine->release();
        delete self->effectEngine;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->effectEngine->resize(filterFrameSize.width, filterFrameSize.height);
    });
}

- (void)renderToTextureWithVertices:(const GLfloat *)vertices textureCoordinates:(const GLfloat *)textureCoordinates;
{
    if (self.preventRendering)
    {
        [firstInputFramebuffer unlock];
        return;
    }
    
    outputFramebuffer = [[GPUImageContext sharedFramebufferCache] fetchFramebufferForSize:[self sizeOfFBO] textureOptions:self.outputTextureOptions onlyTexture:NO];
    [outputFramebuffer activateFramebuffer];
    if (usingNextFrameForImageCapture)
    {
        [outputFramebuffer lock];
    }
    self->effectEngine->setSrcTextureID(firstInputFramebuffer.texture);
    CGSize size = [self sizeOfFBO];
    FrameBuffer *frameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(size.width, size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->effectEngine->renderToFrameBuffer(frameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(frameBuffer);
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

- (void)setLutImagePath:(NSString *)lutImagePath {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->effectEngine->replaceLutImagePath(lutImagePath.UTF8String);
    });
}

- (void)setLutDegree:(float)degree {
    self->effectEngine->setLutDegree(degree);
}

- (void)setSmallHeadDegree:(float)degree {
    self->effectEngine->setSmallHeadDegree(degree);
}

- (void)setFaceData:(SCFaceDataIOS *)faceData {
    self->effectEngine->setFaceData(faceData.faceData);
}

@end
