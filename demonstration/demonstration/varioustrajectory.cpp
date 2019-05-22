//code this file Protsenko Nikita
#include "varioustrajectory.h"

std::pair<double, double> NextPointCircle(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * sin(frequency * time);
	new_point.second = radius * cos(frequency * time);
	return new_point;
}

ArgumentsTrajectory *ArgumentsCircle() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 1;
	arguments->radius = 390;
//	arguments->time = arguments->radius * 10;
	arguments->speed = 1;
	//arguments->frequency = (2 * 3.14 * (arguments->radius)) / (arguments->time / arguments->numTurn);
	arguments->frequency = 0.001;
	arguments->startX = 960;
	
	//arguments->updateinterval = ((30000) / (arguments->time * arguments->numTurn * arguments->speed));
	arguments->startY = 490;
	return arguments;
}

std::pair<double, double> NextPointSpiral(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * sin(3 * frequency * time + 1.57);
	new_point.second = radius * sin(2 * frequency * time);
	return new_point;
}

ArgumentsTrajectory *ArgumentsSpiral() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 1;
	arguments->radius = 100;
	arguments->frequency = 0.01;
	arguments->startX = 400;
	arguments->startY = 400;
	return arguments;
}

std::pair<double, double> NextPointQuadro(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	if (time < 3150) {
		new_point.first = 300 + (double)(time * (1.0 / 3150)) * 1120;
		new_point.second = 300;
		return new_point;
	}
	if (time >= 3150 && time < 4900) {
		new_point.first = 1420;
		new_point.second = 300 + (double)((time - 3150) * (double)(1.0 / 1750)) * 280;
		return new_point;
	}

	if (time >= 4900 && time < 8150) {
		new_point.first = 1420 - (time - 4900) * (1.0 / 3250) * 1120;
		new_point.second = 580;
		return new_point;
	}

	if (time >= 8150 && time < 10000) {
		new_point.first = 300;
		new_point.second = 580 - (time - 8150) * (1.0 / 1850) * 280;
		return new_point;
	}
	return new_point;
}

ArgumentsTrajectory *ArgumentsQuadro() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 1;
	arguments->radius = 390;
	//	arguments->time = arguments->radius * 10;
	arguments->speed = 100;
	//arguments->frequency = (2 * 3.14 * (arguments->radius)) / (arguments->time / arguments->numTurn);
	arguments->frequency = 0.001;
	arguments->startX = 0;

	//arguments->updateinterval = ((30000) / (arguments->time * arguments->numTurn * arguments->speed));
	arguments->startY = 0;
	return arguments;
}

std::pair<double, double> NextPointLove(double time, double radius, double frequency) {
	std::pair<double, double> new_point(0, 0);
	new_point.first = radius * (16 * pow(sin(frequency * time), 3));
	new_point.second = radius * (13 * cos(frequency * time) - 5 * cos(2 * frequency * time) - 2 * cos(3 * frequency * time) - cos(4 * frequency * time));
	return new_point;
}

ArgumentsTrajectory *ArgumentsLove() {
	ArgumentsTrajectory *arguments = new ArgumentsTrajectory();
	arguments->numTurn = 0;
	arguments->radius = 0;
	arguments->frequency = 0;
	arguments->startX = 0;
	arguments->startY = 0;
	return arguments;
}

//Circle::pointFunc Circle::getFunc() {
//	return &Circle::NextPointCircle;
//}