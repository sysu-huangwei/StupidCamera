//
//  FaceDataIOS.m
//
//  Created by rayyyhuang on 2021/6/16.
//

#import "FaceDataIOS.h"

@implementation FaceDataIOS

- (instancetype)init {
    if (self = [super init]) {
        _faceData = new FaceData();
    }
    return self;
}

- (void)dealloc {
    if (_faceData) {
        delete _faceData;
    }
}


@end
