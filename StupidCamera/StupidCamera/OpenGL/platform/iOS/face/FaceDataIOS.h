//
//  FaceDataIOS.h
//
//  Created by rayyyhuang on 2021/6/16.
//

#import <Foundation/Foundation.h>
#import "FaceData.hpp"

NS_ASSUME_NONNULL_BEGIN

#define FACEDATA_KEY_FACEID @"faceID"
#define FACEDATA_KEY_FACERECT @"faceRect"
#define FACEDATA_KEY_FACEPOINTS @"facePoints"
#define FACEDATA_KEY_HASROLLANGLE @"hasRollAngle"
#define FACEDATA_KEY_ROLLANGLE @"rollAngle"
#define FACEDATA_KEY_HASYAWANGLE @"hasYawAngle"
#define FACEDATA_KEY_YAWANGLE @"yawAngle"

@interface FaceDataIOS : NSObject

/// 这个faceData是一个C++指针，不是一个OC对象，其生命周期跟着FaceDataIOS走，如果FaceDataIOS对象被dealloc，那么faceData也被释放
@property (nonatomic, readonly) FaceData* faceData;

@end

NS_ASSUME_NONNULL_END
