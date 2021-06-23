//
// Created by smallflyfly on 2021/6/21.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


void drawLine(const Mat &im, const vector<Vec2f> &lines) {
    Point p1, p2;
    cout << lines.size() << endl;
    for (int i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        double length = max(im.rows, im.cols);

        p1.x = cvRound(x0 + length * (-b));
        p1.y = cvRound(y0 + length * a);

        p2.x = cvRound(x0 - length * (-b));
        p2.y = cvRound(y0 - length * a);

        line(im, p1, p2, Scalar(255), 1);
    }
}

int  main() {
    Mat im = imread("road2.jfif");
    resize(im, im, Size(0, 0), 0.5, 0.5);
    cvtColor(im, im, CV_BGR2GRAY);
    imshow("im", im);


    Mat edge;
    Canny(im, edge, 200, 220, 3, false);
    threshold(edge, edge, 125, 255, THRESH_BINARY);

    imshow("edge", edge);

    // 标准霍夫变换
    vector<Vec2f> lines1, lines2;
    HoughLines(edge, lines1, 1, CV_PI/180, 150);
    HoughLines(edge, lines2, 1, CV_PI/180, 100);

    Mat im1, im2;
    im1 = im.clone();
    im2 = im.clone();

    drawLine(im1, lines1);
    drawLine(im2, lines2);

    imshow("im1", im1);
    imshow("im2", im2);

    // 渐进概率式霍夫变换
    Mat im3, im4;
    im3 = im.clone();
    im4 = im.clone();
    vector<Vec4f> lines3, lines4;
    HoughLinesP(edge, lines3, 1, CV_PI/180, 150, 10, 300);
    HoughLinesP(edge, lines4, 1, CV_PI/180, 100, 10, 300);

    for (Vec4f & i : lines3) {
        line(im3, Point(i[0], i[1]), Point(i[2], i[3]),
             Scalar(255, 255, 255), 1);
    }

    for (Vec4f & i : lines4) {
        line(im4, Point(i[0], i[1]), Point(i[2], i[3]),
             Scalar(255, 255, 255), 1);
    }

    imshow("im3", im3);
    imshow("im4", im4);


    // 通过霍夫变换获取点集合中的直线  采用标准霍夫变换
    const static float points[20][2] = {
            { 0.0f,   369.0f },{ 10.0f,  364.0f },{ 20.0f,  358.0f },{ 30.0f,  352.0f },
            { 40.0f,  346.0f },{ 50.0f,  341.0f },{ 60.0f,  335.0f },{ 70.0f,  329.0f },
            { 80.0f,  323.0f },{ 90.0f,  318.0f },{ 100.0f, 312.0f },{ 110.0f, 306.0f },
            { 120.0f, 300.0f },{ 130.0f, 295.0f },{ 140.0f, 289.0f },{ 150.0f, 284.0f },
            { 160.0f, 277.0f },{ 170.0f, 271.0f },{ 180.0f, 266.0f },{ 190.0f, 260.0f }
    };
    vector<Point2f> pts;
    for (auto point : points) {
        pts.emplace_back(point[0], point[1]);
    }
    vector<Vec3d> lines;
    HoughLinesPointSet(pts, lines, 20, 1, 0, 360, 1, 0,
                       CV_PI / 2, CV_PI / 180);

    for (int i = 0; i < lines.size(); ++i) {
        cout << "votes: " << lines[i][0] << ", "
        << "rho: " << lines[i][1] << ", "
        << "theta :" << lines[i][2] << endl;
    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}