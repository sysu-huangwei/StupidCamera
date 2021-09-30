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
    
    std::shared_ptr<effect::FrameBuffer> inputFrameBuffer = getCPPFrameBufferFromGPUImageFrameBuffer(firstInputFramebuffer);
    std::shared_ptr<effect::FrameBuffer> outputFrameBuffer = getCPPFrameBufferFromGPUImageFrameBuffer(outputFramebuffer);
    
    self->effectEngine->setInputFrameBuffer(inputFrameBuffer);
    
    self->effectEngine->renderToFrameBuffer(outputFrameBuffer);
    
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
            { FilterType_Lut, {
                { FilterParam_Lut_Path, std::string(lutImagePath.UTF8String) }
            } }
        };
        self->effectEngine->setParams(params);
    });
}

- (void)setLutDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { FilterType_Lut, {
            { FilterParam_Lut_Alpha, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setBlurDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { FilterType_Smooth, {
            { FilterParam_Blur_Alpha, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setSharpenDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { FilterType_SharpenUSM, {
            { FilterParam_Sharpen_Alpha, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setSmallHeadDegree:(float)degree {
    std::map<std::string, std::map<std::string, std::string> > params = {
        { FilterType_SmallHead, {
            { FilterParam_SmallHead_Degree, std::to_string(degree) }
        } }
    };
    self->effectEngine->setParams(params);
}

- (void)setFaceData:(FaceData)faceData {
    std::shared_ptr<FaceData> pFaceData = std::make_shared<FaceData>();
    memcpy(pFaceData.get(), &faceData, sizeof(FaceData));
    self->effectEngine->setFaceData(pFaceData);
}

@end
