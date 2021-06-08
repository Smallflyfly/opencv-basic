//
// Created by smallflyfly on 2021/6/8.
//


#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

using namespace std;
using namespace cv;


int main() {
    VideoCapture cap;
    cap.open(0);
    Mat frame;
    while (cap.isOpened()) {
        cap >> frame;
        imshow("camera", frame);
        if (waitKey(1) == 'q') {
            break;
        }
    }
    destroyAllWindows();
    cap.release();
}