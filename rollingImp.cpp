//
// Created by shanyi on 2021/7/20.
//
#include "stringSpilt.h"
#include "rolling.h"

void readTxt(Speckle_info speckleInfo, Structure_info structureInfo, Sensor_info sensorInfo, Intrinsic intrinsic,
             string path) {
    ifstream myfile(path);
    vector<string> s1;
    string temp;
    while (getline(myfile, temp)) //按行读取字符串
        s1.push_back(temp);
    speckleInfo.distance = stod(stringSplit(stringSplit(s1[1], " ")[2], "mm")[0]);
    speckleInfo.length_per_pixel = stod(stringSplit(stringSplit(s1[2], " ")[2], "mm")[0]);
    speckleInfo.center.x = stod(stringSplit(stringSplit(stringSplit(s1[3], " ")[2], ",")[0], "[")[1]);
    speckleInfo.center.y = stod(stringSplit(stringSplit(stringSplit(s1[3], " ")[2], ",")[1], "[")[0]);

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