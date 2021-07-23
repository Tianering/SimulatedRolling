//
// Created by shanyi on 2021/7/23.
//

#include "interpolatinoChart.h"

// 双线性插值法
vector<int> BilinearInterpolation(Matrix<double, 3, 1> point, cv::Mat image) {
    //cout << point << endl;
    vector<int> bgr1(3);
    bgr1[0] = 0;
    bgr1[1] = 0;
    bgr1[2] = 0;
    double y = point(0);
    double x = point(1);
    if (y > image.cols || y < 0 || isnan(y) || x > image.rows || x < 0 || isnan(x)) {
        return bgr1;
    }
    int x1 = floor(x);
    int x2 = x1 + 1;
    int y1 = floor(y);
    int y2 = y1 + 1;
    //cout << x2 << "\t" << y2 << "\t" << endl;
    //cv::Mat image = imread(image_path);
    // 第一次线性插值（底部）
    int rx1y1 = image.at<cv::Vec3b>(x1, y1)[2];
    int rx2y1 = image.at<cv::Vec3b>(x2, y1)[2];
    int gx1y1 = image.at<cv::Vec3b>(x1, y1)[1];
    int gx2y1 = image.at<cv::Vec3b>(x2, y1)[1];
    int bx1y1 = image.at<cv::Vec3b>(x1, y1)[0];
    int bx2y1 = image.at<cv::Vec3b>(x2, y1)[0];
    double R1 = ((x - x1) / (x2 - x1)) * rx1y1 + ((x2 - x) / (x2 - x1)) * rx2y1;
    double G1 = ((x - x1) / (x2 - x1)) * gx1y1 + ((x2 - x) / (x2 - x1)) * gx2y1;
    double B1 = ((x - x1) / (x2 - x1)) * bx1y1 + ((x2 - x) / (x2 - x1)) * bx2y1;
    // 第二次线性插值
    Vec3b point_x1y2 = image.at<cv::Vec3b>(x1, y2);
    int rx1y2 = point_x1y2[2];
    int gx1y2 = point_x1y2[1];
    int bx1y2 = point_x1y2[0];
    Vec3b point_x2y2 = image.at<cv::Vec3b>(x2, y2);
    int rx2y2 = point_x2y2[2];
    int gx2y2 = point_x2y2[1];
    int bx2y2 = point_x2y2[0];

    double R2 = ((x - x1) / (x2 - x1)) * rx1y2 + ((x2 - x) / (x2 - x1)) * rx2y2;
    double G2 = ((x - x1) / (x2 - x1)) * gx1y2 + ((x2 - x) / (x2 - x1)) * gx2y2;
    double B2 = ((x - x1) / (x2 - x1)) * bx1y2 + ((x2 - x) / (x2 - x1)) * bx2y2;
    // 第三次线性插值
    double R = ((y - y1) / (y2 - y1)) * R1 + ((y2 - y) / (y2 - y1)) * R2;
    double G = ((y - y1) / (y2 - y1)) * G1 + ((y2 - y) / (y2 - y1)) * G2;
    double B = ((y - y1) / (y2 - y1)) * B1 + ((y2 - y) / (y2 - y1)) * B2;

    bgr1[0] = B;
    bgr1[1] = G;
    bgr1[2] = R;
    return bgr1;
}

// 多通道图像赋值
void ColorChart(Mat &image, int x, int y, vector<int> point) {
    //cout << x << "," << y << endl;
    image.at<cv::Vec3b>(y, x)[0] = point[0];
    image.at<cv::Vec3b>(y, x)[1] = point[1];
    image.at<cv::Vec3b>(y, x)[2] = point[2];
    //cout << image.at<cv::Vec3b>(y, x) << endl;
}
