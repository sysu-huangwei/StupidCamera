//
//  ViewController.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/12.
//

#import "ViewController.h"
#import "CameraViewController.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (IBAction)openCamera:(id)sender {
    CameraViewController* cameraViewController = [[CameraViewController alloc] init];
    cameraViewController.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:cameraViewController animated:YES completion:nil];
}

@end
