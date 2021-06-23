//
// Created by smallflyfly on 2021/6/22.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat im = imread("rice.jfif");
//    resize(im, im, Size(0, 0), 0.5, 0.5);
    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);

    Mat imBin;
    threshold(gray, imBin, 150, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(imBin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    Mat im1 = im.clone();
    Mat im2 = im.clone();
    for (auto & contour : contours) {
        // 最大外接矩阵
        Rect rect = boundingRect(contour);
        rectangle(im, rect, Scalar(0, 0, 255), 1);

        // 最小外接矩形
        RotatedRect rotatedRect = minAreaRect(contour);
        Point2f pts[4];
        rotatedRect.points(pts);
        Point2f pt = rotatedRect.center;
        for (int i = 0; i < 4; ++i) {
            if (i == 3) {
                line(im1, pts[i], pts[0], Scalar(255, 255, 0), 1);
            } else {
                line(im1, pts[i], pts[i+1], Scalar(255, 255, 0), 1);
            }
        }
        circle(im1, pt, 1, Scalar(0, 0, 255), -1);

        // 外接多边形
        Mat ploys;
        approxPolyDP(contour, ploys, 5, true);
        // draw ploy
        Vec2i pt1, pt2;
        for (int i = 0; i < ploys.rows; ++i) {
            if (i == ploys.rows - 1) {
                pt1 = ploys.at<Vec2i>(i);
                pt2 = ploys.at<Vec2i>(0);

            } else {
                pt1 = ploys.at<Vec2i>(i);
                pt2 = ploys.at<Vec2i>(i+1);
            }
            line(im2, pt1, pt2, Scalar(0, 0, 255), 2);
        }
    }

    imshow("im", im);
    imshow("im1", im1);
    imshow("im2", im2);

    waitKey(0);
    destroyAllWindows();

    return 0;

}