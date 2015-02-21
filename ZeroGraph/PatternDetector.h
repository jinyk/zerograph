//
//  PatternDetector.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include "VideoFrame.h"

class PatternDetector {

public:
    // (1) Constructor
    PatternDetector(const cv::Mat& pattern);

    // (2) Scan the input video frame
    void scanFrame(VideoFrame frame);

    // (3) Match APIs
    const cv::Point& matchPoint();
    float matchValue();
    float matchThresholdValue();

    // (4) Tracking API
    bool isTracking();

private:
    // (5) Reference Marker Images
    cv::Mat m_patternImage;
    cv::Mat m_patternImageGray;
    cv::Mat m_patternImageGrayScaled;

    // (6) Supporting Members
    cv::Point m_matchPoint;
    int m_matchMethod;
    float m_matchValue;
    float m_matchThresholdValue;
    float m_scaleFactor;

};