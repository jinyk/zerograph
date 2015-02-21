//
//  VideoFrame.h
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#include <cstddef>

struct VideoFrame {
    size_t width;
    size_t height;
    size_t stride;
    unsigned char *data;
};
