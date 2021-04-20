//
//  GPUImageFaceLineFilter.h
//  StupidCamera
//
//  Created by rayyy on 2021/4/20.
//

#if __cplusplus
extern "C" {
#endif
#import <GPUImage/GPUImage.h>
#if __cplusplus
}
#endif

NS_ASSUME_NONNULL_BEGIN

@interface GPUImageFaceLineFilter : GPUImageFilter

@property (strong, nonatomic) NSArray<NSDictionary *> *faceDataDict;

@end

NS_ASSUME_NONNULL_END
