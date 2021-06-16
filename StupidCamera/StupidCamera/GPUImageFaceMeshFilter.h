//
//  GPUImageMeshFilter.h
//  StupidCamera
//
//  Created by rayyy on 2021/4/22.
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

@interface GPUImageFaceMeshFilter : GPUImageFilter

@property (strong, nonatomic) NSArray<NSDictionary *> *faceDataDict;
@property (strong, nonatomic) SCFaceDataIOS *faceData;

@property (assign, nonatomic) float smallFaceDegree;

@end

NS_ASSUME_NONNULL_END
