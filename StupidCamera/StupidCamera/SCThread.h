//
//  SCThread.h
//  StupidCamera
//
//  Created by rayyy on 2021/4/13.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SCThread : NSObject

@property (atomic, readonly)BOOL isStopping;

- (void)start;

- (void)stop;

- (void)runBlockAsync:(void(^)(void))block;

- (void)runBlockSync:(void(^)(void))block;

@end

NS_ASSUME_NONNULL_END
