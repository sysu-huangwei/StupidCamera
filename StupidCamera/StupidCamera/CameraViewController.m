//
//  CameraViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "CameraViewController.h"
#import <GPUImage/GPUImage.h>

#define TOP_VIEW_HEIGHT 60

@interface CameraViewController ()
@property (strong, nonatomic) UIView *topView;
@property (strong, nonatomic) UIView *showView;
@property (strong, nonatomic) UIView *bottomView;

@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageView *imageView;
@end

@implementation CameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initTopView];
    [self initShowView];
    [self initBottomView];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self initCameraView];
}

- (void)initTopView {
    if (!_topView) {
        _topView = [[UIView alloc] init];
        [self.view addSubview:_topView];
    }
    _topView.backgroundColor = UIColor.darkGrayColor;
    _topView.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *constraintHeight = [NSLayoutConstraint constraintWithItem:_topView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:TOP_VIEW_HEIGHT];
    [_topView addConstraint:constraintHeight];
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_topView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_topView.superview attribute:NSLayoutAttributeTopMargin multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_topView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:_topView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_topView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:_topView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
}

- (void)initShowView {
    if (!_showView) {
        _showView = [[UIView alloc] init];
        [self.view addSubview:_showView];
    }
    _showView.backgroundColor = UIColor.systemBlueColor;
    _showView.translatesAutoresizingMaskIntoConstraints = NO;
    CGFloat height = self.view.bounds.size.width / 3.0 * 4.0;
    NSLayoutConstraint *constraintHeight = [NSLayoutConstraint constraintWithItem:_showView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:height];
    [_showView addConstraint:constraintHeight];
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_showView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_topView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_showView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:_showView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_showView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:_showView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
}

- (void)initBottomView {
    if (!_bottomView) {
        _bottomView = [[UIView alloc] init];
        [self.view addSubview:_bottomView];
    }
    _bottomView.backgroundColor = UIColor.yellowColor;
    _bottomView.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_showView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:_bottomView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:_bottomView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:_bottomView.superview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintBottom];
}

- (void)initCameraView {
    _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
    _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
    _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
    [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
    _imageView = [[GPUImageView alloc] initWithFrame:_showView.bounds];
    [_camera addTarget:_imageView];
    [_showView addSubview:_imageView];
    [_camera startCameraCapture];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
