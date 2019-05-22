//code this file Protsenko Nikita
#include "demonstration.h"
#include <QtWidgets/QApplication>
#include "camera.h"
#include "callib.h"
#include "calculatecoordinates.h"
#include <QWidget>
#include <QThread>

#include "finalvisual.cpp"
#include "openface.cpp"

//#include<shellapi.h>
//#include<Windows.h>


const QString in = "C:/Users/Tiger20111/Documents/biometry/in.txt";
//QString in = "C:/Users/Tiger20111/Documents/biometry/openfaceCalib.txt";

const int freqCamera = 30;
const int callibTime = 15000;
const int demonstrationTime = 15000;
const int freqAnimation = 10000;

const QString ballIn = "C:/Users/Tiger20111/Documents/biometry/trajectory.txt";
const QString outBall = "C:/Users/Tiger20111/Documents/biometry/outBall.txt";
const QString outEye = "C:/Users/Tiger20111/Documents/biometry/outEye.txt";

const String outBallV = "C:/Users/Tiger20111/Documents/biometry/outBall.txt";
const String outEyeV = "C:/Users/Tiger20111/Documents/biometry/outEye.txt";

const String callibVideo = "C:/Users/Tiger20111/Documents/biometry/callib.mkv";
const String demonstrationVideo = "C:/Users/Tiger20111/Documents/biometry/demonstration.mkv";

const QString callibOpenFace = "C:/Users/Tiger20111/Documents/biometry/OpenFace_2.0.5_win_x64/processed/callib.csv";
const QString demonstrationOpenFace = "C:/Users/Tiger20111/Documents/biometry/OpenFace_2.0.5_win_x64/processed/demonstration.csv";

const String visualOut = "C:/Users/Tiger20111/Documents/biometry/visual.mkv";


class MyThreadCamera : public QThread {
public:
	String file;
	double time;
	void run() {
		Camera camera;
		camera.recordVideo(file, time, freqCamera);
	}
	void setParam(String file1, double time1) {
		file = file1;
		time = time1;
	}
};


void demonstration() {

	MyThreadCamera* thread = new MyThreadCamera();
	thread->setParam(demonstrationVideo, demonstrationTime + 3000);
	thread->start();

	Ball* ball = new Ball(ballIn);
	ball->runAnimation(demonstrationTime, freqAnimation);
	
}

void calculateCoordinates(QString in, QString ballIn, QString outBall, QString outEye) {
	setCoordinates(demonstrationTime, freqCamera, freqAnimation, in, ballIn, outBall, outEye);
}

void callibration() {
	MyThreadCamera* thread = new MyThreadCamera();
	thread->setParam(callibVideo, callibTime - 5000);
	thread->start();

	std::vector<std::pair<int, int>> callibPoints;
	callibPoints.push_back({ 100, 100 });
	callibPoints.push_back({ 1820, 100 });
	callibPoints.push_back({ 1820, 880 });
	callibPoints.push_back({ 100, 880 });

	Callib* callibration = new Callib();
	callibration->runAnimation(callibPoints, callibTime);

}



void openFace() {
	//	char input_file_name[11] = "Nikita.csv";
	//	VideoProcesser v(input_file_name);
	//	pair<vector<double>, vector<double> > ans = v.solve();
}

void comparison() {

}

class MyThreadDemonstration : public QThread {
public:
	void run(int argc, char *argv[]) {
		QApplication a(argc, argv);

		//QThread::sleep(40000);
		//clock_t t1 = clock();
		//clock_t t0 = clock();
		//while(((t1 - t0) < 4000)) {
		//	t1 = clock();
		//}
		demonstration();
		a.exec();
	}
};

class MyThreadDCallib : public QThread {
public:
	void run(int argc, char *argv[]) {
		QApplication b(argc, argv);

		callibration();
		b.exec();
	}
};


void runOpenFace() {
//	ShellExecute(NULL, "open", "C:/Users/Tiger20111/Documents/biometry/OpenFace_2.0.5_win_x64/FeatureExtraction.exe", )
}

int main(int argc, char *argv[])
{
	
	/*
	MyThreadDCallib* thread1 = new MyThreadDCallib();
	thread1->run(argc, argv);
	thread1->quit();

	MyThreadDemonstration* thread2 = new MyThreadDemonstration();
	thread2->run(argc, argv);
	*/
	
	runOpenFace();

	VideoProcesser* openFace = new VideoProcesser(callibOpenFace, demonstrationOpenFace, in);
	openFace->solve_2inputs();

	calculateCoordinates(in, ballIn, outBall, outEye);
	
	Visual* visual = new Visual();
	visual->makeFinalVideo(outBallV, outEyeV, visualOut);
	//comparison();

	return 0;
}


