#include <iostream>
#include <opencv2/opencv.hpp>

#include "objectIR.h"
#include "rolling.h"

using namespace std;
using namespace cv;


int main() {
    String path = "../config/config.txt";
    Speckle_info speckleInfo;
    Structure_info structureInfo;
    Sensor_info sensorInfo;
    Intrinsic intrinsic;
    // 读取参数文件，获取相机内参等参数
    readTxt(speckleInfo, structureInfo, sensorInfo, intrinsic, path);
    Mat img = imread("../images/full_fov_speckle.bmp");

    Mat img1 = Mat(img.rows, img.cols, CV_16FC3, Scalar(0, 0, 0));
    // 右手坐标系
    // 欧拉角为RPY角（roll、pitch、yaw），即xyz顺序
    Vec3d euler_angles;
    euler_angles[0] = 0;
    euler_angles[1] = 1;
    euler_angles[2] = 0;
    img1 = rotateX(img, intrinsic, euler_angles);
    imwrite("../images/rotated_y.png", img1);
    return 0;
}
