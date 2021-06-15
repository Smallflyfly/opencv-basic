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
    resize(im, im, Size(0,0), 0.5, 0.5);

    Mat kernel1 = (Mat_<float>(1, 2) << 1, -1);
    Mat kernel2 = (Mat_<float>(1, 3) << 1, 0, -1);
    Mat kernel3 = (Mat_<float>(3, 1) << 1, 0, -1);
    Mat kernelXY = (Mat_<float>(2, 2) << 1, 0, 0, -1);
    Mat kernelYX = (Mat_<float>(2, 2) << 0, -1, 1, 0);

    // 边缘检测
    Mat result1, result2, result3, resultXY, resultYX;
    // 检测水平方向边缘
    filter2D(im, result1, -1, kernel1);
    convertScaleAbs(result1, result1);
    // 检测水平方向边缘
    filter2D(im, result2, -1, kernel2);
    convertScaleAbs(result2, result2);
    // 检测垂直方向边缘
    filter2D(im, result3, -1, kernel3);
    convertScaleAbs(result3, result3);
    // 整幅图像的边缘
    Mat result23 = result2 + result3;
    // 检测左上到右下的边缘
    filter2D(im, resultXY, -1, kernelXY);
    convertScaleAbs(resultXY, resultXY);
    // 检测右上到左下的边缘
    filter2D(im, resultYX, -1, kernelYX);
    convertScaleAbs(resultYX, resultYX);

    Mat resultXYYX = resultXY + resultYX;

    showImage("result1", result1);
    showImage("result2", result2);
    showImage("result3", result3);
    showImage("result23", result23);
    showImage("resultXY", resultXY);
    showImage("resultYX", resultYX);
    showImage("resultXYYX", resultXYYX);

    waitKey(0);
    destroyAllWindows();


    return 0;

}