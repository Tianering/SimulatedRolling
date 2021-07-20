//
// Created by shanyi on 2021/7/20.
//
#include <opencv2/opencv.hpp>

using namespace cv;

class Speckle_info {
public:
    double distance; //距离mm
    double length_per_pixel; //长度与像素比mm
    Point2d center; //中心点
};

class Structure_info {
public:
    int ldmp_direction; //0:left,1:right
    double baseline; //基线长度mm
};

class Sensor_info {
public:
    double pixelsize; //像素所代表的长度mm
    double width;
    double height;
};

class Intrinsic {
public:
    double fx; //焦距
    double fy;
    double cx; //主点
    double cy;
    double k1; //径向畸变
    double k2;
    double k3;
    double p1; //切向畸变
    double p2;
};

