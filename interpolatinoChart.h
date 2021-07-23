//
// Created by shanyi on 2021/7/23.
//

#ifndef SIMULATEDROLLING_INTERPOLATINOCHART_H
#define SIMULATEDROLLING_INTERPOLATINOCHART_H

#include <iostream>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

vector<int> BilinearInterpolation(Matrix<double, 3, 1> point, cv::Mat image);

void ColorChart(Mat &image, int x, int y, vector<int> point);

#endif //SIMULATEDROLLING_INTERPOLATINOCHART_H
