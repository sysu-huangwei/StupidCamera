//
//  CameraViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "CameraViewController.h"
#import <GPUImage/GPUImage.h>
#import "EditPhotoViewController.h"
#import "GPUImageBaseFilter.h"
#import "GPUImageLutFilter.h"

@interface CameraViewController ()
@property (strong, nonatomic) UIButton *captureButton;

@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageBaseFilter *baseFilter;
@property (strong, nonatomic) GPUImageLutFilter *lutFilter;

@property (strong, nonatomic) NSArray *lutImagePaths;
@property (assign, nonatomic) int currintLutIndex;
@end

@implementation CameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initCaptureButton];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self initCamera];
    [_camera startCameraCapture];
    _lutImagePaths = @[
        @"",
//        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup_miss_etikate.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup_soft_elegance_1.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup_soft_elegance_2.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"lookup_amatorka.png"],
    ];
    _currintLutIndex = 0;
}


- (void)initCaptureButton {
    if (!_captureButton) {
        _captureButton = [[UIButton alloc] init];
        [self.bottomView addSubview:_captureButton];
        [_captureButton setTitle:@"拍照" forState:UIControlStateNormal];
        [_captureButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [_captureButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateHighlighted];
    }
    _captureButton.backgroundColor = UIColor.redColor;
    _captureButton.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeTop multiplier:1.0 constant:50];
    [self.bottomView addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:100];
    [self.bottomView addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeRight multiplier:1.0 constant:-100];
    [self.bottomView addConstraint:ConstraintRight];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:_captureButton attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:-50];
    [self.bottomView addConstraint:ConstraintBottom];
    [_captureButton addTarget:self action:@selector(takeOriginPhotoClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)takeOriginPhotoClick:(UIButton *)button{
    [_lutFilter setLutImagePath:_lutImagePaths[_currintLutIndex++]];
    if (_currintLutIndex == _lutImagePaths.count) { _currintLutIndex = 0; }
//    [self takeOriginPhoto:^(UIImage *image) {
//        EditPhotoViewController *editPhotoViewController = [[EditPhotoViewController alloc] initWithUIImage:image];
//        editPhotoViewController.modalPresentationStyle = UIModalPresentationFullScreen;
//        [self presentViewController:editPhotoViewController animated:NO completion:nil];
//    }];
}


- (void)initCamera {
    if (!_camera) {
        _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
        _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
        _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
        [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
        _lutFilter = [[GPUImageLutFilter alloc] init];
        [_camera addTarget:_lutFilter];
        [_lutFilter addTarget:self.imageView];
    }
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
        [_camera stopCameraCapture];
        block(image);
    }];
}


@end
