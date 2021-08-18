//
//  ViewController.m
//
//  Created by rayyyhuang on 2021/4/12.
//

#import "ViewController.h"
#import "SCCameraViewController.h"

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (IBAction)openCamera:(id)sender {
    SCCameraViewController* cameraViewController = [[SCCameraViewController alloc] init];
    cameraViewController.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:cameraViewController animated:YES completion:nil];
}

@end
