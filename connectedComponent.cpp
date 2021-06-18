//
// Created by smallflyfly on 2021/6/16.
//

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int main() {

    Mat im = imread("rice.jfif");
    resize(im, im, Size(0, 0), 0.5, 0.5);
    Mat gray;
    cvtColor(im, gray, CV_BGR2GRAY);


    imshow("im", im);

    Mat im1;
    threshold(gray, im1, 125, 255, THRESH_BINARY);

    imshow("im1", im1);

    RNG rng(10010);
    Mat out;
    int num = connectedComponents(im1, out, 8, CV_16U);
    vector<Vec3b> colors;
    for (int i=0; i<num; i++) {
        // 使用均匀分布的随机确定颜色
        Vec3b vec = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        colors.push_back(vec);
    }
    Mat result = Mat::zeros(im.size(), im.type());
    for (int i = 0; i < im.rows; ++i) {
        for (int j = 0; j < im.cols; ++j) {
            int label = out.at<uint16_t>(i, j);
            if (label == 0) {
                continue;
            }
            result.at<Vec3b>(i, j) = colors[label];
        }
    }

    imshow("result", result);

    Mat labels, stats, centroids;
    int count = connectedComponentsWithStats(im1, labels, stats, centroids, 8);
    cout << count << endl;

    for (int i = 1; i < count; ++i) {
        int x = centroids.at<double>(i, 0);
        int y = centroids.at<double>(i, 1);
        cout << x << " " << y << endl;
        circle(im, Point(x, y), 2, Scalar(0, 0, 255), -1);
        int xmin = stats.at<int>(i, CC_STAT_LEFT);
        int ymin = stats.at<int>(i, CC_STAT_TOP);
        int w = stats.at<int>(i, CC_STAT_WIDTH);
        int h = stats.at<int>(i, CC_STAT_HEIGHT);

        Rect rect(xmin, ymin, w, h);
        rectangle(im, rect, Scalar(0, 255, 255), 2);
        putText(im, to_string(i), Point(x+5, y), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.3, Scalar(0, 0, 255), 1);
    }

    imshow("connected", im);

    waitKey(0);
    destroyAllWindows();

    return 0;

}