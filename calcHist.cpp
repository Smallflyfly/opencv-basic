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
    float inRange[2] = {0, 255};
    const float *ranges[1] = {inRange};
    const int bins[1] = {256};
    cv::calcHist(&im, 1, channels, Mat(), hist, 1, bins, ranges);
    // ªÊ÷∆÷±∑ΩÕº
    int histW = 512;
    int histH = 400;
    int width = 2;
    Mat histImage = Mat::zeros(histH, histW, CV_8UC3);
    for (int i = 1; i <= hist.rows; ++i) {
        rectangle(histImage, Point(width * (i-1), histH-1),
                  Point(width * i - 1, histH - cvRound(hist.at<float>(i-1) / 5)),
                  Scalar(255, 255, 255), -1);
    }

    imshow("im", im);
    imshow("hist", histImage);

    waitKey(0);

    destroyAllWindows();

    return 0;
}