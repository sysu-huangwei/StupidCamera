//
//  SCFaceDataIOS.m
//  StupidCamera
//
//  Created by rayyy on 2021/6/16.
//

#import "SCFaceDataIOS.h"
#import <UIKit/UIKit.h>

@implementation SCFaceDataIOS

- (instancetype)initWithFaceDataDictArray:(nullable NSArray<NSDictionary *> *)faceDataDicts {
    if (self = [super init]) {
        if (faceDataDicts) {
            _faceData = createSCFaceData();
            _faceData->faceCount = faceDataDicts.count > MAX_FACE_COUNT ? MAX_FACE_COUNT : (int)faceDataDicts.count;
            for (int i = 0; i < _faceData->faceCount; i++) {
                NSDictionary *faceDataDict = faceDataDicts[i];
                if ([faceDataDict[FACEDATA_KEY_FACEID] isKindOfClass:[NSNumber class]]) {
                    _faceData->faces[i].faceID = [faceDataDict[FACEDATA_KEY_FACEID] intValue];
                }
                if ([faceDataDict[FACEDATA_KEY_FACERECT] isKindOfClass:[NSValue class]]) {
                    CGRect rect = [faceDataDict[FACEDATA_KEY_FACERECT] CGRectValue];
                    _faceData->faces[i].rectOriginX = rect.origin.x;
                    _faceData->faces[i].rectOriginY = rect.origin.y;
                    _faceData->faces[i].rectWidth = rect.size.width;
                    _faceData->faces[i].rectHeight = rect.size.height;
                }
                if ([faceDataDict[FACEDATA_KEY_FACEPOINTS] isKindOfClass:[NSArray class]]) {
                    NSArray<NSValue *> *facePoints = faceDataDict[FACEDATA_KEY_FACEPOINTS];
                    int facePointsCount = facePoints.count > FACE_POINT_COUNT ? FACE_POINT_COUNT : (int)facePoints.count;
                    for (int i = 0; i < facePointsCount; i++) {
                        _faceData->faces[i].facePoints[2 * i] = [facePoints[i] CGPointValue].x;
                        _faceData->faces[i].facePoints[2 * i + 1] = [facePoints[i] CGPointValue].y;
                    }
                }
                if ([faceDataDict[FACEDATA_KEY_HASROLLANGLE] isKindOfClass:[NSNumber class]]) {
                    _faceData->faces[i].hasRollAngle = [faceDataDict[FACEDATA_KEY_HASROLLANGLE] boolValue];
                }
                if ([faceDataDict[FACEDATA_KEY_ROLLANGLE] isKindOfClass:[NSNumber class]]) {
                    _faceData->faces[i].rollAngle = [faceDataDict[FACEDATA_KEY_ROLLANGLE] floatValue];
                }
                if ([faceDataDict[FACEDATA_KEY_HASYAWANGLE] isKindOfClass:[NSNumber class]]) {
                    _faceData->faces[i].hasYawlAngle = [faceDataDict[FACEDATA_KEY_HASYAWANGLE] boolValue];
                }
                if ([faceDataDict[FACEDATA_KEY_YAWANGLE] isKindOfClass:[NSNumber class]]) {
                    _faceData->faces[i].yawAngle = [faceDataDict[FACEDATA_KEY_YAWANGLE] floatValue];
                }
            }
        }
    }
    return self;
}

- (void)dealloc {
    if (_faceData) {
        freeSCFaceData(&_faceData);
    }
}

- (nonnull id)copyWithZone:(nullable NSZone *)zone {
    SCFaceDataIOS *faceDataIOS = [[SCFaceDataIOS allocWithZone:zone] initWithFaceDataDictArray:nil];
    faceDataIOS->_faceData = copySCFaceData(_faceData);
    return faceDataIOS;
}

@end
