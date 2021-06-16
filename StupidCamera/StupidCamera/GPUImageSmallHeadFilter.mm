//
//  GPUImageSmallHeadFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "GPUImageSmallHeadFilter.h"
#import "SCFilterSmallHead.hpp"

@interface GPUImageSmallHeadFilter()
{
    SCFilterSmallHead *smallHeadFilter;
}
@end

@implementation GPUImageSmallHeadFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            [GPUImageContext useImageProcessingContext];
            self->smallHeadFilter = new SCFilterSmallHead();
            self->smallHeadFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->smallHeadFilter->release();
        delete self->smallHeadFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->smallHeadFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    
    self->smallHeadFilter->setFaceData(self.faceData.faceData);
    
    self->smallHeadFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->smallHeadFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->smallHeadFilter->render();
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

- (void)setSmallHeadDegree:(float)smallHeadDegree {
    _smallHeadDegree = smallHeadDegree;
    smallHeadFilter->setSmallHeadDegree(smallHeadDegree);
}

@end
