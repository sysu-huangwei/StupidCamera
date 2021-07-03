//
//  GPUImageFaceLineFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/20.
//

#import "GPUImageFaceLineFilter.h"
#import "SCFilterFaceLine.hpp"
#import "DelaunayTriangle.hpp"
#import "FrameBufferPool.hpp"

#define MAX_SMALL_FACE_DEGREE 0.2

@interface GPUImageFaceLineFilter()
{
    SCFilterFaceLine *lineFilter;
}
@property (nonatomic, copy) dispatch_block_t setFacedataBlock;
@end

@implementation GPUImageFaceLineFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            self->lineFilter = new SCFilterFaceLine();
            self->lineFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lineFilter->release();
        delete self->lineFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lineFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    
    self->lineFilter->setFaceData(self.faceData.faceData);
    
    self->lineFilter->setSrcTextureID(firstInputFramebuffer.texture);
    CGSize size = [self sizeOfFBO];
    FrameBuffer *frameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(size.width, size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->lineFilter->renderToFrameBuffer(frameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(frameBuffer);
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}


@end
