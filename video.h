#include <opencv2/opencv.hpp>
using namespace cv;

class Video
{
	public:
		VideoCapture cap;
		Mat currentframe;
		bool isBlurred, detectedEdges, isGradient, adjustedBrightness, adjustedContrast, isNegative, isGreyscale,
			 isZoomed, isRotated, isFlippedH, isFlippedV;
		int gaussianKernel, minThreshold, maxThreshold, brightnessVal;
		double contrastVal;

		Video(int camera);

		Mat getFrame();
		void update(int key, int kernelSize, int minThreshold, int maxThreshold, int brightnessVal, float contrastVal);
		void applyChanges();
		void applyGaussian();
		void applyCanny();
		void applySobel();
		void adjustBrightness();
		void adjustContrast();
		void makeNegative();
		void applyConvertTo(double alpha, int beta);
		void makeGreyscale();
		void zoomOut();
		void rotate();
		void applyFlip(int type);
};

