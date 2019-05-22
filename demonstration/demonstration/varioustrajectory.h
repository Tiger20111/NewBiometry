//code this file Protsenko Nikita
#include <cmath>
#include <QWidget>
#include "animationball.h"

std::pair<double, double> NextPointCircle(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsCircle();

std::pair<double, double> NextPointSpiral(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsSpiral();

std::pair<double, double> NextPointQuadro(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsQuadro();

std::pair<double, double> NextPointLove(double time, double radius, double frequency);
ArgumentsTrajectory *ArgumentsLove();

