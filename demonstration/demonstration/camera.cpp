//code this file Protsenko Nikita
#include "camera.h"
#include <ctime>

void Camera::recordVideo(String file, double time, int freqCamera) {
	VideoCapture vcap(0);
	if (!vcap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return;
	}

	int frame_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	VideoWriter video(file, CV_FOURCC('X', 'V', 'I', 'D'), freqCamera, Size(1280, 720), true);
	vcap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	vcap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	clock_t t0 = clock();

	for (;;) {

		Mat frame;
		vcap >> frame;
		video.write(frame);
		//imshow("Frame", frame);
		clock_t t1 = clock();
		if ((t1 - t0) > time) break;
		char c = (char)waitKey(33);
		if (c == 27) break;
	}
}
