//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test.jpg");

    // ͼ��ÿ��ͨ����ֵ
    Scalar mean;
    mean = cv::mean(im);
    cout << mean << endl;
    cout << mean[0] << " " << mean[1] << " " <<  mean[2] << endl;

    // ͼ���ֵ �� ��׼����
    Mat meanMat, stdMat;

    cv::meanStdDev(im, meanMat, stdMat);

    cout << "ͼ���ֵ �� ��׼����" << endl;
    cout << meanMat << endl;
    cout << stdMat << endl;

    cout << meanMat.at<double>(0) << " " << meanMat.at<double>(1) << " " << meanMat.at<double>(2) << endl;
    cout << stdMat.at<double>(0) << " " << stdMat.at<double>(1) << " " << stdMat.at<double>(2) << endl;

    return 0;
}