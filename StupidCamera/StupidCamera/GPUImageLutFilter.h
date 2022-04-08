//
//  GPUImageLutFilter.h
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#if __cplusplus
extern "C" {
#endif
#import <GPUImage/GPUImageFilter.h>
#if __cplusplus
}
#endif

NS_ASSUME_NONNULL_BEGIN

@interface GPUImageLutFilter : GPUImageFilter

@property (nonatomic, strong) NSString *lutImagePath;
@property (nonatomic, assign) float alpha;

@end

NS_ASSUME_NONNULL_END
