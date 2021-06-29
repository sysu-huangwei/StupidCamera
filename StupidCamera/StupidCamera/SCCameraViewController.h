//
//  SCCameraViewController.h
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "ViewController.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SCEffectType) {
    SCEffectType_None = 0,
    SCEffectType_Lut = 1,
    SCEffectType_SmallHead = 2,
};

@interface SCCameraViewController : ViewController
@property (strong, nonatomic) IBOutlet UIButton *smallHeadButton;
@property (strong, nonatomic) IBOutlet UIButton *lutButton;
@property (strong, nonatomic) IBOutlet UILabel *sliderLabel;
@property (strong, nonatomic) IBOutlet UIView *showView;
@property (strong, nonatomic) IBOutlet UISlider *degreeSlider;
@end

NS_ASSUME_NONNULL_END
