//
// Created by smallflyfly on 2021/6/18.
//

#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;


void drawResult(Mat im, int num, Mat stats, Mat centroids, const string& name) {
    for (int i = 1; i < num; ++i) {
        int x = centroids.at<double>(i, 0);
        int y = centroids.at<double>(i, 1);
        cout << x << " " << y << endl;
        circle(im, Point(x, y), 2, Scalar(0, 0, 255), -1);
        int xmin = stats.at<int>(i, CC_STAT_LEFT);
        int ymin = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);

        Rect rect(xmin, ymin, w, h);
        rectangle(im, rect, Scalar(255, 255, 255), 2);
        putText(im, to_string(i), Point(x+5, y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.3, Scalar(0, 0, 255), 1);
    }
    imshow(name, im);
}


int main() {

    Mat src = (
                Mat_<uchar>(6, 6) <<
                        0, 0, 0, 0, 255, 0,
                        0, 255, 255, 255, 255, 255,
                        0, 255, 255, 255, 255, 0,
                        0, 255, 255, 255, 255, 0,
                        0, 255, 255, 255, 255, 0,
                        0, 0, 0, 0, 255, 0
            );
    resize(src, src, Size(0, 0), 50, 50, INTER_NEAREST);
    Mat m1, m2;
    m1 = getStructuringElement(0, Size(3, 3));
    m2 = getStructuringElement(1, Size(3, 3));

    Mat erodeM1, erodeM2;
    erode(src, erodeM1, m1, Point(-1, -1), 10);
    erode(src, erodeM2, m2, Point(-1, -1), 10);

    imshow("src", src);
    imshow("erodeM1", erodeM1);
    imshow("erodeM2", erodeM2);

    Mat xbim = imread("xiaobai.jpg");
    Mat xbM1, xbM2;
    erode(xbim, xbM1, m1, Point(-1, -1), 2);
    erode(xbim, xbM2, m2, Point(-1, -1), 2);

    imshow("xb", xbim);
    imshow("xbM1", xbM1);
    imshow("xbM2", xbM2);

    Mat im = imread("rice.jfif");
    Mat im1 = im.clone();


    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);
    Mat riceBin;
    threshold(gray, riceBin, 125, 255, THRESH_BINARY);

    Mat out, stats, centroids;
    int count1 = connectedComponentsWithStats(riceBin, out, stats, centroids, 8, CV_16U);
    drawResult(im1, count1, stats, centroids, "no erode");

    Mat erodeIm1, erodeIm2;
    erode(riceBin, erodeIm1, m1, Point(-1, -1), 5);
    erode(riceBin, erodeIm2, m2, Point(-1, -1), 5);

    int count2 = connectedComponentsWithStats(erodeIm1, out, stats, centroids, 8, CV_16U);
    drawResult(erodeIm1, count2, stats, centroids, "erode1");
    int count3 = connectedComponentsWithStats(erodeIm2, out, stats, centroids, 8, CV_16U);
    drawResult(erodeIm2, count3, stats, centroids, "erode2");

    waitKey(0);
    destroyAllWindows();

}