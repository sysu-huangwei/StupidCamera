//
//  SCCameraViewController.m
//
//  Created by rayyyhuang on 2021/6/16.
//

#import "SCCameraViewController.h"
#import "SCEditViewController.h"
#import "GPUImageSCEffectFilter.h"

@interface SCCameraViewController () <AVCaptureMetadataOutputObjectsDelegate>
@property (strong, nonatomic) GPUImageStillCamera *camera;
//@property (strong, nonatomic) GPUImagePicture *picture;
@property (strong, nonatomic) GPUImageSCEffectFilter *effectFilter;

@property (strong, nonatomic) NSArray *lutImagePaths;
@property (assign, nonatomic) NSUInteger currintLutIndex;

@property (strong, nonatomic) NSMutableArray<NSMutableDictionary *> *faceDataDict;

@property (assign, nonatomic) SCEffectType currentSelectEffectType;
@property (strong, nonatomic) NSMutableDictionary<NSNumber *, UIButton *> *effectButton;
@property (strong, nonatomic) NSMutableDictionary<NSNumber *, NSNumber *> *effectDegree;

@end

@implementation SCCameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self initCamera];
    _faceDataDict = [[NSMutableArray alloc] init];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [_camera startCameraCapture];
}

- (IBAction)back:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)sliderChange:(UISlider *)slider {
    _sliderLabel.text = [NSString stringWithFormat:@"%d", (int)(slider.value * 100)];
    _effectDegree[@(_currentSelectEffectType)] = @(slider.value);
    switch (_currentSelectEffectType) {
        case SCEffectType_Lut:
            [_effectFilter setLutDegree:slider.value];
            break;
        case SCEffectType_SmallHead:
            [_effectFilter setSmallHeadDegree:slider.value];
            break;
        case SCEffectType_Smooth:
            [_effectFilter setBlurDegree:slider.value];
            break;
        case SCEffectType_Sharpen:
            [_effectFilter setSharpenDegree:slider.value];
            break;
        default:
            break;
    }
//    [_picture processImage];
}

- (IBAction)takePhoto:(UIButton *)button {
//    [_picture processImageUpToFilter:_effectFilter withCompletionHandler:^(UIImage *processedImage) {
//        NSLog(@"1");
//    }];
//    [_camera capturePhotoAsImageProcessedUpToFilter:_effectFilter withCompletionHandler:^(UIImage *processedImage, NSError *error) {
//        [self->_camera stopCameraCapture];
//        SCEditViewController *editViewController = [[SCEditViewController alloc] initWithUIImage:processedImage];
//        editViewController.modalPresentationStyle = UIModalPresentationFullScreen;
//        [self presentViewController:editViewController animated:YES completion:nil];
//    }];
}

- (IBAction)lutSelected:(UIButton *)button {
    [self selectEffect:SCEffectType_Lut];
}

- (IBAction)smallHeadSelected:(UIButton *)button {
    [self selectEffect:SCEffectType_SmallHead];
}

- (IBAction)smoothSelected:(UIButton *)button {
    [self selectEffect:SCEffectType_Smooth];
}

- (IBAction)sharpenSelected:(UIButton *)button {
    [self selectEffect:SCEffectType_Sharpen];
}

- (void)selectEffect:(SCEffectType)effectType {
    SCEffectType lastType = _currentSelectEffectType;
    if (lastType != effectType) {
        _degreeSlider.hidden = NO;
        _sliderLabel.hidden = NO;
        _currentSelectEffectType = effectType;
        float effectDegree = [_effectDegree[@(effectType)] floatValue];
        _sliderLabel.text = [NSString stringWithFormat:@"%d", (int)(effectDegree * 100)];
        [_degreeSlider setValue:effectDegree];
        if(_effectButton[@(lastType)]) {
            [_effectButton[@(lastType)] setBackgroundColor:UIColor.systemTealColor];
        }
        [_effectButton[@(effectType)] setBackgroundColor:UIColor.systemOrangeColor];
    } else {
        [_effectButton[@(_currentSelectEffectType)] setBackgroundColor:UIColor.systemTealColor];
        _degreeSlider.hidden = YES;
        _sliderLabel.hidden = YES;
        _currentSelectEffectType = SCEffectType_None;
    }
}


- (IBAction)changeLutGesture:(UISwipeGestureRecognizer *)recognizer {
    if (recognizer.direction == UISwipeGestureRecognizerDirectionLeft) {
        _currintLutIndex = _currintLutIndex == _lutImagePaths.count - 1 ? 0 : _currintLutIndex + 1;
    }
    if (recognizer.direction == UISwipeGestureRecognizerDirectionRight) {
        _currintLutIndex = _currintLutIndex == 0 ? _lutImagePaths.count - 1 : _currintLutIndex - 1;
    }
    [_effectFilter setLutImagePath:_lutImagePaths[_currintLutIndex]];
}

- (void)initCamera {
    _currentSelectEffectType = SCEffectType_None;
    _effectDegree = [[NSMutableDictionary alloc] initWithDictionary:@{
        @(SCEffectType_Lut) : @(0.0),
        @(SCEffectType_SmallHead) : @(0.0),
        @(SCEffectType_Smooth) : @(0.0),
        @(SCEffectType_Sharpen) : @(0.0),
    }];
    _effectButton = [[NSMutableDictionary alloc] initWithDictionary:@{
        @(SCEffectType_Lut) : _lutButton,
        @(SCEffectType_SmallHead) : _smallHeadButton,
        @(SCEffectType_Smooth) : _smoothButton,
        @(SCEffectType_Sharpen) : _sharpenButton,
    }];
    
    NSString *path = [NSBundle.mainBundle.bundlePath stringByAppendingPathComponent:@"????????????.jpeg"];
    UIImage *image = [[UIImage alloc] initWithContentsOfFile:path];
//    _picture = [[GPUImagePicture alloc] initWithImage:image];
    
    _camera = [[GPUImageStillCamera alloc] initWithSessionPreset:AVCaptureSessionPresetPhoto cameraPosition:AVCaptureDevicePositionFront];
    _camera.outputImageOrientation = UIInterfaceOrientationPortrait;//???????????????????????????????????????
    _camera.horizontallyMirrorFrontFacingCamera = YES;//???????????????????????????
    [_camera setCaptureSessionPreset:AVCaptureSessionPresetPhoto];
    [_camera setAVCaptureMetadataOutputObjectsDelegate:self];
    [_camera enableFaceDetect:YES];
    
    _effectFilter = [[GPUImageSCEffectFilter alloc] init];
//    [_picture addTarget:_effectFilter];
    [_camera addTarget:_effectFilter];
    [_effectFilter addTarget:_showView];
//    [_picture processImage];
    
    _lutImagePaths = @[
        @"",
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"Resource/brunch1.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"Resource/brunch2.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"Resource/brunch3.png"],
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"Resource/brunch4.png"],
    ];
    _currintLutIndex = 0;
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
            //iOS??????????????????????????????xy??????????????????????????????????????????
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
        [_effectFilter setFaceData:[[SCFaceDataIOS alloc] initWithFaceDataDictArray:_faceDataDict]];
}

@end
