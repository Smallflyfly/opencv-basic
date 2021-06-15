//
// Created by smallflyfly on 2021/6/15.
//

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {
    float points[] = {
            1, 2, 3, 4, 5,
            6, 7, 8, 9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20,
            21, 22, 23, 24, 25
    };
    Mat data(5, 5, CV_32FC1, points);

    // 验证高斯滤波器可分离
    Mat gaussX = getGaussianKernel(3, 1);
    cout << gaussX << endl;
    Mat gaussDstData, gaussDataXY;
    GaussianBlur(data, gaussDstData, Size(3, 3), 1, 1, BORDER_CONSTANT);
    sepFilter2D(data, gaussDataXY, -1, gaussX, gaussX, Point(-1, -1), 0, BORDER_CONSTANT);
    cout << gaussDstData << endl;
    cout << gaussDataXY << endl;
    cout << "######################################" << endl;

    // Y方向上滤波
    Mat a = (Mat_<float>(3, 1) << -1, 3, -1);
    // X方向上滤波
    Mat b = a.reshape(1, 1);
    // XY联合滤波
    Mat ab = a * b;
    Mat dataX, dataY, dataXY1, dataXY2, dataSepXY;
    filter2D(data, dataX, -1, b);
    filter2D(dataX, dataXY1, -1, a);
    filter2D(data, dataXY2, -1, ab);
    sepFilter2D(data, dataSepXY, -1, a, b);

    // 验证结果
    cout << dataXY1 << endl;
    cout << dataXY2 << endl;
    cout << dataSepXY << endl;

    Mat im = imread("test.jpg");
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat imX, imY, imXY, imSepXY;
    filter2D(im, imX, -1, b);
    filter2D(imX, imXY, -1, a);
    sepFilter2D(im, imSepXY, -1, a, b);

    imshow("imXY", imXY);
    imshow("imSepXY", imSepXY);

    waitKey(0);
    destroyAllWindows();

    return 0;

}