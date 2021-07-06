//
//  SCEditViewController.h
//  StupidCamera
//
//  Created by rayyy on 2021/7/6.
//

#import "ViewController.h"
#import <GPUImage/GPUImage.h>

NS_ASSUME_NONNULL_BEGIN

@interface SCEditViewController : ViewController
@property (strong, nonatomic) IBOutlet GPUImageView *showView;

- (instancetype)initWithUIImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
