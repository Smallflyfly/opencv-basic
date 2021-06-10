//
// Created by smallflyfly on 2021/6/10.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // circle
//    Mat im = imread("test.jpg");

    Mat im;

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "camera read error" << endl;
    }
    cap >> im;
    cap.release();

    vector<Mat> gauss, laps;
    int level = 2;
    gauss.push_back(im);
    for (int i = 0; i < level; ++i) {
        Mat gas;
        pyrDown(gauss[i], gas);
        gauss.push_back(gas);
    }
    // construct lap pyramid
    for (int i = gauss.size() - 1; i > 0 ; i--) {
        Mat lap, upGauss;
        if (i == gauss.size() - 1) {
            // top level gauss  down -> up
            Mat down;
            pyrDown(gauss[i], down);
            pyrUp(down, upGauss);
        } else {
            pyrUp(gauss[i+1], upGauss);
        }
        cout << gauss[i].size << endl;
        cout << upGauss.size << endl;
        subtract(gauss[i], upGauss, lap);
        laps.push_back(lap);
    }

    int i = 0;
    for (i = 0; i < gauss.size()-1; ++i) {
        imshow("gauss"+to_string(i), gauss[i]);
        imshow("lap"+to_string(i), laps[i]);
    }
    imshow("gauss"+to_string(i), gauss[i]);

    waitKey(0);

    destroyAllWindows();

    return 0;
}