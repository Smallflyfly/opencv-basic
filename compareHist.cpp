//
// Created by smallflyfly on 2021/6/10.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;


void drawHist(Mat hist, int type, string name) {
    int histW = 512;
    int histH = 480;
    int width = 2;
    Mat histIm = Mat::zeros(histH, histW, CV_8UC3);
    normalize(hist, hist, 1, 0, type);
    for (int i = 1; i <= hist.rows; ++i) {
        Point p1(width * (i-1), histH - 1), p2(width * i - 1, histH - cvRound(histH * 100.0 * hist.at<float>(i)));
        rectangle(histIm, p1, p2, Scalar(255, 255, 255), -1);
    }
    imshow(name, histIm);
}

int main() {
    Mat gray1 = imread("test.jpg", IMREAD_GRAYSCALE);

    Mat gray2;
    resize(gray1, gray2, Size(0, 0), 0.5, 0.5);

    Mat hist1, hist2;
    const int channels[1] = {0};
    float inRange[2] = {0, 255};
    const float *range[1] = {inRange};
    const int bins[1] = {256};
    calcHist(&gray1, 1, channels, Mat(), hist1, 1, bins, range);
    calcHist(&gray2, 1, channels, Mat(), hist2, 1, bins, range);

    drawHist(hist1, NORM_L1, "hist1");
    drawHist(hist2, NORM_L1, "hist2");

    waitKey(0);
    destroyAllWindows();

    double cmp = compareHist(hist1, hist2, HISTCMP_CORREL);
    cout << cmp << endl;

    return 0;
}