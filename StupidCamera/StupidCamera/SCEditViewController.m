//
//  SCCameraViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "SCEditViewController.h"

#import "GPUImageSCEffectFilter.h"

@interface SCEditViewController ()
@property (strong, nonatomic) UIImage *originImage;
@property (strong, nonatomic) UIImage *resultImage;
@property (strong, nonatomic) GPUImagePicture *originPicture;
@property (strong, nonatomic) GPUImageView *imageView;

@end

@implementation SCEditViewController

- (instancetype)initWithUIImage:(UIImage *)image {
    if (self = [super init]) {
        _originImage = image;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    _originPicture = [[GPUImagePicture alloc] initWithImage:_originImage];
    _imageView = [[GPUImageView alloc] initWithFrame:_showView.bounds];
    [_showView addSubview:_imageView];
    
}

- (void)viewDidAppear:(BOOL)animated {
    GPUImageFilter *filter = [[GPUImageFilter alloc] init];
    [_originPicture addTarget:filter];
    [filter addTarget:self.imageView];
    [_originPicture useNextFrameForImageCapture];
    [filter useNextFrameForImageCapture];
    [_originPicture processImageUpToFilter:filter withCompletionHandler:^(UIImage *processedImage) {
        self->_resultImage = processedImage;
    }];
}

- (IBAction)back:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}


@end
