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
//    VideoCapture cap;
//    cap.open(0);
    VideoCapture cap(0);
    Mat frame;
    int h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    cout << h << " " << w << endl;
    while (cap.isOpened()) {
        cap >> frame;
        imshow("camera", frame);
        if (waitKey(1) == 'q') {
            break;
        }

        int value = frame.at<uchar>(10, 10);
        cout << value << endl;

    }
    destroyAllWindows();
    cap.release();

    return 0;
}