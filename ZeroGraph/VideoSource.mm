//
//  VideoSource.mm
//  ZeroGraph
//
//  Created by Kim, Jinyoung on 2/20/15.
//  Copyright (c) 2015 Jinyoung Kim. All rights reserved.
//

#import "VideoSource.h"

@interface VideoSource () <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, weak) id<VideoSourceDelegate> delegate;

@end

@implementation VideoSource

#pragma mark - Inits, Getters/Setters

- (instancetype)initWithDelegate:(id<VideoSourceDelegate>)delegate {
    self = [super init];
    if (self) {
        _delegate = delegate;

        // create capture session
        _captureSession = [[AVCaptureSession alloc] init];
        [_captureSession setSessionPreset:AVCaptureSessionPreset1280x720];

        // identify device to capture from
        AVCaptureDevice *videoDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];

        // get video input from back camera
        AVCaptureDeviceInput *deviceInput = [AVCaptureDeviceInput deviceInputWithDevice:videoDevice error:nil];
        if ([_captureSession canAddInput:deviceInput]) {
            [_captureSession addInput:deviceInput];
        }

        AVCaptureVideoDataOutput *dataOutput = [[AVCaptureVideoDataOutput alloc] init];
        NSString *key = (NSString *)kCVPixelBufferPixelFormatTypeKey;
        NSNumber *value = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA];
        dataOutput.videoSettings = @{ key : value };
        dataOutput.alwaysDiscardsLateVideoFrames = YES;

        dispatch_queue_t queue;
        queue = dispatch_queue_create("com.jinyoungkim.zerograph", DISPATCH_QUEUE_SERIAL);
        [dataOutput setSampleBufferDelegate:self queue:queue];

        [_captureSession addOutput:dataOutput];
        [_captureSession startRunning];
    }
    return self;
}

#pragma mark - AVCaptureVideoDataOutputSampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
       fromConnection:(AVCaptureConnection *)connection {

    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);

    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(imageBuffer);
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
    size_t stride = CVPixelBufferGetBytesPerRow(imageBuffer);
    VideoFrame frame = {width, height, stride, baseAddress};

    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef newContext = CGBitmapContextCreate(frame.data,
                                                    frame.width,
                                                    frame.height,
                                                    8,
                                                    frame.stride,
                                                    colorSpace,
                                                    kCGBitmapByteOrder32Little |
                                                    kCGImageAlphaPremultipliedFirst);
    CGImageRef newImage = CGBitmapContextCreateImage(newContext);
    CGContextRelease(newContext);
    CGColorSpaceRelease(colorSpace);
    UIImage *image = [UIImage imageWithCGImage:newImage];
    CGImageRelease(newImage);

    __weak typeof(self) _weakSelf = self;
    dispatch_sync(dispatch_get_main_queue(), ^{
        [[_weakSelf delegate] captureReady:image andFrame:frame];
    });
    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
}


@end
