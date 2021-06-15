//
//  GPUImageFaceLineFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/20.
//

#import "GPUImageFaceLineFilter.h"
#import "SCFilterBackgroundLine.hpp"
#import "DelaunayTriangle.hpp"

#define MAX_SMALL_FACE_DEGREE 0.2

@interface GPUImageFaceLineFilter()
{
    SCFilterBackgroundLine *lineFilter;
}
@property (nonatomic, copy) dispatch_block_t setFacedataBlock;
@end

@implementation GPUImageFaceLineFilter

- (instancetype)init {
    if (self = [super init]) {
        _smallFaceDegree = 0.0f;
        runSynchronouslyOnVideoProcessingQueue(^{
            self->lineFilter = new SCFilterBackgroundLine();
            self->lineFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lineFilter->release();
        delete self->lineFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        self->lineFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    
    self->lineFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->lineFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->lineFilter->render();
    
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
            NSArray<NSNumber *> *facePointsArray = faceDataDict[0][@"facePoints"];
            if (facePointsArray.count >= 26) {
                float facePointFloat[26];
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
                facePointFloat[18] = [facePointsArray[18] floatValue];
                facePointFloat[19] = [facePointsArray[19] floatValue];
                facePointFloat[20] = [facePointsArray[20] floatValue];
                facePointFloat[21] = [facePointsArray[21] floatValue];
                facePointFloat[22] = [facePointsArray[22] floatValue];
                facePointFloat[23] = [facePointsArray[23] floatValue];
                facePointFloat[24] = [facePointsArray[24] floatValue];
                facePointFloat[25] = [facePointsArray[25] floatValue];
                float facePointFloatChanged[26];
                memcpy(facePointFloatChanged, facePointFloat, sizeof(float) * 26);
                [strongSelf changeSmallFacePoint:facePointFloatChanged];
                int lineIndex[56] = {
                    0,1,  0,2,  0,3,  0,4,
                    1,2,  2,4,  4,3,  3,1,
                    5,10, 10,6, 6,11, 11,8, 8,12, 12,7, 7,9, 9,5,
                    1,5,  1,10, 10,2, 2,6,  2,11, 4,11, 4,8, 4,12, 3,12, 3,7, 3,9, 1,9
                };
                float lines[112];
                for (int i = 0; i < 112; i += 4) {
                    int currentIndex = i / 4;
                    lines[i] = facePointFloatChanged[2 * lineIndex[2 * currentIndex]];
                    lines[i + 1] = facePointFloatChanged[2 * lineIndex[2 * currentIndex] + 1];
                    lines[i + 2] = facePointFloatChanged[2 * lineIndex[2 * currentIndex + 1]];
                    lines[i + 3] = facePointFloatChanged[2 * lineIndex[2 * currentIndex + 1] + 1];
                }
                strongSelf->lineFilter->setLines(lines, 28);
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
