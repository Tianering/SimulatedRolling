#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("../images/full_fov_speckle.bmp");
    cout << "start" << endl;
    return 0;
}
