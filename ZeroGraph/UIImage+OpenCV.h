//
//  UIImage+OpenCV.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (OpenCV)

+ (UIImage *)fromCVMat:(const cv::Mat&)cvMat;
+ (cv::Mat)toCVMat:(UIImage *)image;
- (cv::Mat)toCVMat;

@end
