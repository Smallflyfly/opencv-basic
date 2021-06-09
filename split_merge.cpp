//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test.jpg");

    cv::resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat ims[3];
    cv::split(im, ims);

    imshow("bgr", im);
    imshow("b", ims[0]);
    imshow("g", ims[1]);
    imshow("r", ims[2]);

    Mat merge;
    cv::merge(ims, 3, merge);

    imshow("merge1", merge);

    Mat ims2[3];
    ims2[0] = ims[1];
    ims2[1] = ims[2];
    ims2[2] = ims[0];

    cv::merge(ims2, 3, merge);

    imshow("merge2", merge);

    waitKey(0);

    destroyAllWindows();

    return 0;

}