//
//  ViewController.m
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/15/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include <opencv2/opencv.hpp>
#import "ViewController.h"
#import "ObjectDetector.h"
#import "UIImage+OpenCV.h"

@interface ViewController () <VideoSourceDelegate>

@property (nonatomic, strong) VideoSource *videoSource;
@property (nonatomic, strong) NSTimer *trackingTimer;
@property (nonatomic) ObjectDetector *objectDetector;

@end

@implementation ViewController

#pragma mark - View Controller Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

    self.videoSource = [[VideoSource alloc] initWithDelegate:self];

    self.objectDetector = new ObjectDetector();
}

#pragma mark - VideoSourceDelegate

- (void)captureReady:(UIImage *)image andFrame:(VideoFrame)frame {
    self.backgroundImageView.image = image;
    self.edgeImageView.image = [UIImage fromCVMat:self.objectDetector->getEdgeImage(frame)];
}

@end
