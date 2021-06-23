//
// Created by smallflyfly on 2021/6/22.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat im = imread("rice.jfif");
    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);

    Mat imBin;
    threshold(gray, imBin, 150, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(imBin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (auto & contour : contours) {
        // 计算图像连通域的几何矩和中心距以及归一化的几何矩
        Moments m;
        m = moments(contour, true);
        cout << "spatial moments: " << endl
        << "m00: " << m.m00 << " m01: " << m.m01 << " m10: " << m.m10 << endl
        << "m11: " << m.m11 << " m02: " << m.m02 << " m20: " << m.m20 << endl
        << "m12: " << m.m12 << " m21: " << m.m21 << " m03: " << m.m03 << " m30: " << m.m30 << endl;

        cout << "central moments: " << endl
        << "mu20: " << m.mu20 << " mu02: " << m.mu02 << " mu11: " << m.mu11 << endl
        << "mu30: " << m.mu30 << " mu21: " << m.mu21 << " mu12: " << m.mu12 << " mu03: " << m.mu03 << endl;

        cout << "central normalized moments: " << endl
        << "nu20: " << m.nu20 << " nu11: " << m.nu11 << " nu02: " << m.nu02 << endl
        << "nu30: " << m.nu30 << " nu21: " << m.nu21 << " nu12: " << m.nu12 << " nu03: " << m.nu03 << endl;

        // 计算 Hu矩
        Mat hu;
        HuMoments(m, hu);
        cout << "************** Hu moments *********************" << endl
        << hu << endl;
    }

    // 轮廓匹配
    Mat fang1 = imread("fang1.png");
    Mat fang2 = imread("fang2.png");

    Mat gray1, gray2;
    cvtColor(fang1, gray1, CV_BGR2GRAY);
    cvtColor(fang2, gray2, CV_BGR2GRAY);

    Mat fangBin1, fangBin2;
    threshold(gray1, fangBin1, 125, 255, THRESH_BINARY_INV);
    threshold(gray2, fangBin2, 125, 255, THRESH_BINARY_INV);

    vector<vector<Point>> contours1;
    vector<vector<Point>> contours2;

    findContours(fangBin1, contours1, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    findContours(fangBin2, contours2, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    imshow("fangBin1", fangBin1);
    imshow("fangBin2", fangBin2);

    // 模板
    Moments m2 = moments(contours2[0]);
    Mat hu2;
    HuMoments(m2, hu2);

    int i = 0;
    for (auto &contour : contours1) {
        Moments m = moments(contour);
        Mat hu;
        HuMoments(m, hu);
        // match
        double dis;
        dis = matchShapes(hu, hu2, CONTOURS_MATCH_I1, 0);
        if (dis < 1) {
            drawContours(fang1, contours1, i, Scalar(0, 0, 255), 2);
        }
        i++;
    }

    imshow("fang1", fang1);

    waitKey(0);
    destroyAllWindows();

    return 0;

}