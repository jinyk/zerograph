//
//  VideoSource.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "VideoFrame.h"

@protocol VideoSourceDelegate <NSObject>

@required
- (void)frameReady:(VideoFrame)frame;

@end

@interface VideoSource : NSObject

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureDeviceInput *deviceInput;
@property (nonatomic, weak) id<VideoSourceDelegate> delegate;

- (BOOL)startWithDevicePosition:(AVCaptureDevicePosition)devicePosition;

@end