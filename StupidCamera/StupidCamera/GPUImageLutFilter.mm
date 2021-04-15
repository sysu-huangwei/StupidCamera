//
//  GPUImageLutFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#import "GPUImageLutFilter.h"
#import "SCFilterLut.hpp"

@interface GPUImageLutFilter()
{
    SCFilterLut *lutFilter;
}
@end

@implementation GPUImageLutFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            self->lutFilter = new SCFilterLut();
            self->lutFilter->init();
            self->lutFilter->setLutImagePath([NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup_soft_elegance_1.png"].UTF8String);
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lutFilter->release();
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lutFilter->resize(filterFrameSize.width, filterFrameSize.height);
    });
}

- (void)renderToTextureWithVertices:(const GLfloat *)vertices textureCoordinates:(const GLfloat *)textureCoordinates;
{
    GLenum err = glGetError();
    printf("rayyy err1 = %d\n", err);
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
    err = glGetError();
    printf("rayyy err2 = %d\n", err);
    self->lutFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->lutFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->lutFilter->render();
    
    err = glGetError();
    printf("rayyy err3 = %d\n", err);
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

@end
