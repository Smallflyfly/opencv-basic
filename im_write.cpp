//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/video.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
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

    // 保存图片
    imwrite("test.jpg", frame);

    cap.release();

    return 0;
}