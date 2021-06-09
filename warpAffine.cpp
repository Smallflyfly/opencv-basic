//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat im = imread("test.jpg");
    resize(im, im, Size(0, 0), 0.5, 0.5);
    imshow("im", im);

    Mat r1;
    double angle = 30.0;
    Size size(im.cols, im.rows);
    Point2f center(im.rows / 2.0, im.cols / 2.0);
    r1 = getRotationMatrix2D(center, angle, 1);
    Mat warp;
    warpAffine(im, warp, r1, size);
    imshow("warp1", warp);

    // 根据三个点进行仿射
    Point2f srcPoints[3];
    Point2f dstPoints[3];

    //src image 3 points
    srcPoints[0] = Point2f(0, 0);
    srcPoints[1] = Point2f(0, im.cols-1);
    srcPoints[2] = Point2f(im.rows-1, im.cols-1);
    // dst image 3 points
    dstPoints[0] = Point2f(im.rows * 0.2, im.cols * 0.2);
    dstPoints[1] = Point2f(im.rows * 0.1, im.cols * 0.7);
    dstPoints[2] = Point2f(im.rows * 0.9, im.cols * 0.7);
    r1 = getAffineTransform(srcPoints, dstPoints);
    warpAffine(im, warp, r1, size);
    imshow("warp", warp);

    waitKey(0);
    destroyAllWindows();

    return 0;
}