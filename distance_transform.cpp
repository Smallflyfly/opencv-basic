//
// Created by smallflyfly on 2021/6/15.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    // 自定义矩阵
    Mat a = (Mat_<uchar>(5, 5) <<
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,0,1,1,
            1,1,1,1,1,
            1,1,1,1,1
            );
    Mat distL1, distL2, distC;
    distanceTransform(a, distL1, DIST_L1, 3, CV_8U);
    distanceTransform(a, distL2, DIST_L2, 5, CV_8U);
    distanceTransform(a, distC, DIST_C, 3, CV_8U);

    cout << distL1 << endl;
    cout << distL2 << endl;
    cout << distC << endl;

    Mat im = imread("test.jpg", IMREAD_GRAYSCALE);
    if (im.empty()) {
        cerr << "image file read error" << endl;
        return -1;
    }
    resize(im, im, Size(0, 0), 0.5, 0.5);

    // 转为二值图像
    Mat im1, im2;
    threshold(im, im1, 125 ,255, THRESH_BINARY);
    threshold(im, im2, 125, 255, THRESH_BINARY_INV);

    Mat dist1, dist2;
    distanceTransform(im1, dist1, DIST_L1, 3, CV_32F);
    distanceTransform(im2, dist2, DIST_L1, 3, CV_8U);

    showImage("im1", im1);
    showImage("dist1", dist1);
    showImage("im2", im2);
    showImage("dist2", dist2);

    waitKey(0);
    destroyAllWindows();

    return 0;
}