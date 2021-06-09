//
// Created by smallflyfly on 2021/6/9.
//

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>


using namespace cv;
using namespace std;


int main() {
    Mat mat(3, 4, CV_8UC3, Scalar(0, 0, 1));
    cout << mat << endl;
    cout << "########################" << endl;

    Vec3b vc3 = mat.at<Vec3b>(0, 0);
    int a = vc3.val[0];
    int b = vc3.val[1];
    int c = vc3.val[2];
    cout << a << " " << b << " " << c << endl;
    cout << "########################" << endl;

    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            Vec3b vc = mat.at<Vec3b>(i, j);
            cout << (int)vc.val[0] << " " << (int)vc.val[1] << " " << (int)vc.val[2] << " ";
        }
        cout << endl;
    }
    cout << "########################" << endl;


    for (int i = 0; i < mat.rows; i ++) {
        uchar *ptr = mat.ptr<uchar>(i);
        for (int j = 0; j < mat.cols*mat.channels(); ++j) {
            cout << (int)ptr[j] << " ";
        }
        cout << endl;
    }

    cout << "iter read" << endl;

    MatIterator_<Vec3b> it = mat.begin<Vec3b>();
    MatIterator_<Vec3b> end = mat.end<Vec3b>();
    for (int i = 0; it != end; ++it) {
        cout << (int)(*it).val[0] << " " << (int)(*it).val[1] << " " << (int)(*it).val[2];
        ++i;
        if (i % (mat.cols * mat.channels()) != 0) {
            cout << " ";
        }
        if ((i % mat.cols) == 0) {
            cout << endl;
        }
    }

    return 0;
}