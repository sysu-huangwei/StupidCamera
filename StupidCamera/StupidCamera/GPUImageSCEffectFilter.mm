//
//  GPUImageSCEffectFilter.m
//
//  Created by rayyyhuang on 2021/6/30.
//

#import "GPUImageSCEffectFilter.h"
#import "SCEffectEngine.hpp"
#import "FrameBufferPool.hpp"
#import "GLUtilsForIOSGPUImage.h"

@interface GPUImageSCEffectFilter()
{
    effect::SCEffectEngine *effectEngine;
}
@end

@implementation GPUImageSCEffectFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            [GPUImageContext useImageProcessingContext];
            self->effectEngine = new effect::SCEffectEngine();
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
    
    effect::FrameBuffer inputFrameBuffer = getCPPFrameBufferFromGPUImageFrameBuffer(firstInputFramebuffer);
    effect::FrameBuffer outputFrameBuffer = getCPPFrameBufferFromGPUImageFrameBuffer(outputFramebuffer);
    
    self->effectEngine->setInputFrameBuffer(&inputFrameBuffer);
    
    self->effectEngine->renderToFrameBuffer(&outputFrameBuffer);
    
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

- (void)setBlurDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { SCFilterType_Smooth, {
            { SCFilterParam_BlurAlpha, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setSharpenDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { SCFilterType_SharpenUSM, {
            { SCFilterParam_SharpenAlpha, std::to_string(degree) }
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
