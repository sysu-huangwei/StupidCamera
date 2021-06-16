//
//  GPUImageFaceBase.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "GPUImageFaceBase.h"

@implementation GPUImageFaceBase

- (void)setFaceData:(SCFaceDataIOS *)faceData {
    runAsynchronouslyOnVideoProcessingQueue(^{
        self->_faceData = [faceData copy];
    });
}

@end
