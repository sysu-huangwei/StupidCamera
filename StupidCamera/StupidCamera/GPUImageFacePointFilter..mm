//
//  GPUImageFacePointFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/16.
//

#import "GPUImageFacePointFilter.h"
#import "SCFilterPoint.hpp"

@interface GPUImageFacePointFilter()
{
    SCFilterPoint *pointFilter;
}
@end

@implementation GPUImageFacePointFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            self->pointFilter = new SCFilterPoint();
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
    self->pointFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->pointFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->pointFilter->render();
    
    [firstInputFramebuffer unlock];
    
    if (usingNextFrameForImageCapture)
    {
        dispatch_semaphore_signal(imageCaptureSemaphore);
    }
}

- (void)setFaceDataDict:(NSArray<NSDictionary *> *)faceDataDict {
    _faceDataDict = [faceDataDict mutableCopy];
    if (faceDataDict.count > 0) {
        NSArray<NSNumber *> *facePointsArray = _faceDataDict[0][@"facePoints"];
        if (facePointsArray.count >= 18) {
            float facePointFloat[18];
            facePointFloat[0] = [facePointsArray[0] floatValue];
            facePointFloat[1] = [facePointsArray[1] floatValue];
            facePointFloat[2] = [facePointsArray[2] floatValue];
            facePointFloat[3] = [facePointsArray[3] floatValue];
            facePointFloat[4] = [facePointsArray[4] floatValue];
            facePointFloat[5] = [facePointsArray[5] floatValue];
            facePointFloat[6] = [facePointsArray[6] floatValue];
            facePointFloat[7] = [facePointsArray[7] floatValue];
            facePointFloat[8] = [facePointsArray[8] floatValue];
            facePointFloat[9] = [facePointsArray[9] floatValue];
            facePointFloat[10] = [facePointsArray[10] floatValue];
            facePointFloat[11] = [facePointsArray[11] floatValue];
            facePointFloat[12] = [facePointsArray[12] floatValue];
            facePointFloat[13] = [facePointsArray[13] floatValue];
            facePointFloat[14] = [facePointsArray[14] floatValue];
            facePointFloat[15] = [facePointsArray[15] floatValue];
            facePointFloat[16] = [facePointsArray[16] floatValue];
            facePointFloat[17] = [facePointsArray[17] floatValue];
            pointFilter->setPoints(facePointFloat, 9);
        }
    }
}

@end
