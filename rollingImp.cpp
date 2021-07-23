//
// Created by shanyi on 2021/7/20.
//
#include "stringSpilt.h"
#include "rolling.h"
#include "interpolatinoChart.h"

// 读取txt文件
void readTxt(Speckle_info &speckleInfo, Structure_info &structureInfo, Sensor_info &sensorInfo, Intrinsic &intrinsic,
             string path) {
    ifstream myfile(path);
    vector<string> s1;
    string temp;
    while (getline(myfile, temp)) //按行读取字符串
        s1.push_back(temp);
    speckleInfo.distance = stod(stringSplit(stringSplit(s1[1], " ")[2], "mm")[0]);
    speckleInfo.length_per_pixel = stod(stringSplit(stringSplit(s1[2], " ")[2], "mm")[0]);
    speckleInfo.center.y = stod(stringSplit(stringSplit(stringSplit(s1[3], " ")[2], ",")[0], "[")[1]);
    speckleInfo.center.x = stod(stringSplit(stringSplit(stringSplit(s1[3], " ")[2], ",")[1], "[")[0]);

    string t = stringSplit(s1[6], " ")[2];
    if (t == "left")
        structureInfo.ldmp_direction = 0;
    else
        structureInfo.ldmp_direction = 1;
    structureInfo.baseline = stod(stringSplit(stringSplit(s1[7], "=")[1], "mm")[0]);

    sensorInfo.pixelsize = stod(stringSplit(stringSplit(s1[10], " ")[2], "mm")[0]);
    sensorInfo.width = stod(stringSplit(s1[11], " ")[2]);
    sensorInfo.height = stod(stringSplit(s1[12], " ")[2]);

    intrinsic.fx = stod(stringSplit(s1[15], " ")[2]);
    intrinsic.fy = stod(stringSplit(s1[16], " ")[2]);
    intrinsic.cx = stod(stringSplit(s1[17], " ")[2]);
    intrinsic.cy = stod(stringSplit(s1[18], " ")[2]);
    intrinsic.k1 = stod(stringSplit(s1[19], " ")[2]);
    intrinsic.k2 = stod(stringSplit(s1[20], " ")[2]);
    intrinsic.k3 = stod(stringSplit(s1[21], " ")[2]);
    intrinsic.p1 = stod(stringSplit(s1[22], " ")[2]);
    intrinsic.p2 = stod(stringSplit(s1[23], " ")[2]);
    myfile.close();

}

// 欧拉角转旋转矩阵
Matrix<double, 3, 3> eulerToMatrix(Vec3d euler_angles) {
    Matrix<double, 3, 3> R_x, R_y, R_z, rotateMat;
    R_x << 1, 0, 0,
            0, cos(euler_angles[0]), -sin(euler_angles[0]),
            0, sin(euler_angles[0]), cos(euler_angles[0]);
    R_y << cos(euler_angles[1]), 0, sin(euler_angles[1]),
            0, 1, 0,
            -sin(euler_angles[1]), 0, cos(euler_angles[1]);
    R_z << cos(euler_angles[2]), -sin(euler_angles[2]), 0,
            sin(euler_angles[2]), cos(euler_angles[2]), 0,
            0, 0, 1;
    rotateMat = R_x * R_y * R_z;
    cout << rotateMat << endl;
    return rotateMat;
}

// 旋转图像
void rotateX(Mat &image, Mat &image_out, Vec3d euler_angles) {
    Matrix<double, 3, 3> rotateMat;
    rotateMat = eulerToMatrix(euler_angles);
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            Matrix<double, 3, 1> img_pixel, img_rotating;
            img_pixel << x, y, 400;
            img_rotating = rotateMat * img_pixel;
            vector<int> bgr = BilinearInterpolation(img_rotating, image);
            ColorChart(image_out, x, y, bgr);
        }
    }
}

// 获取不同距离的图像
Mat trans1(Mat &image, Mat &img_out, Intrinsic intrinsic, Speckle_info speckleInfo, Structure_info structureInfo,
           double dis) {
    Matrix<double, 3, 3> rotateMat;
    for (int v = 0; v < img_out.rows; v++) {
        for (int u = 0; u < img_out.cols; u++) {
            // 将传感器转至相机坐标系
            double x = (u - intrinsic.cx) / intrinsic.fx;
            double y = (v - intrinsic.cy) / intrinsic.fy;
            Matrix<double, 3, 1> po;
            po << x * dis + structureInfo.baseline, y * dis, dis;
            po[0] = (po[0] * speckleInfo.distance / dis) + speckleInfo.center.x;
            po[1] = (po[1] * speckleInfo.distance / dis) + speckleInfo.center.y;
            // 在原图上取值，并赋值给新图
            vector<int> bgr = BilinearInterpolation(po, image);
            ColorChart(img_out, u, v, bgr);
        }
    }
    return img_out;
}