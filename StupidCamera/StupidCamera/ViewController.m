//
//  ViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "ViewController.h"
#import <GPUImage/GPUImage.h>

@interface ViewController ()
@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageView *imageView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
    _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
    _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
    [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
    _imageView = [[GPUImageView alloc] initWithFrame:self.view.bounds];
    [_camera addTarget:_imageView];
    [self.view addSubview:_imageView];
    [_camera startCameraCapture];
}


@end
