//
//  EditPhotoViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#import "EditPhotoViewController.h"
#import <GPUImage/GPUImage.h>

@interface EditPhotoViewController ()
@property (strong, nonatomic) UIImage *originImage;
@property (strong, nonatomic) GPUImagePicture *originPicture;
@property (strong, nonatomic) GPUImageView *imageView;
@end

@implementation EditPhotoViewController

- (instancetype)initWithUIImage:(UIImage *)image {
    if (self = [super init]) {
        _originImage = image;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    _originPicture = [[GPUImagePicture alloc] initWithImage:_originImage];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    _imageView = [[GPUImageView alloc] initWithFrame:self.view.bounds];
    GPUImageFilter *filter = [[GPUImageFilter alloc] init];
    [_originPicture addTarget:filter];
    [filter addTarget:_imageView];
    [self.view addSubview:_imageView];
    [_originPicture processImage];
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
