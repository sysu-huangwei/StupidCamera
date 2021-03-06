//
//  SCFaceDataIOS.h
//
//  Created by rayyyhuang on 2021/6/16.
//

#import <Foundation/Foundation.h>
#import "SCFaceData.hpp"

NS_ASSUME_NONNULL_BEGIN

#define FACEDATA_KEY_FACEID @"faceID"
#define FACEDATA_KEY_FACERECT @"faceRect"
#define FACEDATA_KEY_FACEPOINTS @"facePoints"
#define FACEDATA_KEY_HASROLLANGLE @"hasRollAngle"
#define FACEDATA_KEY_ROLLANGLE @"rollAngle"
#define FACEDATA_KEY_HASYAWANGLE @"hasYawAngle"
#define FACEDATA_KEY_YAWANGLE @"yawAngle"

@interface SCFaceDataIOS : NSObject<NSCopying>

/// 这个faceData是一个C指针，不是一个OC对象，其生命周期跟着SCFaceDataIOS走，如果SCFaceDataIOS对象被dealloc，那么faceData也被释放
@property (nonatomic, readonly) SCFaceData* faceData;

/// 使用人脸数据初始化
/// @param faceDataDicts 人脸数据
- (instancetype)initWithFaceDataDictArray:(nullable NSArray<NSDictionary *> *)faceDataDicts;

- (instancetype)__unavailable init;

@end

NS_ASSUME_NONNULL_END
