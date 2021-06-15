//
// Created by smallflyfly on 2021/6/15.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test.jpg");
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat im3, im9;
    medianBlur(im, im3, 3);
    medianBlur(im, im9, 9);

    // gaussNoise
    Mat gaussNoise = Mat::zeros(im.rows, im.cols, im.type());
    RNG rng;
    rng.fill(gaussNoise, RNG::NORMAL, 10, 20);

    Mat imGauss = im + gaussNoise;
    medianBlur(imGauss, imGauss, 3);
    imshow("im3", im3);
    imshow("im9", im9);
    imshow("imGauss", imGauss);

    waitKey(0);
    destroyAllWindows();

    return 0;
}