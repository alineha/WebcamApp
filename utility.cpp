#include "utility.h"

void createTutorialWindow()
{
	Mat img(420, 300, CV_8UC3, Scalar(0, 0, 0));
	putText(img, "G = Gaussian Blur", Point2f(1, 20), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "E = Edge Detection", Point2f(1, 50), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "L = Sobel Filter", Point2f(1, 80), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "B = Increase Brightness", Point2f(1, 110), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "I = Lower Brightness", Point2f(1, 140), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "C = Increase Contrast", Point2f(1, 170), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "O = Lower Contrast", Point2f(1, 200), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "N = Negative", Point2f(1, 230), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "Y = Greyscale", Point2f(1, 260), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "Z = Zoom Out", Point2f(1, 290), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "R = Rotate", Point2f(1, 320), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "H = Horizontal Flip", Point2f(1, 350), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "V = Vertical Flip", Point2f(1, 380), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	putText(img, "S = Start/Stop Recording", Point2f(1, 410), FONT_HERSHEY_COMPLEX_SMALL, 0.9, Scalar(255, 255, 255));
	imshow("Cheatsheet", img);
}

void initializeTrackbars()
{
	namedWindow("Values", 0);
	int init = 0;
	createTrackbar("Kernel", "Values", &init, 9);
	createTrackbar("-Threshold", "Values", &init, 255);
	createTrackbar("+Threshold", "Values", &init, 255);
	createTrackbar("Brightness", "Values", &init, 255);
	createTrackbar("Contrast", "Values", &init, 100);
}