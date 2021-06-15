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

    imshow("im", im);

    Mat gaussNoise = Mat::zeros(im.rows, im.cols, im.type());
    RNG rng;
    rng.fill(gaussNoise, RNG::NORMAL, 10, 20);

    Mat gaussIm = im + gaussNoise;
    imshow("gaussNoise", gaussIm);

    Mat gauss1;
    GaussianBlur(im, gauss1, Size(3, 3), 10 ,20);
    imshow("gauss1", gauss1);

    Mat gauss2;
    GaussianBlur(gaussIm, gauss2, Size(3, 3), 10, 20);
    imshow("gauss2", gauss2);

    waitKey(0);

    destroyAllWindows();

    return 0;

}