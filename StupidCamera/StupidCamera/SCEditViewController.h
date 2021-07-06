//
//  SCEditViewController.h
//  StupidCamera
//
//  Created by rayyy on 2021/7/6.
//

#import "ViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface SCEditViewController : ViewController
@property (strong, nonatomic) IBOutlet UIView *showView;

- (instancetype)initWithUIImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
