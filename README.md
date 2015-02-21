# ZeroGraph

The goal of this iOS app is to automate the process of resizing a 
[truncated graph](http://en.wikipedia.org/wiki/Misleading_graph#Truncated_graph) and 
make the y-axis zero based. Using the camera detect a graph (using [OpenCV](http://opencv.org)), understand 
the scale of the y-axis (using [Tesseract](https://code.google.com/p/tesseract-ocr/)) and rescales 
the image to a zero-base y-axis graph. 

At this point, thanks to 
[Paul Sholtz](http://www.raywenderlich.com/59602/make-augmented-reality-target-shooter-game-opencv-part-1) 
and the OpenCV CocoaPod, I got the camera output to an UIImage view and OpenCV processing the image to look
for patterns.
