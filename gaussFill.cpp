//
// Created by smallflyfly on 2021/6/11.
//


#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test.jpg");
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);

    Mat rgbNoise = Mat::zeros(im.rows, im.cols, im.type());
    Mat grayNoise = Mat::zeros(gray.rows, gray.cols, gray.type());

    RNG rng;
    rng.fill(rgbNoise, RNG::NORMAL, 10, 20);
    rng.fill(grayNoise, RNG::NORMAL, 10, 20);

    imshow("three channels noise", rgbNoise);
    imshow("one channels noise", grayNoise);

    im = im + rgbNoise;
    gray = gray +grayNoise;

    imshow("add noise rgb", im);
    imshow("add noise gray", gray);

    waitKey(0);

    destroyAllWindows();


    return 0;

}