//code this file Protsenko Nikita
#include "mypoint.h"
#include <iostream>
#include <fstream>

MyPoint::MyPoint() {
	int StartX = 0;
	int StartY = 0;
	setPos(StartX, StartY);
}

QRectF MyPoint::boundingRect() const {
	return QRect(0, 0, 20, 20);
	//left, top angle position
}

void MyPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	QRectF rec = boundingRect();
	QBrush Brush(Qt::green);

	painter->setBrush(Qt::red);
	painter->drawEllipse(rec);
}
