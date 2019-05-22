//code this file Bezlepkin Matthew
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

class Visual {
public:
	Mat getMat1(Point a, Point b, Point c, int resolution_x = 1920, int resolution_y = 1080) {
		int radius = 20;
		Mat img = Mat(Size(resolution_x, resolution_y), CV_8UC3);
		circle(img, a, 1, Scalar(0, 255, 255), radius, LINE_8, 0);
		circle(img, b, 1, Scalar(255, 0, 255), radius, LINE_8, 0);
		circle(img, c, 1, Scalar(255, 255, 0), radius, LINE_8, 0);
		return img;
	}


	void makeFinalVideo(String file1, String file2, String output) {

		//QFile F1(file1), F2(file2);
		//QTextStream readStream1(&F1), readStream2(&F2);
		VideoWriter video(output, CV_FOURCC('X', 'V', 'I', 'D'), 15, Size(1920, 1080), true);

		double x1, y1, x2, y2, x3, y3;

		std::vector<std::pair<double, double> > ball, eye;
		
		ball = fillVector(file1);
		eye = fillVector(file2);

		for (int i = 0; i < eye.size(); i++) {
			x1 = ball[i].first;
			y1 = ball[i].second;

			x2 = eye[i].first;
			y2 = eye[i].second;

			y3 = y2;
			x3 = x2;
			Point a(x1, y1), b(x2, y2), c(x3, y3);
			Mat frame = getMat1(a, b, c);;
			video.write(frame);			
		}
		return;
	}

	std::vector<std::pair<double, double> > fillVector(String file) {
		std::vector<std::pair<double, double> > array;
		std::ifstream in1;
		in1.open(file);
		double x1 = 0;
		double y1 = 0;
		while (in1 >> x1) {
			in1 >> y1;
			array.push_back(std::make_pair(x1, y1));
		}
		return array;
	}
};

