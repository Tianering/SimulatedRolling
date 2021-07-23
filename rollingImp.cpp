//
// Created by shanyi on 2021/7/20.
//
#include "stringSpilt.h"
#include "rolling.h"

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

//
Mat trans1(Mat &image, Mat &img_out, Intrinsic intrinsic, Speckle_info speckleInfo, Structure_info structureInfo,
           Sensor_info sensorInfo, double dis) {
    Matrix<double, 3, 3> rotateMat;
    for (int v = 0; v < img_out.rows; v++) {
        for (int u = 0; u < img_out.cols; u++) {
            double x = (u - intrinsic.cx) / intrinsic.fx;
            double y = (v - intrinsic.cy) / intrinsic.fy;
            Matrix<double, 3, 1> po;
            po << x * dis + structureInfo.baseline, y * dis, dis;
            po[0] = (po[0] * speckleInfo.distance / dis) + speckleInfo.center.x;
            po[1] = (po[1] * speckleInfo.distance / dis) + speckleInfo.center.y;
            vector<int> bgr = BilinearInterpolation(po, image);
            ColorChart(img_out, u, v, bgr);
        }
    }
    return img_out;
}