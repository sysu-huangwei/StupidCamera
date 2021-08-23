//
//  SCCameraViewController.h
//
//  Created by rayyyhuang on 2021/6/16.
//

#import "ViewController.h"
#import <GPUImage/GPUImage.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SCEffectType) {
    SCEffectType_None = 0,
    SCEffectType_Lut = 1,
    SCEffectType_SmallHead = 2,
    SCEffectType_Smooth = 3,
    SCEffectType_Sharpen = 4,
};

@interface SCCameraViewController : ViewController
@property (strong, nonatomic) IBOutlet UIButton *smallHeadButton;
@property (strong, nonatomic) IBOutlet UIButton *lutButton;
@property (strong, nonatomic) IBOutlet UIButton *smoothButton;
@property (strong, nonatomic) IBOutlet UIButton *sharpenButton;
@property (strong, nonatomic) IBOutlet UILabel *sliderLabel;
@property (strong, nonatomic) IBOutlet GPUImageView *showView;
@property (strong, nonatomic) IBOutlet UISlider *degreeSlider;
@end

NS_ASSUME_NONNULL_END
