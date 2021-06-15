//
// Created by smallflyfly on 2021/6/15.
//

#ifndef OPENCV_BASIC_UTILS_H
#define OPENCV_BASIC_UTILS_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

void showImage(const std::string &winName, const cv::Mat &im) {
    cv::imshow(winName, im);
}


#endif //OPENCV_BASIC_UTILS_H
