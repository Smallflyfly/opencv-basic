//
// Created by smallflyfly on 2021/6/15.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test3.jfif");
    if (im.empty()) {
        cerr << "image file read error" << endl;
        return -1;
    }
//    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat im1;
    bilateralFilter(im, im1, 9, 40, 40);

    showImage("im", im);
    showImage("im1", im1);

    waitKey(0);
    destroyAllWindows();

    return 0;
}