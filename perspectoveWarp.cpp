//
// Created by smallflyfly on 2021/6/10.
//


#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {

    Mat im = imread("test.jpg");

    Point2f srcPoints[4];
    Point2f dstPoints[4];

    srcPoints[0] = Point2f(20, 30);
    srcPoints[1] = Point2f(50, 100);
    srcPoints[2] = Point2f(200, 400);
    srcPoints[3] = Point2f(500, 800);

    dstPoints[0] = Point2f(45, 120);
    dstPoints[1] = Point2f(80, 250);
    dstPoints[2] = Point2f(300, 500);
    dstPoints[3] = Point2f(600, 600);

    Mat r, warp;
    r = getPerspectiveTransform(srcPoints, dstPoints);
    warpPerspective(im, warp, r, im.size());

    imshow("warp", warp);

    waitKey(0);

    destroyAllWindows();

    return 0;

}