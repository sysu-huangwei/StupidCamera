//
//  CameraViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "CameraViewController.h"
#import <GPUImage/GPUImage.h>
#import "EditPhotoViewController.h"

#define TOP_VIEW_HEIGHT 60

@interface CameraViewController ()
@property (strong, nonatomic) UIView *topView;
@property (strong, nonatomic) UIView *showView;
@property (strong, nonatomic) UIView *bottomView;
@property (strong, nonatomic) UIButton *backButton;
@property (strong, nonatomic) UIButton *captureButton;

@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageView *imageView;
@end

@implementation CameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initTopView];
    [self initShowView];
    [self initBottomView];
    [self initCaptureButton];
    [self initBackButton];
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

- (void)initBackButton {
    if (!_backButton) {
        _backButton = [[UIButton alloc] init];
        [_topView addSubview:_backButton];
        [_backButton setTitle:@"返回" forState:UIControlStateNormal];
        [_backButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [_backButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateHighlighted];
    }
    _backButton.backgroundColor = UIColor.redColor;
    _backButton.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_backButton attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_backButton.superview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0];
    [_topView addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_backButton attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:_backButton.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [_topView addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintWidth = [NSLayoutConstraint constraintWithItem:_backButton attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:100];
    [_backButton addConstraint:ConstraintWidth];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:_backButton attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:_backButton.superview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [_topView addConstraint:ConstraintBottom];
    [_backButton addTarget:self action:@selector(backClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)initCaptureButton {
    if (!_captureButton) {
        _captureButton = [[UIButton alloc] init];
        [_bottomView addSubview:_captureButton];
        [_captureButton setTitle:@"拍照" forState:UIControlStateNormal];
        [_captureButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [_captureButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateHighlighted];
    }
    _captureButton.backgroundColor = UIColor.redColor;
    _captureButton.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_bottomView attribute:NSLayoutAttributeTop multiplier:1.0 constant:50];
    [_bottomView addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:_bottomView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:100];
    [_bottomView addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:_bottomView attribute:NSLayoutAttributeRight multiplier:1.0 constant:-100];
    [_bottomView addConstraint:ConstraintRight];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:_bottomView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:-50];
    [_bottomView addConstraint:ConstraintBottom];
    [_captureButton addTarget:self action:@selector(takeOriginPhotoClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)takeOriginPhotoClick:(UIButton *)button{
    [self takeOriginPhoto:^(UIImage *image) {
        EditPhotoViewController *editPhotoViewController = [[EditPhotoViewController alloc] initWithUIImage:image];
        editPhotoViewController.modalPresentationStyle = UIModalPresentationFullScreen;
        [self presentViewController:editPhotoViewController animated:NO completion:nil];
    }];
}

- (void)backClick:(UIButton *)button{
    [_camera stopCameraCapture];
    [self dismissViewControllerAnimated:YES completion:nil];
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

- (void)takeOriginPhoto:(void (^)(UIImage *image))block {
    if (!block) {
        return;
    }
    __block GPUImageFilter* filter = [[GPUImageFilter alloc] init];
    [_camera addTarget:filter];
    [self->_camera capturePhotoAsImageProcessedUpToFilter:filter withCompletionHandler:^(UIImage *image, NSError *error) {
        [self->_camera removeTarget:filter];
        filter = nil;
        block(image);
    }];
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
