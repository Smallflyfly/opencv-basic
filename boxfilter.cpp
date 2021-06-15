//
// Created by smallflyfly on 2021/6/11.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("test.jpg");
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat box1, box2;
    boxFilter(im, box1, -1, Size(3, 3), Point(-1, -1), true);
    boxFilter(im, box2, -1, Size(3, 3), Point(-1, -1), false);

    imshow("box1", box1);
    imshow("box2", box2);

    waitKey(0);

    destroyAllWindows();


    return 0;

}