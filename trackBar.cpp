//
// Created by smallflyfly on 2021/6/10.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

const int maxAlphaValue = 1000;
int nAlphaValueSlider;
double dAlphaValue;
double dBetaValue;

Mat im1, im2;
Mat dstIm;

void onTrackBar(int, void *) {
    dAlphaValue = nAlphaValueSlider * 1.0 / maxAlphaValue;
    dBetaValue = (1.0 - dAlphaValue);
    addWeighted(im1, dAlphaValue, im2, dBetaValue, 0.0, dstIm);

    imshow("trackBar", dstIm);
}


int main() {

    im1 = imread("test.jpg");
    im2 = imread("test.jpg");

    nAlphaValueSlider = 50;

    namedWindow("trackBar");
    string trackBarName = "透明值100";
    cv::createTrackbar(trackBarName, "trackBar", &nAlphaValueSlider, maxAlphaValue, onTrackBar);

    onTrackBar(nAlphaValueSlider, nullptr);

    waitKey(0);

    destroyAllWindows();

    return 0;

}