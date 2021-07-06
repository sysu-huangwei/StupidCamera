//
//  GPUImageFacePointFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/16.
//

#import "GPUImageFacePointFilter.h"
#import "SCFilterFacePoint.hpp"
#import "FrameBufferPool.hpp"

#define MAX_SMALL_FACE_DEGREE 0.2

@interface GPUImageFacePointFilter()
{
    SCFilterFacePoint *pointFilter;
}
@end

@implementation GPUImageFacePointFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            self->pointFilter = new SCFilterFacePoint();
            self->pointFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->pointFilter->release();
        delete self->pointFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        self->pointFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    
    self->pointFilter->setFaceData(self.faceData.faceData);
    
    FrameBuffer *inputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(firstInputFramebuffer.size.width, firstInputFramebuffer.size.height, false, firstInputFramebuffer.texture, firstInputFramebuffer.framebuffer);
    self->pointFilter->setInputFrameBuffer(inputFrameBuffer);
    FrameBuffer *outputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(outputFramebuffer.size.width, outputFramebuffer.size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->pointFilter->renderToFrameBuffer(outputFrameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(inputFrameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(outputFrameBuffer);
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}


@end
