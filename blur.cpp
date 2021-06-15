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

    Mat gaussNoise = Mat::zeros(im.rows, im.cols, im.type());

    RNG rng;
    rng.fill(gaussNoise, RNG::NORMAL, 10, 20);

    Mat imGaussNoise = im + gaussNoise;
    imshow("gauss im", imGaussNoise);

    Mat blurIm1, blurIm2;
    blur(imGaussNoise, blurIm1, Size(3, 3));
    imshow("blur im1", blurIm1);

    blur(im, blurIm2, Size(3, 3));
    imshow("blurIm2", blurIm2);

    waitKey(0);

    destroyAllWindows();

    return 0;
}