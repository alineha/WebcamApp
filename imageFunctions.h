#include <opencv2/opencv.hpp>
using namespace cv;
#pragma once
Mat gaussian(Mat original, int kernel);
void callbackButton(int state, void* userdata);