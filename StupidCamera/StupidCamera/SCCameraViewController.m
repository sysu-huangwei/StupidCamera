//
//  SCCameraViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "SCCameraViewController.h"

#import "GPUImageLutFilter.h"
#import "GPUImageFacePointFilter.h"
#import "GPUImageFaceLineFilter.h"
#import "GPUImageSmallHeadFilter.h"

@interface SCCameraViewController () <AVCaptureMetadataOutputObjectsDelegate>
@property (strong, nonatomic) IBOutlet UILabel *sliderLabel;
@property (strong, nonatomic) IBOutlet UIView *showView;

@property (strong, nonatomic) GPUImageView *imageView;

@property (strong, nonatomic) GPUImageStillCamera *camera;
@property (strong, nonatomic) GPUImageLutFilter *lutFilter;
@property (strong, nonatomic) GPUImageFacePointFilter *facePointFilter;
@property (strong, nonatomic) GPUImageFaceLineFilter *faceLineFilter;
@property (strong, nonatomic) GPUImageSmallHeadFilter *smallHeadFilter;

@property (strong, nonatomic) NSMutableArray<NSMutableDictionary *> *faceDataDict;

@end

@implementation SCCameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self initCamera];
    _faceDataDict = [[NSMutableArray alloc] init];
}

- (IBAction)back:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)sliderChange:(UISlider *)slider {
    _sliderLabel.text = [NSString stringWithFormat:@"%d", (int)(slider.value * 100)];
    [_smallHeadFilter setSmallHeadDegree:slider.value];
}

- (IBAction)takePhoto:(UIButton *)button {
    
}

- (void)initCamera {
    _imageView = [[GPUImageView alloc] initWithFrame:_showView.bounds];
    [_showView addSubview:_imageView];
    _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
    _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//设置照片的方向为设备的定向
    _camera.horizontallyMirrorFrontFacingCamera = YES;//设置前置是否为镜像
    [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
    [_camera setAVCaptureMetadataOutputObjectsDelegate:self];
    [_camera enableFaceDetect:YES];
    _faceLineFilter = [[GPUImageFaceLineFilter alloc] init];
    _facePointFilter = [[GPUImageFacePointFilter alloc] init];
    _smallHeadFilter = [[GPUImageSmallHeadFilter alloc] init];
    [_camera addTarget:_smallHeadFilter];
    [_smallHeadFilter addTarget:_faceLineFilter];
    [_faceLineFilter addTarget:self.imageView];
    
    [_camera startCameraCapture];
}

#pragma mark - AVCaptureMetadataOutputObjectsDelegate
-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputMetadataObjects:(NSArray *)metadataObjects fromConnection:(AVCaptureConnection *)connection {
    [_faceDataDict removeAllObjects];
    for (AVMetadataObject *objectOri in metadataObjects) {
        AVMetadataObject *object = [captureOutput transformedMetadataObjectForMetadataObject:objectOri connection:connection];
        if ([object isKindOfClass:[AVMetadataFaceObject class]]) {
            AVMetadataFaceObject *faceObject = (AVMetadataFaceObject *)object;
            NSMutableDictionary *oneFaceDict = [[NSMutableDictionary alloc] init];
            oneFaceDict[@"faceID"] = @(faceObject.faceID);
            //iOS原生的人脸检测坐标是xy颠倒的，这里需要重新计算一下
            CGRect boundsOrigin = faceObject.bounds;
            CGRect bounds;
            bounds.origin.x = boundsOrigin.origin.y;
            bounds.origin.y = boundsOrigin.origin.x;
            bounds.size.width = boundsOrigin.size.height;
            bounds.size.height = boundsOrigin.size.width;
            oneFaceDict[@"faceRect"] = @(bounds);
            NSMutableArray<NSValue *> *facePoints = [[NSMutableArray alloc] init];
            [facePoints addObject:@(CGPointMake(bounds.origin.x + bounds.size.width * 0.5f, bounds.origin.y + bounds.size.height * 0.5f))]; // 0
            [facePoints addObject:@(CGPointMake(bounds.origin.x, bounds.origin.y))]; // 1
            [facePoints addObject:@(CGPointMake(bounds.origin.x + bounds.size.width, bounds.origin.y))]; // 2
            [facePoints addObject:@(CGPointMake(bounds.origin.x, bounds.origin.y + bounds.size.height))]; // 3
            [facePoints addObject:@(CGPointMake(bounds.origin.x + bounds.size.width, bounds.origin.y + bounds.size.height))]; // 4
            [facePoints addObject:@(CGPointMake(bounds.origin.x - bounds.size.width * 0.2f, bounds.origin.y - bounds.size.height * 0.4f))]; // 5
            [facePoints addObject:@(CGPointMake(bounds.origin.x + bounds.size.width * 1.2f, bounds.origin.y - bounds.size.height * 0.4f))]; // 6
            [facePoints addObject:@(CGPointMake(bounds.origin.x - bounds.size.width * 0.2f, bounds.origin.y + bounds.size.height * 1.3f))]; // 7
            [facePoints addObject:@(CGPointMake(bounds.origin.x + bounds.size.width * 1.2f, bounds.origin.y + bounds.size.height * 1.3f))]; // 8
            [facePoints addObject:@(CGPointMake((facePoints[5].CGPointValue.x + facePoints[7].CGPointValue.x) * 0.5, (facePoints[5].CGPointValue.y + facePoints[7].CGPointValue.y) * 0.5))]; // 9
            [facePoints addObject:@(CGPointMake((facePoints[5].CGPointValue.x + facePoints[6].CGPointValue.x) * 0.5, (facePoints[5].CGPointValue.y + facePoints[6].CGPointValue.y) * 0.5))]; // 10
            [facePoints addObject:@(CGPointMake((facePoints[6].CGPointValue.x + facePoints[8].CGPointValue.x) * 0.5, (facePoints[6].CGPointValue.y + facePoints[8].CGPointValue.y) * 0.5))]; // 11
            [facePoints addObject:@(CGPointMake((facePoints[7].CGPointValue.x + facePoints[8].CGPointValue.x) * 0.5, (facePoints[7].CGPointValue.y + facePoints[8].CGPointValue.y) * 0.5))]; // 12
            oneFaceDict[@"facePoints"] = facePoints;
            oneFaceDict[@"hasRollAngle"] = @(faceObject.hasRollAngle);
            oneFaceDict[@"rollAngle"] = @(faceObject.rollAngle);
            oneFaceDict[@"hasYawAngle"] = @(faceObject.hasYawAngle);
            oneFaceDict[@"yawAngle"] = @(faceObject.yawAngle);
            [_faceDataDict addObject:oneFaceDict];
        }
    }
    [_facePointFilter setFaceData:[[SCFaceDataIOS alloc] initWithFaceDataDictArray:_faceDataDict]];
    [_smallHeadFilter setFaceData:[[SCFaceDataIOS alloc] initWithFaceDataDictArray:_faceDataDict]];
    [_faceLineFilter setFaceData:[[SCFaceDataIOS alloc] initWithFaceDataDictArray:_faceDataDict]];
}

@end
