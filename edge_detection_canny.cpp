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

    Mat im = imread("test.jpg", IMREAD_GRAYSCALE);
    if (im.empty()) {
        cerr << "image file read error" << endl;
        return -1;
    }
    resize(im, im, Size(0, 0), 0.5, 0.5);

    Mat result11, result12, result21, result22, result31, result32, result41, result42;
    Canny(im, result11, 100, 200);
    Canny(im, result12, 100, 200, 3, true);

    Canny(im, result21, 20, 50);
    Canny(im, result22, 20, 50, 3, true);

    // gauss blur
    Mat imGauss;
    GaussianBlur(im, imGauss, Size(5, 5), 5);
    Canny(imGauss, result31, 20, 50);
    Canny(imGauss, result32, 20, 50, 3, true);

    Canny(imGauss, result41, 100, 200);
    Canny(imGauss, result42, 100, 200, 3, true);

    showImage("result11", result11);
    showImage("result12", result12);
    showImage("result21", result21);
    showImage("result22", result22);
    showImage("result31", result31);
    showImage("result32", result32);
    showImage("result41", result41);
    showImage("result42", result42);

    waitKey(0);
    destroyAllWindows();

    return 0;
}