//
// Created by shanyi on 2021/7/20.
//

#ifndef SIMULATEDROLLING_ROLLING_H
#define SIMULATEDROLLING_ROLLING_H

#include <iostream>
#include <fstream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include "objectIR.h"

using namespace std;
using namespace Eigen;

// 读取txt文件，获得相机参数等信息
void readTxt(Speckle_info &speckleInfo, Structure_info &structureInfo, Sensor_info &sensorInfo, Intrinsic &intrinsic,
             string path);

// 旋转图像
void rotateX(Mat &image, Mat &image_out, Vec3d euler_angles);

// 欧拉角转旋转矩阵
Matrix<double, 3, 3> eulerToMatrix(Vec3d euler_angles);

// 获取不同距离图像
Mat trans1(Mat &image, Mat &img_out, Intrinsic intrinsic, Speckle_info speckleInfo, Structure_info structureInfo,
           double dis);

#endif //SIMULATEDROLLING_ROLLING_H
