//
// Created by smallflyfly on 2021/6/10.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // circle
    Mat im = imread("test.jpg");

    Point p(200, 500);

    circle(im, p, 5, Scalar(255, 255, 0), -1);

    line(im, Point(20, 100), Point(500, 800), Scalar(255, 0, 255), 2);

    rectangle(im, Point(200, 40), Point(500, 500), Scalar(0, 255, 255), 2);

    imshow("im", im);

    waitKey(0);
    destroyAllWindows();

    return 0;

}