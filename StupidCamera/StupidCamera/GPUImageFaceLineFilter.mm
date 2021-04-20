//
//  GPUImageFaceLineFilter.mm
//  StupidCamera
//
//  Created by rayyy on 2021/4/20.
//

#import "GPUImageFaceLineFilter.h"
#import "SCFilterLine.hpp"
#import "DelaunayTriangle.hpp"

@interface GPUImageFaceLineFilter()
{
    SCFilterLine *lineFilter;
}
@end

@implementation GPUImageFaceLineFilter

- (instancetype)init {
    if (self = [super init]) {
        runSynchronouslyOnVideoProcessingQueue(^{
            self->lineFilter = new SCFilterLine();
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
    runAsynchronouslyOnVideoProcessingQueue(^{
        self->_faceDataDict = [faceDataDict mutableCopy];
        if (faceDataDict.count > 0) {
            NSArray<NSNumber *> *facePointsArray = self->_faceDataDict[0][@"facePoints"];
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
                int trianglesCountOutput;
                float *faceTriangle = DelaunayTriangle::getTriangles(facePointFloat, 9, trianglesCountOutput);
                float *faceTriangleLines = new float[trianglesCountOutput * 3 * 4];
                for (int i = 0; i < trianglesCountOutput; i++) {
                    faceTriangleLines[12 * i] = faceTriangle[6 * i];
                    faceTriangleLines[12 * i + 1] = faceTriangle[6 * i + 1];
                    faceTriangleLines[12 * i + 2] = faceTriangle[6 * i + 2];
                    faceTriangleLines[12 * i + 3] = faceTriangle[6 * i + 3];
                    faceTriangleLines[12 * i + 4] = faceTriangle[6 * i];
                    faceTriangleLines[12 * i + 5] = faceTriangle[6 * i + 1];
                    faceTriangleLines[12 * i + 6] = faceTriangle[6 * i + 4];
                    faceTriangleLines[12 * i + 7] = faceTriangle[6 * i + 5];
                    faceTriangleLines[12 * i + 8] = faceTriangle[6 * i + 2];
                    faceTriangleLines[12 * i + 9] = faceTriangle[6 * i + 3];
                    faceTriangleLines[12 * i + 10] = faceTriangle[6 * i + 4];
                    faceTriangleLines[12 * i + 11] = faceTriangle[6 * i + 5];
                }
                self->lineFilter->setLines(faceTriangleLines, trianglesCountOutput * 3);
                delete [] faceTriangle;
                delete [] faceTriangleLines;
            }
        }
    });
}

@end
