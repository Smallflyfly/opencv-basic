//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "read camera error!" << endl;
        return -1;
    }
    Mat frame;
    cap >> frame;

    cap.release();

    Mat gray, rgb;
    cvtColor(frame, gray, CV_BGR2GRAY);

    cvtColor(frame, rgb, CV_BGR2RGB);

    imshow("bgr", frame);
    imshow("gray", gray);
    imshow("rgb", rgb);

    waitKey(0);

    destroyAllWindows();

    return 0;
}