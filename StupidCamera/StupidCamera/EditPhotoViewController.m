//
//  EditPhotoViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#import "EditPhotoViewController.h"
#import <GPUImage/GPUImage.h>

@interface EditPhotoViewController ()
@property (strong, nonatomic) UIButton *saveButton;

@property (strong, nonatomic) UIImage *originImage;
@property (strong, nonatomic) UIImage *resultImage;
@property (strong, nonatomic) GPUImagePicture *originPicture;
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
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self initSaveButton];
    GPUImageFilter *filter = [[GPUImageFilter alloc] init];
    [_originPicture addTarget:filter];
    [filter addTarget:self.imageView];
    [_originPicture processImageUpToFilter:filter withCompletionHandler:^(UIImage *processedImage) {
        self->_resultImage = processedImage;
    }];
}

- (void)initSaveButton {
    if (!_saveButton) {
        _saveButton = [[UIButton alloc] init];
        [self.bottomView addSubview:_saveButton];
        [_saveButton setTitle:@"保存" forState:UIControlStateNormal];
        UIImage *image = [UIImage imageNamed:@"confirm"];
        [_saveButton setImage:image forState:UIControlStateNormal];
    }
    CGFloat saveWidthHeight = 80;
    CGFloat toTop = (self.bottomView.bounds.size.height - saveWidthHeight) * 0.5;
    CGFloat toLeft = (self.bottomView.bounds.size.width - saveWidthHeight) * 0.5;
    _saveButton.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:_saveButton attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeTop multiplier:1.0 constant:toTop];
    [self.bottomView addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:_saveButton attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:toLeft];
    [self.bottomView addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:_saveButton attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeRight multiplier:1.0 constant:-toLeft];
    [self.bottomView addConstraint:ConstraintRight];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:_saveButton attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.bottomView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:-toTop];
    [self.bottomView addConstraint:ConstraintBottom];
    [_saveButton addTarget:self action:@selector(saveClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)saveClick:(UIButton *)button{
    if (_resultImage) {
        UIImageWriteToSavedPhotosAlbum(_resultImage, self, @selector(image:didFinishSavingWithError:contextInfo:), nil);
    }
}

- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo {
    [self dismissViewControllerAnimated:YES completion:nil];
}




@end
