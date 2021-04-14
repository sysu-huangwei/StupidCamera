//
//  BaseViewController.h
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#import "ViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface BaseViewController : ViewController
@property (strong, nonatomic) UIView *topView;
@property (strong, nonatomic) UIView *showView;
@property (strong, nonatomic) UIView *bottomView;
@property (strong, nonatomic) UIButton *backButton;
@end

NS_ASSUME_NONNULL_END
