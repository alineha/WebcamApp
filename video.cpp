#include "video.h"

Video::Video(int camera)
{
	cap.open(camera);

	isBlurred = false;
	detectedEdges = false;
	isGradient = false;
	adjustedBrightness = false;
	adjustedContrast = false; 
	isNegative = false; 
	isGreyscale = false;
	isZoomed = false;
	isRotated = false;
	isFlippedH = false; 
	isFlippedV = false;

	gaussianKernel = 1;
	minThreshold = 0;
	maxThreshold = 255;
	brightnessVal = 0;
	contrastVal = 1;
}

Mat Video::getFrame()
{
	cap >> currentframe;

	if (!currentframe.empty())
		applyChanges();

	return currentframe;
}

void Video::update(int key, int kernelSize, int  minThreshold, int maxThreshold, int brightnessVal, float contrastVal)
{
	switch (key)
	{
		case (int)('G') :
			isBlurred = !isBlurred;
			if (isBlurred)
				gaussianKernel = ((kernelSize % 2 == 0) ? kernelSize + 1 : kernelSize);
			break;
		case (int)('E') :
			detectedEdges = !detectedEdges;
			if (detectedEdges)
			{
				Video::minThreshold = minThreshold;
				Video::maxThreshold = maxThreshold;
			}
			break;
		case (int)('L') :
			isGradient = !isGradient;
			break;
		case (int)('B') :
			if (Video::brightnessVal > 0)
			{
				adjustedBrightness = false;
				Video::brightnessVal = 0;
			}
			else
			{
				if (!adjustedBrightness)
					adjustedBrightness = true;
				Video::brightnessVal = brightnessVal;
			}
			break;
		case (int)('I') :
			if (Video::brightnessVal < 0)
			{
				adjustedBrightness = false;
				Video::brightnessVal = 0;
			}
			else
			{
				if (!adjustedBrightness)
					adjustedBrightness = true;
				Video::brightnessVal = - brightnessVal;
			}
			break;
		case (int)('C') :
			if (Video::contrastVal > 1)
			{
				adjustedContrast = false;
				Video::contrastVal = 1;
			}
			else
			{
				if (!adjustedContrast)
					adjustedContrast = true;
				Video::contrastVal = contrastVal;
			}
			break;
		case (int)('O') :
			if (Video::contrastVal < 1)
			{
				adjustedContrast = false;
				Video::contrastVal = 1;
			}
			else
			{
				if (!adjustedContrast)
					adjustedContrast = true;
				Video::contrastVal = contrastVal/100;
			}
			break;
		case (int)('N') :
			isNegative = !isNegative;
			break;
		case (int)('Y') :
			isGreyscale = !isGreyscale;
			break;
		case (int)('Z') :
			isZoomed = !isZoomed;
			break;
		case (int)('R') :
			isRotated = !isRotated;
			break;
		case (int)('H') :
			isFlippedH = !isFlippedH;
			break;
		case (int)('V') :
			isFlippedV = !isFlippedV;
			break;
		default:
			break;
	}
}

void Video::applyChanges()
{
	if (isBlurred)
		applyGaussian();
	if (detectedEdges)
		applyCanny();
	if (isGradient)
		applySobel();
	if (adjustedBrightness)
		adjustBrightness();
	if (adjustedContrast)
		adjustContrast();
	if (isNegative)
		makeNegative();
	if (isGreyscale)
		makeGreyscale();
	if (isZoomed)
		zoomOut();
	if (isRotated)
		rotate();
	if (isFlippedH)
		applyFlip(1);
	if (isFlippedV)
		applyFlip(0);
}

void Video::applyGaussian()
{
	Mat aux;
	currentframe.copyTo(aux);
	
	GaussianBlur(aux, currentframe, Size(gaussianKernel, gaussianKernel), 0);

	aux.release();
}

void Video::applyCanny()
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	Canny(aux, currentframe, (double)minThreshold, (double)maxThreshold, 3);
	currentframe.copyTo(aux);
	cvtColor(aux, currentframe, COLOR_GRAY2RGB);

	aux.release();
}

void Video::applySobel()
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	Sobel(aux, currentframe, -1, 1, 1);

	aux.release();
}

void Video::adjustBrightness()
{
	applyConvertTo(1.0, brightnessVal);
}

void Video::adjustContrast()
{
	applyConvertTo(contrastVal, 1);
}

void Video::makeNegative()
{
	applyConvertTo(-1, 255);
}

void Video::applyConvertTo(double alpha, int beta)
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	aux.convertTo(currentframe, -1, alpha, beta);

	aux.release();
}

void Video::makeGreyscale()
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	cvtColor(aux, currentframe, COLOR_RGB2GRAY);
	currentframe.copyTo(aux);
	cvtColor(aux, currentframe, COLOR_GRAY2RGB);

	aux.release();
}

void Video::zoomOut()
{
	Mat aux;
	currentframe.copyTo(aux);

	resize(aux, currentframe, Size(aux.size().width/2, aux.size().height/2));

	aux.release();
}

void Video::rotate()
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	Point2f center(aux.size().width / 2, aux.size().height / 2);
	Mat matRotation = getRotationMatrix2D(center, 90, 1);
	
	warpAffine(aux, currentframe, matRotation, aux.size());

	aux.release();
}

void Video::applyFlip(int type)
{
	Mat aux;
	currentframe.copyTo(aux); // copies the current frame to an auxiliary variable

	flip(aux, currentframe, type);

	aux.release();
}
