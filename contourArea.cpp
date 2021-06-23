//
// Created by smallflyfly on 2021/6/22.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat im = imread("rice.jfif");
    resize(im, im, Size(0, 0), 0.5, 0.5);
    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);

    Mat imBin;
    threshold(gray, imBin, 125, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(imBin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    drawContours(im, contours, -1, Scalar(255, 0, 255));

    for (int i = 0; i < contours.size(); ++i) {
        double area = contourArea(contours[i]);
        double length = arcLength(contours[i], true);
        cout << "area: " << area << " " << "length: " << length << endl;
    }

    imshow("im", im);

    waitKey(0);
    destroyAllWindows();

    return 0;

}