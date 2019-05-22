//code this file Protsenko Nikita
#include "callib.h"

#include "mypoint.h"

#include <QDebug>
#include <QThread>


Callib::Callib() {

}

void DrawBorder1(QGraphicsScene *scene) {
	scene->setSceneRect(0, 0, 1920, 1080);
	QPen mypen = QPen(Qt::red);

	QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
	QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
	QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
	QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

	scene->addLine(TopLine, mypen);
	scene->addLine(LeftLine, mypen);
	scene->addLine(RightLine, mypen);
	scene->addLine(BottomLine, mypen);
}

void Callib::ShowOneBall(QGraphicsItemAnimation *animation, std::vector<std::pair<int, int>> callibPoints) {

	/*
	for (unsigned long i = 0; i < points.size(); i++) {
		double num = (double)((double)i / (double)(points.size() - 1));
		QPointF* pos = new QPointF(points[i].first, points[i].second);
		animation->setPosAt(num, QPointF(points[i].first, points[i].second));
	}
	*/

	
	animation->setPosAt((double)(0), QPointF(callibPoints[0].first, callibPoints[0].second));
	animation->setPosAt((double)(0.245), QPointF(callibPoints[0].first, callibPoints[0].second));

	animation->setPosAt((double)(0.255), QPointF(callibPoints[1].first, callibPoints[1].second));
	animation->setPosAt((double)(0.495), QPointF(callibPoints[1].first, callibPoints[1].second));

	animation->setPosAt((double)(0.505), QPointF(callibPoints[2].first, callibPoints[2].second));
	animation->setPosAt((double)(0.745), QPointF(callibPoints[2].first, callibPoints[2].second));

	animation->setPosAt((double)(0.755), QPointF(callibPoints[3].first, callibPoints[3].second));
	animation->setPosAt((double)(1), QPointF(callibPoints[3].first, callibPoints[3].second));
	
	//for (int i = 0; i < 980; ++i)
	//	animation->setPosAt(i / 980.0, QPointF(1820, i));

}

QTimeLine *Callib::runTimer(int timeAnimation) {
	QTimeLine *timer = new QTimeLine(timeAnimation);
	timer->setFrameRange(0, 100);
	timer->setUpdateInterval(0.00001);
	return timer;
}

void Callib::runAnimation(std::vector<std::pair<int, int>> points, int timeAnimation) {

	QGraphicsView *view;
	QGraphicsScene *scene = new QGraphicsScene();
	
	view = new QGraphicsView(scene);

	DrawBorder1(scene);
	QTimeLine* timer = runTimer(timeAnimation);

	MyPoint *point = new MyPoint();

	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
	animation->setItem(point);
	animation->setTimeLine(timer);

	ShowOneBall(animation, points);

	scene->addItem(point);
	view->show();
	timer->start();
	
}
