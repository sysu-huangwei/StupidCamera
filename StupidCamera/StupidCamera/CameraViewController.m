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

@interface CameraViewController () <AVCaptureMetadataOutputObjectsDelegate>
@property (strong, nonatomic) UISlider *lutAlphaSlider;
@property (strong, nonatomic) UILabel *lutAlphaLabel;
@property (strong, nonatomic) UIButton *captureButton;

@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageBaseFilter *baseFilter;
@property (strong, nonatomic) GPUImageLutFilter *lutFilter;

@property (strong, nonatomic) NSArray *lutImagePaths;
@property (assign, nonatomic) NSUInteger currintLutIndex;
@end

@implementation CameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initCaptureButton];
    [self initLutAlphaSlider];
    [self initLutAlphaLabel];
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
    [_captureButton addTarget:self action:@selector(takePhotoClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)initLutAlphaSlider {
    if (!_lutAlphaSlider) {
        _lutAlphaSlider = [[UISlider alloc] init];
        [self.bottomView addSubview:_lutAlphaSlider];
        [_lutAlphaSlider setValue:1.0f];
        
        _lutAlphaSlider.translatesAutoresizingMaskIntoConstraints = NO;
        
        NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_lutAlphaSlider attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeTop multiplier:1.0 constant:10];
        [self.bottomView addConstraint:ConstraintTop];
        NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_lutAlphaSlider attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:20];
        [self.bottomView addConstraint:ConstraintLeft];
        NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_lutAlphaSlider attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeRight multiplier:1.0 constant:-50];
        [self.bottomView addConstraint:ConstraintRight];
        
        [_lutAlphaSlider addTarget:self action:@selector(lutAlphaSliderChange:) forControlEvents:UIControlEventValueChanged];
    }
}

- (void)initLutAlphaLabel {
    if (!_lutAlphaLabel) {
        _lutAlphaLabel = [[UILabel alloc] init];
        [self.bottomView addSubview:_lutAlphaLabel];
        _lutAlphaLabel.text = @"100";
        
        _lutAlphaLabel.translatesAutoresizingMaskIntoConstraints = NO;
        
        NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_lutAlphaLabel attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeTop multiplier:1.0 constant:10];
        [self.bottomView addConstraint:ConstraintTop];
        NSLayoutConstraint *ConstraintWidth = [NSLayoutConstraint constraintWithItem:_lutAlphaLabel attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:30];
        [_lutAlphaLabel addConstraint:ConstraintWidth];
        NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_lutAlphaLabel attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeRight multiplier:1.0 constant:-10];
        [self.bottomView addConstraint:ConstraintRight];
    }
}

- (void)lutAlphaSliderChange:(UISlider *)slider {
    _lutAlphaLabel.text = [NSString stringWithFormat:@"%d", (int)(slider.value * 100)];
    [_lutFilter setAlpha:slider.value];
}

- (void)showViewGesture:(UISwipeGestureRecognizer *)recognizer {
    [_lutFilter setLutImagePath:_lutImagePaths[_currintLutIndex]];
    if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft) {
        _currintLutIndex = _currintLutIndex == _lutImagePaths.count - 1 ? 0 : _currintLutIndex + 1;
    }
    if (recognizer.direction == UISwipeGestureRecognizerDirectionRight) {
        _currintLutIndex = _currintLutIndex == 0 ? _lutImagePaths.count - 1 : _currintLutIndex - 1;
    }
}

- (void)takePhotoClick:(UIButton *)button {
    [self takePhoto:^(UIImage *image) {
        EditPhotoViewController *editPhotoViewController = [[EditPhotoViewController alloc] initWithUIImage:image];
        editPhotoViewController.modalPresentationStyle = UIModalPresentationFullScreen;
        [self presentViewController:editPhotoViewController animated:NO completion:nil];
    }];
}


- (void)initCamera {
    if (!_camera) {
        _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
        _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
        _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
        [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
        [_camera setAVCaptureMetadataOutputObjectsDelegate:self];
        [_camera enableFaceDetect:YES];
        _lutFilter = [[GPUImageLutFilter alloc] init];
        [_camera addTarget:_lutFilter];
        [_lutFilter addTarget:self.imageView];
    }
}

- (void)takePhoto:(void (^)(UIImage *image))block {
    if (!block) {
        return;
    }
    [self->_camera capturePhotoAsImageProcessedUpToFilter:_lutFilter withCompletionHandler:^(UIImage *image, NSError *error) {
        [self->_camera stopCameraCapture];
        block(image);
    }];
}

#pragma mark - AVCaptureMetadataOutputObjectsDelegate
-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputMetadataObjects:(NSArray *)metadataObjects fromConnection:(AVCaptureConnection *)connection {
    if (metadataObjects.count > 0) {
        AVMetadataMachineReadableCodeObject *metadataObject = [metadataObjects objectAtIndex :0];
        if (metadataObject.type == AVMetadataObjectTypeFace) {
            AVMetadataObject *objec = [captureOutput transformedMetadataObjectForMetadataObject:metadataObject connection:connection];
            NSLog(@"111");
        }
    }
}


@end
