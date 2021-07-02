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
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lutFilter->release();
        delete self->lutFilter;
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
    self->lutFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->lutFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    CGSize size = [self sizeOfFBO];
    FrameBuffer *frameBuffer = new FrameBuffer();
    frameBuffer->init(size.width, size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->lutFilter->renderToFrameBuffer(frameBuffer);
    delete frameBuffer;
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

- (void)setLutImagePath:(NSString *)lutImagePath {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->_lutImagePath = lutImagePath;
        self->lutFilter->setLutImagePath(self->_lutImagePath.UTF8String);
    });
}

- (void)setAlpha:(float)alpha {
    lutFilter->setAlpha(alpha);
}

@end
