//
//  VideoSource.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "VideoFrame.h"

@protocol VideoSourceDelegate <NSObject>

@required

- (void)captureReady:(UIImage *)image andFrame:(VideoFrame)frame;

@end

@interface VideoSource : NSObject

- (instancetype)initWithDelegate:(id<VideoSourceDelegate>)delegate;

@end