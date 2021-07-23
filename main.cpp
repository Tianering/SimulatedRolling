#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <iomanip>

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
    Vec3d translation;
    // 平移向量
    Mat img = imread("../images/trans_400.png");
    Mat img1 = Mat(img.rows, img.cols, img.type(), Scalar(0, 0, 0));
    // 欧拉角为RPY角（roll、pitch、yaw），即xyz顺序
    for (int a = 1; a < 6; a++) {
        Vec3d euler_angles;
        euler_angles[0] = 0;
        euler_angles[1] = 0;
        euler_angles[2] = M_PI / 180 * a * 0.3;
        rotateX(img, img1, euler_angles);
        path = "../images/400_z" + to_string(a) + ".png";
        imwrite(path, img1);
    }

//    double dis = 400;
//    Mat img_out = Mat(sensorInfo.height, sensorInfo.width, img.type(), Scalar(0, 0, 0));
//    trans1(img, img_out, intrinsic, speckleInfo, structureInfo, sensorInfo, dis);
//    imwrite("../images/trans_400.png", img_out);
//    return 0;
}
