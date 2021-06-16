//
//  GPUImageFacePointFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/16.
//

#import "GPUImageFacePointFilter.h"
#import "SCFilterBackgroundPoint.hpp"

#define MAX_SMALL_FACE_DEGREE 0.2

@interface GPUImageFacePointFilter()
{
    SCFilterBackgroundPoint *pointFilter;
}
@property (nonatomic, copy) dispatch_block_t setFacedataBlock;
@end

@implementation GPUImageFacePointFilter

- (instancetype)init {
    if (self = [super init]) {
        _smallFaceDegree = 0.0f;
        runSynchronouslyOnVideoProcessingQueue(^{
            self->pointFilter = new SCFilterBackgroundPoint();
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
    
    if (_setFacedataBlock) {
        _setFacedataBlock();
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
    __weak typeof(self) weakSelf = self;
    _setFacedataBlock = ^{
        __strong typeof(weakSelf) strongSelf = weakSelf;
        strongSelf->_faceDataDict = [NSMutableArray arrayWithArray:faceDataDict];
        if (faceDataDict.count > 0) {
            NSArray<NSValue *> *facePointsArray = faceDataDict[0][@"facePoints"];
            if (facePointsArray.count >= 13) {
                float facePointFloat[26];
                for (int i = 0; i < 13; i++) {
                    facePointFloat[2 * i] = facePointsArray[i].CGPointValue.x;
                    facePointFloat[2 * i + 1] = facePointsArray[i].CGPointValue.y;
                }
                float facePointFloatChanged[26];
                memcpy(facePointFloatChanged, facePointFloat, sizeof(float) * 26);
                [strongSelf changeSmallFacePoint:facePointFloatChanged];
                strongSelf->pointFilter->setPoints(facePointFloatChanged, 13);
            }
        }
    };
}

- (void)changeSmallFacePoint:(float *)facePointFloat {
    facePointFloat[2] += (facePointFloat[0] - facePointFloat[2]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    facePointFloat[3] += (facePointFloat[1] - facePointFloat[3]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    
    facePointFloat[4] -= (facePointFloat[4] - facePointFloat[0]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    facePointFloat[5] += (facePointFloat[1] - facePointFloat[5]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    
    facePointFloat[6] += (facePointFloat[0] - facePointFloat[6]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    facePointFloat[7] -= (facePointFloat[7] - facePointFloat[1]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    
    facePointFloat[8] -= (facePointFloat[8] - facePointFloat[0]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
    facePointFloat[9] -= (facePointFloat[9] - facePointFloat[1]) * MAX_SMALL_FACE_DEGREE * _smallFaceDegree;
}

@end
