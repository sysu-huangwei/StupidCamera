//
//  ViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "ViewController.h"
#import "CameraViewController.h"
#import <GPUImage/GPUImage.h>

@interface ViewController ()
@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageView *imageView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
//    _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetHigh cameraPosition:AVCaptureDevicePositionFront];
//    _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
//    _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
//    [_camera setCaptureSessionPreset:AVCaptureSessionPresetHigh];
//    _imageView = [[GPUImageView alloc] initWithFrame:self.view.bounds];
//    [_camera addTarget:_imageView];
//    [self.view addSubview:_imageView];
//    [_camera startCameraCapture];
}

- (IBAction)openCamera:(id)sender {
    CameraViewController* cameraViewController = [[CameraViewController alloc] init];
    cameraViewController.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:cameraViewController animated:YES completion:nil];
}

@end
