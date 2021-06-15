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

    Mat im = imread("test.jpg", IMREAD_GRAYSCALE);
    if (im.empty()) {
        cerr << "image file read error" << endl;
        return -1;
    }
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat result1, resultGauss, result2;
    // 未使用高斯滤波进行边缘检测
    Laplacian(im, result1, -1, 3);
    convertScaleAbs(result1, result1);

    // 先用高斯滤波器进行滤波后再进行边缘检测
    GaussianBlur(im, resultGauss, Size(3, 3), 10);
    Laplacian(resultGauss, result2, -1, 3);
    convertScaleAbs(result2, result2);

    showImage("result1", result1);
    showImage("result2", result2);

    waitKey(0);
    destroyAllWindows();

    return 0;
}