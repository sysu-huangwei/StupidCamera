//
//  GPUImageDrawAlphaFilter.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/21.
//

#import "GPUImageDrawAlphaFilter.h"
#import "SCFilterDrawAlpha.hpp"

@interface GPUImageDrawAlphaFilter()
{
    SCFilterDrawAlpha *drawAlphaFilter;
}
@end

@implementation GPUImageDrawAlphaFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            [GPUImageContext useImageProcessingContext];
            self->drawAlphaFilter = new SCFilterDrawAlpha();
            self->drawAlphaFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->drawAlphaFilter->release();
        delete self->drawAlphaFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->drawAlphaFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    self->drawAlphaFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->drawAlphaFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->drawAlphaFilter->render();
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

@end