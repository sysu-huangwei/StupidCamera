//
//  GPUImageMeshFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/22.
//

#import "GPUImageFaceMeshFilter.h"

#import "SCFilterBackgroundMesh.hpp"
#import "DelaunayTriangle.hpp"
#import "SCFaceData.hpp"

#define MAX_SMALL_FACE_DEGREE 0.2

@interface GPUImageFaceMeshFilter()
{
    SCFilterBackgroundMesh *backgroundMeshFilter;
}
@property (nonatomic, copy) dispatch_block_t setFacedataBlock;
@end

@implementation GPUImageFaceMeshFilter

- (instancetype)init {
    if (self = [super init]) {
        _smallFaceDegree = 0.0f;
        runSynchronouslyOnVideoProcessingQueue(^{
            [GPUImageContext useImageProcessingContext];
            self->backgroundMeshFilter = new SCFilterBackgroundMesh();
            self->backgroundMeshFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->backgroundMeshFilter->release();
        delete self->backgroundMeshFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->backgroundMeshFilter->resize(filterFrameSize.width, filterFrameSize.height);
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
    self->backgroundMeshFilter->setSrcTextureID(firstInputFramebuffer.texture);
    self->backgroundMeshFilter->setOutsideTextureAndFbo(outputFramebuffer.texture, outputFramebuffer.framebuffer);
    self->backgroundMeshFilter->render();
    
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
                strongSelf->backgroundMeshFilter->setMesh(facePointFloatChanged, facePointFloat, 26, FaceTriangleIndex, FACE_TRIANGLE_INDEX_INT_ARRAY_SIZE);
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
