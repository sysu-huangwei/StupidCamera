//
//  BaseViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/14.
//

#import "BaseViewController.h"

#define TOP_VIEW_HEIGHT 60

@interface BaseViewController ()

@end

@implementation BaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initTopView];
    [self initShowView];
    [self initBottomView];
    [self initBackButton];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self initGPUImageView];
}

- (void)initTopView {
    if (!self.topView) {
        self.topView = [[UIView alloc] init];
        [self.view addSubview:self.topView];
    }
    self.topView.backgroundColor = UIColor.whiteColor;
    self.topView.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *constraintHeight = [NSLayoutConstraint constraintWithItem:self.topView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:TOP_VIEW_HEIGHT];
    [self.topView addConstraint:constraintHeight];
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:self.topView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.topView.superview attribute:NSLayoutAttributeTopMargin multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:self.topView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.topView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:self.topView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.topView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
}

- (void)initShowView {
    if (!self.showView) {
        self.showView = [[UIView alloc] init];
        [self.view addSubview:self.showView];
    }
    self.showView.backgroundColor = UIColor.whiteColor;
    self.showView.translatesAutoresizingMaskIntoConstraints = NO;
    CGFloat height = self.view.bounds.size.width / 3.0 * 4.0;
    NSLayoutConstraint *constraintHeight = [NSLayoutConstraint constraintWithItem:self.showView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:height];
    [self.showView addConstraint:constraintHeight];
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:self.showView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.topView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:self.showView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.showView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:self.showView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.showView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
    
    UISwipeGestureRecognizer *leftRecognizer;
    leftRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(showViewGesture:)];
    [leftRecognizer setDirection:UISwipeGestureRecognizerDirectionLeft];
    [self.showView addGestureRecognizer:leftRecognizer];
    UISwipeGestureRecognizer *rightRecognizer;
    rightRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(showViewGesture:)];
    [rightRecognizer setDirection:UISwipeGestureRecognizerDirectionRight];
    [self.showView addGestureRecognizer:rightRecognizer];
}

- (void)showViewGesture:(UISwipeGestureRecognizer *)recognizer {
    
}

- (void)initBottomView {
    if (!self.bottomView) {
        self.bottomView = [[UIView alloc] init];
        [self.view addSubview:self.bottomView];
    }
    self.bottomView.backgroundColor = UIColor.whiteColor;
    self.bottomView.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:self.bottomView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.showView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:self.bottomView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.bottomView.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintRight = [NSLayoutConstraint constraintWithItem:self.bottomView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.bottomView.superview attribute:NSLayoutAttributeRight multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintRight];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:self.bottomView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.bottomView.superview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.view addConstraint:ConstraintBottom];
}

- (void)initBackButton {
    if (!self.backButton) {
        self.backButton = [[UIButton alloc] init];
        [self.topView addSubview:self.backButton];
        [self.backButton setTitle:@"返回" forState:UIControlStateNormal];
        [self.backButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [self.backButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateHighlighted];
    }
    UIImage *image = [UIImage imageNamed:@"back"];
    [self.backButton setImage:image forState:UIControlStateNormal];
    self.backButton.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *ConstraintTop = [NSLayoutConstraint constraintWithItem:self.backButton attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.backButton.superview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0];
    [self.topView addConstraint:ConstraintTop];
    NSLayoutConstraint *ConstraintLeft = [NSLayoutConstraint constraintWithItem:self.backButton attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.backButton.superview attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0];
    [self.topView addConstraint:ConstraintLeft];
    NSLayoutConstraint *ConstraintWidth = [NSLayoutConstraint constraintWithItem:self.backButton attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:100];
    [self.backButton addConstraint:ConstraintWidth];
    NSLayoutConstraint *ConstraintBottom = [NSLayoutConstraint constraintWithItem:self.backButton attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.backButton.superview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0];
    [self.topView addConstraint:ConstraintBottom];
    [self.backButton addTarget:self action:@selector(backClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)initGPUImageView {
    self.imageView = [[GPUImageView alloc] initWithFrame:self.showView.bounds];
    [self.showView addSubview:self.imageView];
}

- (void)backClick:(UIButton *)button{
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
