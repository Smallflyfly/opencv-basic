//
// Created by smallflyfly on 2021/6/10.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {

    Mat im = imread("test.jpg", IMREAD_GRAYSCALE);

    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat hist;
    const int channels[1] = {0};
    float inRanges[2] = {0, 255};
    const float *ranges[1] = {inRanges};
    const int bins[1] = {256};
    calcHist(&im, 1, channels, Mat(), hist, 1, bins, ranges);
    int histW = 512;
    int histH = 480;
    int width = 2;
    Mat histL1_im = Mat::zeros(histH, histW, CV_8UC3);
    Mat histInf_im = Mat::zeros(histH, histW, CV_8UC3);
    Mat histL1, histInf;
    normalize(hist, histL1, 1, 0, NORM_L1);
    for (int i = 1; i <= histL1.rows; ++i) {
        float va = histL1.at<float>(i-1);
        rectangle(histL1_im, Point(width * (i-1), histH-1),
                  Point(width * i - 1, histH - cvRound(histH * 100.0 * histL1.at<float>(i-1)) - 1),
                  Scalar(255, 255, 255), -1);
    }

    imshow("hist-L1", histL1_im);

    waitKey(0);

    destroyAllWindows();

    return 0;
}