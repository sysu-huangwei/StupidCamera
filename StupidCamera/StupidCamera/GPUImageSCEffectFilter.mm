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
    
    FrameBuffer *inputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(firstInputFramebuffer.size.width, firstInputFramebuffer.size.height, false, firstInputFramebuffer.texture, firstInputFramebuffer.framebuffer);
    self->effectEngine->setInputFrameBuffer(inputFrameBuffer);
    FrameBuffer *outputFrameBuffer = FrameBufferPool::getSharedInstance()->fetchFrameBufferFromPool(outputFramebuffer.size.width, outputFramebuffer.size.height, false, outputFramebuffer.texture, outputFramebuffer.framebuffer);
    
    self->effectEngine->renderToFrameBuffer(outputFrameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(inputFrameBuffer);
    FrameBufferPool::getSharedInstance()->returnFrameBufferToPool(outputFrameBuffer);
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

- (void)setLutImagePath:(NSString *)lutImagePath {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        std::map<std::string, std::map<std::string, std::string> > params = {
            { SCFilterType_Lut, {
                { SCFilterParam_LutPath, std::string(lutImagePath.UTF8String) }
            } }
        };
        self->effectEngine->setParams(params);
    });
}

- (void)setLutDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { SCFilterType_Lut, {
            { SCFilterParam_LutAlpha, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setSmallHeadDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { SCFilterType_SmallHead, {
            { SCFilterParam_SmallHeadDegree, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setFaceData:(SCFaceDataIOS *)faceData {
    self->effectEngine->setFaceData(faceData.faceData);
}

@end
