//
//  PatternDetector.cpp
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include "PatternDetector.h"

const float kDefaultScaleFactor = 2.00f;
const float kDefaultThresholdValue = 0.50f;

#pragma mark - Constructor

PatternDetector::PatternDetector(const cv::Mat& patternImage) {
    // (1) Save the pattern image
    m_patternImage = patternImage;

    // (2) Create a grayscale version of the pattern image
    switch (patternImage.channels()) {
        case 4: /* 3 color channels + 1 alpha */
            cv::cvtColor(m_patternImage, m_patternImageGray, CV_RGBA2GRAY);
            break;
        case 3: /* 3 color channels */
            cv::cvtColor(m_patternImage, m_patternImageGray, CV_RGB2GRAY);
            break;
        case 1: /* 1 color channel, grayscale */
            m_patternImageGray = m_patternImage;
            break;
    }

    // (3) Scale the gray image
    m_scaleFactor = kDefaultScaleFactor;
    float h = m_patternImageGray.rows / m_scaleFactor;
    float w = m_patternImageGray.cols / m_scaleFactor;
    cv::resize(m_patternImageGray, m_patternImageGrayScaled, cv::Size(w, h));

    // (4) Configure the tracking parameters
    m_matchThresholdValue = kDefaultThresholdValue;
    m_matchMethod = CV_TM_CCOEFF_NORMED;
}

#pragma mark - Public

void PatternDetector::scanFrame(VideoFrame frame) {
    // (1) Build the grayscale query image from the camera data
    cv::Mat queryImageGray, queryImageGrayScale;
    cv::Mat queryImage = cv::Mat((int)frame.height, (int)frame.width, CV_8UC4, frame.data, frame.stride);
    cv::cvtColor(queryImage, queryImageGray, CV_BGR2GRAY);

    // (2) Scale down the image
    float h = queryImageGray.rows / m_scaleFactor;
    float w = queryImageGray.cols / m_scaleFactor;
    cv::resize(queryImageGray, queryImageGrayScale, cv::Size(w, h));

    // (3) Perform the matching
    int rows = queryImageGrayScale.rows - m_patternImageGrayScaled.rows + 1;
    int cols = queryImageGrayScale.cols - m_patternImageGrayScaled.cols + 1;
    cv::Mat resultImage = cv::Mat(cols, rows, CV_32FC1);
    cv::matchTemplate(queryImageGrayScale, m_patternImageGrayScaled, resultImage, m_matchMethod);

    m_edgeImage = cv::Mat(cols, rows, CV_32FC1);
    cv::Canny(queryImage, m_edgeImage, 10, 50);

    // (4) Find the min/max settings
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    switch (m_matchMethod) {
        case CV_TM_SQDIFF:
        case CV_TM_SQDIFF_NORMED:
            m_matchPoint = minLoc;
            m_matchValue = minVal;
            break;
        default:
            m_matchPoint = maxLoc;
            m_matchValue = maxVal;
            break;
    }
}

const cv::Point& PatternDetector::matchPoint() {
    return m_matchPoint;
}

float PatternDetector::matchValue() {
    return m_matchValue;
}

float PatternDetector::matchThresholdValue() {
    return m_matchThresholdValue;
}

bool PatternDetector::isTracking() {
    switch (m_matchMethod) {
        case CV_TM_SQDIFF:
        case CV_TM_SQDIFF_NORMED:
            return m_matchValue < m_matchThresholdValue;
        default:
            return m_matchValue > m_matchThresholdValue;
    }
}

const cv::Mat& PatternDetector::edgeImage() {
    return m_edgeImage;
}
