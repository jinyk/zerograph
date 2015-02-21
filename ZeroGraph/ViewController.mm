//
//  ViewController.m
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/15/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include <opencv2/opencv.hpp>
#import "ViewController.h"
#import "PatternDetector.h"
#import "UIImage+OpenCV.h"

@interface ViewController () <VideoSourceDelegate>

@property (nonatomic, strong) VideoSource *videoSource;
@property (nonatomic, strong) NSTimer *m_trackingTimer;
@property (nonatomic) PatternDetector *m_detector;

@end

@implementation ViewController

#pragma mark - View Controller Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

    self.videoSource = [[VideoSource alloc] init];
    self.videoSource.delegate = self;
    [self.videoSource startWithDevicePosition:AVCaptureDevicePositionBack];

    UIImage *trackerImage = [UIImage imageNamed:@"target"];
    self.m_detector = new PatternDetector([trackerImage toCVMat]);

    self.m_trackingTimer = [NSTimer scheduledTimerWithTimeInterval:(1.0f/20.0f)
                                                            target:self
                                                          selector:@selector(updateTracking:)
                                                          userInfo:nil
                                                           repeats:YES];
}

#pragma mark - VideoSourceDelegate

- (void)frameReady:(VideoFrame)frame {
    __weak typeof(self) _weakSelf = self;
    dispatch_sync( dispatch_get_main_queue(), ^{
        // Construct CGContextRef from VideoFrame
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef newContext = CGBitmapContextCreate(frame.data,
                                                        frame.width,
                                                        frame.height,
                                                        8,
                                                        frame.stride,
                                                        colorSpace,
                                                        kCGBitmapByteOrder32Little |
                                                        kCGImageAlphaPremultipliedFirst);

        // Construct CGImageRef from CGContextRef
        CGImageRef newImage = CGBitmapContextCreateImage(newContext);
        CGContextRelease(newContext);
        CGColorSpaceRelease(colorSpace);

        // Construct UIImage from CGImageRef
        UIImage *image = [UIImage imageWithCGImage:newImage];
        CGImageRelease(newImage);
        [[_weakSelf backgroundImageView] setImage:image];
    });

    self.m_detector->scanFrame(frame);
}

#pragma mark - Private

- (void)updateTracking:(NSTimer *)timer {
    self.matchValueLabel.text = [NSString stringWithFormat:@"match value: %f", self.m_detector->matchValue()];
    if (self.m_detector->isTracking()) {
        self.matchValueLabel.textColor = [UIColor redColor];
    } else {
        self.matchValueLabel.textColor = [UIColor yellowColor];
    }
}

@end
