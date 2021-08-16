//
//  GPUImageSCEffectFilter.h
//  StupidCamera
//
//  Created by rayyy on 2021/6/30.
//

#if __cplusplus
extern "C" {
#endif
#import <GPUImage/GPUImage.h>
#if __cplusplus
}
#endif
#import "SCFaceDataIOS.h"

NS_ASSUME_NONNULL_BEGIN

@interface GPUImageSCEffectFilter : GPUImageFilter

- (void)setLutImagePath:(NSString *)lutImagePath;

- (void)setLutDegree:(float)degree;

- (void)setBlurDegree:(float)degree;

- (void)setSmallHeadDegree:(float)degree;

- (void)setFaceData:(SCFaceDataIOS *)faceData;

@end

NS_ASSUME_NONNULL_END
