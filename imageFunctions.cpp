#include "imageFunctions.h"
Mat gaussian(Mat original, int kernel)
{
	Mat newImg;
	if (kernel % 2 == 0)
		kernel--;
	GaussianBlur(original, newImg, Size(kernel,kernel), 0, 0, 2);
	return newImg;
}

void callbackButton(int state, void* userdata)
{
	if (state == 0)
		state = 1;
	else
		state = 0;
}