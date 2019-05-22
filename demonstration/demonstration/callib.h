//code this file Protsenko Nikita
#include <QGraphicsScene>
#include <QWidget>
#include <cmath>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QTextStream>
#include <QTimeLine>
#include <qfile.h>

class Callib {
public:
	Callib();
	void runAnimation(std::vector<std::pair<int, int>> points, int timeAnimation);
private:
	QTimeLine *runTimer(int timeAnimation);
	void ShowOneBall(QGraphicsItemAnimation *animation, std::vector<std::pair<int, int>> points);


};

