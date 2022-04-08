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
            [GPUImageContext useImageProcessingContext];
            self->pointFilter = new SCFilterBackgroundPoint();
            self->pointFilter->init();
        });
    }
    return self;
}

- (void)dealloc {
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
        self->pointFilter->release();
        delete self->pointFilter;
    });
}

- (void)setupFilterForSize:(CGSize)filterFrameSize;
{
    runSynchronouslyOnVideoProcessingQueue(^{
        [GPUImageContext useImageProcessingContext];
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
    
    [self setFaceDataDict:nil];
    
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
//    __weak typeof(self) weakSelf = self;
//    _setFacedataBlock = ^{
//        __strong typeof(weakSelf) strongSelf = weakSelf;
//        strongSelf->_faceDataDict = [NSMutableArray arrayWithArray:faceDataDict];
//        if (faceDataDict.count > 0) {
//            NSArray<NSValue *> *facePointsArray = faceDataDict[0][@"facePoints"];
//            if (facePointsArray.count >= 13) {
//                float facePointFloat[26];
//                for (int i = 0; i < 13; i++) {
//                    facePointFloat[2 * i] = facePointsArray[i].CGPointValue.x;
//                    facePointFloat[2 * i + 1] = facePointsArray[i].CGPointValue.y;
//                }
//                float facePointFloatChanged[26];
//                memcpy(facePointFloatChanged, facePointFloat, sizeof(float) * 26);
//                [strongSelf changeSmallFacePoint:facePointFloatChanged];
//                strongSelf->pointFilter->setPoints(facePointFloatChanged, 13);
//            }
//        }
//    };
//    float points[386] = {
//        0.240767, 0.497225,
//        0.247368, 0.534511,
//        0.258949, 0.571734,
//        0.273712, 0.608918,
//        0.295931, 0.644499,
//        0.325284, 0.677030,
//        0.362258, 0.704829,
//        0.404782, 0.727741,
//        0.452495, 0.743931,
//        0.503906, 0.751465,
//        0.555474, 0.745051,
//        0.601725, 0.726743,
//        0.642057, 0.701772,
//        0.674520, 0.670970,
//        0.704835, 0.638991,
//        0.727301, 0.603556,
//        0.741409, 0.566605,
//        0.752195, 0.529696,
//        0.757927, 0.492849,
//        0.273438, 0.417969,
//        0.328776, 0.411133,
//        0.368490, 0.412598,
//        0.407552, 0.417969,
//        0.455078, 0.421387,
//        0.419271, 0.397949,
//        0.371745, 0.391602,
//        0.324870, 0.393555,
//        0.724609, 0.415039,
//        0.679036, 0.409668,
//        0.628255, 0.410645,
//        0.589193, 0.416016,
//        0.541016, 0.419434,
//        0.576823, 0.396484,
//        0.624349, 0.389648,
//        0.682292, 0.393066,
//        0.333984, 0.458008,
//        0.354167, 0.470215,
//        0.379557, 0.474121,
//        0.406250, 0.473145,
//        0.432943, 0.472168,
//        0.412760, 0.452148,
//        0.387370, 0.442871,
//        0.358724, 0.445801,
//        0.383219, 0.461060,
//        0.380059, 0.457276,
//        0.664714, 0.458008,
//        0.644531, 0.470215,
//        0.619141, 0.474121,
//        0.592448, 0.473145,
//        0.565755, 0.472168,
//        0.585938, 0.452148,
//        0.611328, 0.442871,
//        0.639974, 0.445801,
//        0.615479, 0.461060,
//        0.610108, 0.456901,
//        0.470136, 0.470285,
//        0.465734, 0.536192,
//        0.436843, 0.582322,
//        0.463638, 0.592439,
//        0.502118, 0.595661,
//        0.539982, 0.592481,
//        0.566486, 0.582086,
//        0.536899, 0.536109,
//        0.529622, 0.470591,
//        0.503107, 0.562645,
//        0.404948, 0.634766,
//        0.594401, 0.634277,
//        0.430339, 0.654297,
//        0.462240, 0.669434,
//        0.500000, 0.673340,
//        0.538411, 0.670410,
//        0.572266, 0.653809,
//        0.544356, 0.640485,
//        0.499412, 0.644254,
//        0.453274, 0.641522,
//        0.436849, 0.631348,
//        0.472005, 0.626953,
//        0.500000, 0.630859,
//        0.524740, 0.626953,
//        0.557943, 0.629395,
//        0.544007, 0.640389,
//        0.499405, 0.644718,
//        0.453611, 0.641405,
//        0.497684, 0.471512,
//        0.498047, 0.420410,
//        0.499005, 0.612981,
//        0.303385, 0.271557,
//        0.489209, 0.286128,
//        0.688802, 0.273321,
//        0.497358, 0.345137,
//        0.236405, 0.422543,
//        0.760493, 0.419268,
//        0.625776, 0.269738,
//        0.723356, 0.332429,
//        0.493899, 0.247993,
//        0.363759, 0.272574,
//        0.269510, 0.336464,
//        -0.010409, 0.006287,
//        -0.010409, 0.006287,
//        -0.085299, -0.061836,
//        -0.075832, 0.567543,
//        -0.070153, 0.945148,
//        0.508787, 0.940250,
//        1.081832, 0.935402,
//        1.076152, 0.557797,
//        1.066685, -0.071583,
//        0.493641, -0.066734,
//        0.339330, 0.621842,
//        0.660851, 0.618917,
//        0.385413, 0.520165,
//        0.615600, 0.520047,
//        0.289673, 0.455261,
//        0.333222, 0.479636,
//        0.379994, 0.493763,
//        0.427601, 0.482037,
//        0.451539, 0.471226,
//        0.440407, 0.439712,
//        0.386994, 0.425949,
//        0.330540, 0.434062,
//        0.413700, 0.432830,
//        0.358767, 0.430005,
//        0.709025, 0.455261,
//        0.665883, 0.479108,
//        0.619577, 0.493763,
//        0.571504, 0.482566,
//        0.547689, 0.471380,
//        0.557754, 0.440410,
//        0.610952, 0.425949,
//        0.667620, 0.433364,
//        0.584353, 0.433179,
//        0.639286, 0.429656,
//        0.385413, 0.520165,
//        0.615600, 0.520047,
//        0.339330, 0.621842,
//        0.660851, 0.618917,
//        0.693906, 0.509129,
//        0.638657, 0.596245,
//        0.682913, 0.558213,
//        0.566121, 0.527127,
//        0.624700, 0.570149,
//        0.630013, 0.518128,
//        0.738720, 0.497733,
//        0.723860, 0.564087,
//        0.684982, 0.626167,
//        0.501953, 0.712402,
//        0.546943, 0.707731,
//        0.586995, 0.690276,
//        0.618229, 0.668025,
//        0.749728, 0.417999,
//        0.247515, 0.421171,
//        0.495973, 0.334202,
//        0.622143, 0.344276,
//        0.715024, 0.374948,
//        0.371062, 0.346999,
//        0.280120, 0.378832,
//        0.306342, 0.510652,
//        0.361684, 0.597455,
//        0.318419, 0.560145,
//        0.434893, 0.527245,
//        0.377631, 0.571233,
//        0.370617, 0.518949,
//        0.260439, 0.501253,
//        0.276790, 0.568257,
//        0.315656, 0.630386,
//        0.457367, 0.706682,
//        0.417560, 0.691019,
//        0.383603, 0.669797,
//        0.155128, 0.505796,
//        0.163929, 0.555510,
//        0.179370, 0.605141,
//        0.199054, 0.654719,
//        0.228679, 0.702161,
//        0.267818, 0.745536,
//        0.317116, 0.782601,
//        0.373815, 0.813151,
//        0.437432, 0.834737,
//        0.505980, 0.844782,
//        0.574737, 0.836230,
//        0.636405, 0.811820,
//        0.690181, 0.778525,
//        0.733465, 0.737456,
//        0.773886, 0.694817,
//        0.803840, 0.647571,
//        0.822650, 0.598303,
//        0.837032, 0.549090,
//        0.844674, 0.499962,
//        0.149313, 0.406220,
//        0.848096, 0.401853,
//        0.668473, 0.202479,
//        0.798580, 0.286067,
//        0.492637, 0.173487,
//        0.319117, 0.206262,
//        0.193451, 0.291448
//    };
    
    float points[2] = {0.5, 0.5};
    pointFilter->setPoints(points, 1);
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
