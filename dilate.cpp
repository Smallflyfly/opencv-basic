//
// Created by smallflyfly on 2021/6/18.
//

#include "opencv2/opencv.hpp"

#include <iostream>

using namespace cv;
using namespace std;

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

    Mat dilateM1, dilateM2;
    dilate(src, dilateM1, m1, Point(-1, -1), 5);
    dilate(src, dilateM2, m2, Point(-1, -1), 5);

    imshow("src", src);
    imshow("dilateM1", dilateM1);
    imshow("dilateM2", dilateM2);

    Mat xbim = imread("xiaobai.jpg");
    Mat xbM1, xbM2;
    dilate(xbim, xbM1, m1, Point(-1, -1), 2);
    dilate(xbim, xbM2, m2, Point(-1, -1), 2);

    imshow("xbim", xbim);
    imshow("xbM1", xbM1);
    imshow("xbM2", xbM2);

    Mat im = imread("rice.jfif");
    resize(im, im, Size(0, 0), 0.6, 0.6);
    Mat im1 = im.clone();

    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);
    Mat riceBin;
    threshold(gray, riceBin, 125, 255, THRESH_BINARY);

    Mat out, stats, centroids;
    int count1 = connectedComponentsWithStats(riceBin, out, stats, centroids, 8, CV_16U);
    drawResult(im, count1, stats, centroids, "no dilate");

    Mat dilateIm1, dilateIm2;
    dilate(riceBin, dilateIm1, m1, Point(-1, -1), 5);
    dilate(riceBin, dilateIm2, m2, Point(-1, -1), 5);

    int count2 = connectedComponentsWithStats(dilateIm1, out, stats, centroids, 8, CV_16U);
    drawResult(dilateIm1, count2, stats, centroids, "dilateIm1");
    int count3 = connectedComponentsWithStats(dilateIm2, out, stats, centroids, 8, CV_16U);
    drawResult(dilateIm2, count3, stats, centroids, "dilateIm2");

    waitKey(0);
    destroyAllWindows();

}