//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {

    cout << "OpenCV Version: " <<  CV_VERSION << endl;

    Mat im = imread("test.jpg");
    cv::resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat gray;
    cv::cvtColor(im, gray, CV_BGR2GRAY);

    Mat im1;
    cv::threshold(im, im1, 125, 255, cv::THRESH_BINARY);
    imshow("im1", im1);

    Mat im2;
    cv::threshold(im, im2, 125, 255, cv::THRESH_BINARY_INV);
    imshow("im2", im2);

    Mat gray1;
    cv::threshold(gray, gray1, 125, 255, cv::THRESH_TOZERO);
    imshow("gray1", gray1);

    Mat gray2;
    cv::threshold(gray, gray2, 125, 255, cv::THRESH_BINARY);
    imshow("gray2", gray2);

    Mat gray3;
    cv::threshold(gray, gray3, 125, 255, cv::THRESH_TRUNC);
    imshow("gray3", gray3);

    Mat gray4;
    cv::threshold(gray, gray4, 125, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    imshow("gray4", gray4);

    Mat gray5;
    cv::threshold(gray, gray5, 100, 255, cv::THRESH_BINARY|cv::THRESH_TRIANGLE);
    imshow("gray5", gray5);

    // 自适应二值化
    Mat adMean, adGauss;

    adaptiveThreshold(gray, adMean, 255, cv::ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 25, 0);
    imshow("adMean", adMean);

    adaptiveThreshold(gray, adGauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 75, 0);
    imshow("adGauss", adGauss);

    waitKey(0);
    destroyAllWindows();

    return 0;

}