//
// Created by smallflyfly on 2021/6/21.
//

#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat im = imread("test.jpg", IMREAD_GRAYSCALE);
    resize(im, im, Size(0, 0), 0.4, 0.4);

    imshow("im", im);

    Mat imBin;
    threshold(im, imBin, 125, 255, THRESH_BINARY);
    imshow("imBin", imBin);

    Mat m = getStructuringElement(0, Size(3, 3));

    // 开 闭 梯度 顶帽  黑帽  击不击中运算
    Mat open, close, gradient, tophat, blackhat, hitmiss;
    morphologyEx(imBin, open, MORPH_OPEN, m, Point(-1, -1), 3);
    imshow("open", open);

    morphologyEx(imBin, close, MORPH_CLOSE, m, Point(-1, -1), 3);
    imshow("close", close);

    morphologyEx(imBin, gradient, MORPH_GRADIENT, m, Point(-1, -1), 3);
    imshow("gradient", gradient);

    morphologyEx(imBin, tophat, MORPH_TOPHAT, m, Point(-1, -1), 3);
    imshow("topHat", tophat);

    morphologyEx(imBin, blackhat, MORPH_BLACKHAT, m, Point(-1, -1), 3);
    imshow("blackHat", blackhat);

    morphologyEx(imBin, hitmiss, MORPH_HITMISS, m, Point(-1, -1), 3);
    imshow("hitmiss", hitmiss);

    waitKey(0);
    destroyAllWindows();

    return 0;

}