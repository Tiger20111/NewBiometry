//code this file Protsenko Nikita
#ifndef BALL_H
#define BALL_H

#include <QGraphicsScene>
#include <QWidget>
#include <cmath>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimeLine>
#include <qfile.h>
#include "trajectory.h"

//#include "animationball.h"

class Ball {


public:
	Ball(QString ballIn);
	void runAnimation(int timeAnimation, int freqAnimation);
private:
	void runTrajectory(QGraphicsItemAnimation *animation, int idTrajectory);
	QTimeLine *runTimer(int timeAnimation);
	void setTrajectoryParametrs(int idTrajectory);
	
	QString inputFile = "/home/tigtig/Inprac/Animation/Trajectory/in_ball_tajectory.txt";
	QString outputFile;

	double time;
	double frequency;
	double startX;
	double updateTime;
	double startY;
	double numTurn;
	double radius;
	double sizeBall = 20;
	double posWindowX = 1920;
	double posWindowY = 1080;
	//double updateTime = 0.000001;
	const QString output;
};

#endif // BALL_H
