//
//  SCThread.m
//  StupidCamera
//
//  Created by rayyy on 2021/4/13.
//

#import "SCThread.h"

@interface SCThread()
@property (nonatomic, strong)NSThread *thread;
@property (nonatomic, strong)NSRunLoop *runloop;
@property (nonatomic, strong)NSPort *port;
@property (nonatomic, strong)NSTimer *timer;
@end

@implementation SCThread

- (instancetype)init {
    if (self = [super init]) {
        _port = [NSMachPort port];
        _timer = [NSTimer timerWithTimeInterval:60
                                         target:nil
                                       selector:nil
                                       userInfo:nil
                                        repeats:YES];
        _thread = [[NSThread alloc] initWithTarget:self
                                          selector:@selector(threadRunloop)
                                            object:nil];
    }
    return self;
}

- (void)start {
    [_thread start];
}

- (void)_cleanRunLoop {
    [_timer invalidate]; _timer = nil;
    if (_port) [_runloop removePort:_port
                            forMode:NSDefaultRunLoopMode];
    CFRunLoopStop(CFRunLoopGetCurrent());
}

- (void)stop {
    _isStopping = YES;
    [_thread cancel];

    __weak typeof(self) wself = self;
    [self runBlockAsync:^{
        [wself _cleanRunLoop];
    }];
}

- (void)threadRunloop {
    @autoreleasepool {
        [[NSThread currentThread] setName:@"SCThread"];
        while (!_isStopping) {
            NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
            if (_port) [runLoop addPort:_port
                                forMode:NSDefaultRunLoopMode];
            if (_timer) [runLoop addTimer:_timer
                                  forMode:NSDefaultRunLoopMode];
            [runLoop runMode:NSDefaultRunLoopMode
                  beforeDate:[NSDate dateWithTimeIntervalSinceNow:60]];
        }
    }
}

- (void)blockProcess:(void (^)(void))block {
    if (block) block();
}

- (void)runBlockAsync:(void (^)(void))block {
    if ([NSThread currentThread] == _thread) {
        if (block) block();
    } else {
        [self performSelector:@selector(blockProcess:)
                     onThread:_thread
                   withObject:[block copy]
                waitUntilDone:NO];
    }
}

- (void)runBlockSync:(void (^)(void))block {
    if ([NSThread currentThread] == _thread) {
        if (block) block();
    } else {
        [self performSelector:@selector(blockProcess:)
                     onThread:_thread
                   withObject:block
                waitUntilDone:YES];
    }
}

@end
