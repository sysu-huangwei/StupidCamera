//
//  GPUImageFacePointFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/16.
//

#import "GPUImageFacePointFilter.h"
#import "SCFilterFacePoint.hpp"

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
    
    self->pointFilter->setSrcTextureID(firstInputFramebuffer.texture);
    
    CGSize size = [self sizeOfFBO];
    FrameBuffer *frameBuffer = new FrameBuffer();
    frameBuffer->init(size.width, size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->pointFilter->renderToFrameBuffer(frameBuffer);
    delete frameBuffer;
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}


@end
