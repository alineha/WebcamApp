#include "imageFunctions.h"
#include "utility.h"
#include "video.h"
int main(int argc, char** argv)
{
	int camera = 0;
	int key = 0;
	bool recording = false;

	Video video(camera);
	createTutorialWindow();
	initializeTrackbars();
	
	int w = static_cast<int>(video.cap.get(CAP_PROP_FRAME_WIDTH));
	int h = static_cast<int>(video.cap.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter videoWriter("MyVideo.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, Size(w,h), true);

	for (;;)
	{
		Mat frame;

		key = waitKey(1);

		if (key == 27) break;
		if (key == (int)('S'))
			recording = !recording;

		video.update(key, getTrackbarPos("Kernel", "Values"), getTrackbarPos("-Threshold", "Values"), getTrackbarPos("+Threshold", "Values"), getTrackbarPos("Brightness", "Values"), getTrackbarPos("Contrast", "Values"));

		frame = video.getFrame();
		if (frame.empty()) break; // end of video stream

		imshow("Webcam", frame);
		if (recording)
			videoWriter.write(frame);
	}
	videoWriter.release();
	video.cap.release();  // release the VideoCapture object
	return 0;
}