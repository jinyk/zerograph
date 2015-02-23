//
//  ObjectDetector.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include "VideoFrame.h"

class ObjectDetector {

public:
    ObjectDetector();
    const cv::Mat& getEdgeImage(VideoFrame frame);
private:
    cv::Mat _edgeImage;
};
