//
//  main.cpp
//  PiMotionDetector
//
//  Created by William Keicher on 5/16/14.
//  Copyright (c) 2014 Yellow Dog. All rights reserved.
//

#include <iostream>
#include <utility>
#include <opencv2/opencv.hpp>
#include "RaspiCamCV.h"

using namespace cv;
using namespace std;

Mat diffImg(Mat t0, Mat t1, Mat t2)
{
    Mat diff1, diff2, ret;
    
    absdiff(t0, t1, diff1);
    absdiff(t1, t2, diff2);
    
    bitwise_and(diff1, diff2, ret);
    threshold(ret, ret, 40, 255, THRESH_BINARY);
    
    return ret;
}

pair<Mat,Mat> captureImage(RaspiCamCvCapture* capture)
{
    Mat processed;
    IplImage* img=raspiCamCvQueryFrame(capture);
    Mat original= cvarrToMat(img); 
    //capture >> original;
    cvtColor(original, processed, COLOR_BGR2GRAY);
    return pair<Mat, Mat>(original, processed);
}

int main(int argc, const char * argv[])
{
    const char* motionWindow = "motion window";
    const char* captureWindow = "capture window";

    namedWindow(motionWindow);
    namedWindow(captureWindow);
    
    RaspiCamCvCapture *capture = raspiCamCvCreateCameraCapture(0); 
    
    /*VideoCapture capture = VideoCapture(0);
    if (!capture.isOpened())
    {
        return -1;
    }*/
    
    pair<Mat,Mat> t0, t1, t2;
    
    t0 = captureImage(capture);
    t1 = captureImage(capture);
    t2 = captureImage(capture);
    
    while (true) {
        t0 = t1;
        t1 = t2;
        t2 = captureImage(capture);
        
        Mat diff = diffImg(t0.second, t1.second, t2.second);
        imshow(motionWindow, diff);
        
        if (countNonZero(diff) > 0)
        {
            imshow(captureWindow, t2.first);
        }
        else
        {
            Mat zeroMat = Mat::zeros(3, 3, CV_32F);
            imshow(captureWindow, zeroMat);
        }
        
        if (waitKey(30) >= 0)
        {
            break;
        }
    }
    
    destroyWindow(motionWindow);
    destroyWindow(captureWindow);
   
    raspiCamCvReleaseCapture(&capture); 
    return 0;
}

