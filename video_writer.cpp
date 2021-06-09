//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video.hpp"

#include "iostream"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "read camera error!" << endl;
        return -1;
    }
    VideoWriter videoWriter;
    // 编码格式
    int coder = VideoWriter::fourcc('M', 'J', 'P', 'G');
    double fps = 25.0;
    Mat frame;
    cap >> frame;
    videoWriter.open("test.avi", coder, fps, frame.size(), true);
    while (cap.isOpened()) {
        cap >> frame;
        videoWriter.write(frame);
        imshow("camera", frame);

        if (waitKey(1) == 'q') {
            break;
        }
    }
    videoWriter.release();
    cap.release();

    destroyAllWindows();

    return 0;
}