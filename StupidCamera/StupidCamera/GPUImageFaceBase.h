//
//  GPUImageFaceBase.h
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
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

@interface GPUImageFaceBase : GPUImageFilter

@property (strong, nonatomic) SCFaceDataIOS *faceData;

@end

NS_ASSUME_NONNULL_END
