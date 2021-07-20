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
    readTxt(speckleInfo,structureInfo,sensorInfo,intrinsic,path);

    Mat img = imread("../images/full_fov_speckle.bmp");
    cout << path << endl;
    return 0;
}
