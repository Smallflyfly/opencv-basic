//
// Created by smallflyfly on 2021/6/22.
//

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Vec4f lines;
    vector<Point2f> points;
    const static float pts[20][2] = {
            {0.0f,0.0f},{10.0f,11.0f},{21.0f,20.0f},{30.0f,30.0f},
            {40.0f,42.0f},{50.0f,50.0f},{60.0f,60.0f},{70.0f,70.0f},
            {80.0f,80.0f},{90.0f,92.0f},{100.0f,100.0f},{110.0f,110.0f},
            {120.f,120.0f},{136.0f,130.0f},{138.0f,140.0f},{150.0f,150.0f},
            {160.0f,163.0f},{175.0f,170.0f},{181.0f,180.0f},{200.0f,190.0f}
    };
    for (int i = 0; i < 20; ++i) {
        points.emplace_back(pts[i][0], pts[i][1]);
    }
    double param = 0.0;
    double reps = 0.01;
    double aeps = 0.01;
    fitLine(points, lines, DIST_L1, param, reps, aeps);
    cout << lines << endl;

    return 0;
}