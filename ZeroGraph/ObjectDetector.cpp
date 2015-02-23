//
//  ObjectDetector.cpp
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include "ObjectDetector.h"

#pragma mark - Constructor

ObjectDetector::ObjectDetector() {
    // ?
}

const cv::Mat& ObjectDetector::getEdgeImage(VideoFrame frame) {
    cv::Mat queryImage = cv::Mat((int)frame.height, (int)frame.width, CV_8UC4, frame.data, frame.stride);
    _edgeImage = cv::Mat(queryImage.cols, queryImage.rows, CV_32FC1);
    cv::Canny(queryImage, _edgeImage, 50, 50);

    return _edgeImage;
}
