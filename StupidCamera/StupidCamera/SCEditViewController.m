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
    [_originPicture addTarget:_showView];
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:_showView.bounds];
    [imageView setImage:_originImage];
    [_showView addSubview:imageView];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    for (UIView *view in _showView.subviews) {
        [view removeFromSuperview];
    }
    [_originPicture processImage];
}

- (IBAction)back:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}


@end
