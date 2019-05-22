//code this file Protsenko Nikita
#include "calculatecoordinates.h"

std::pair<QString, QString> setTimeEyes(QString str) {
	std::pair<QString, QString> new_element = {"", ""};
	int i = 0;
	int j = 0;
	//QString time = "";
	while (str[i] != '\0') {
		//time += str[i]; //need choose
		if (str[i] == " ") {
			j++;
			i++;
			continue;
		}
		if (j == 1) {
			new_element.first += str[i];
		}

		if (j == 2) {
			new_element.second += str[i];
		}
		i++;
	}
	return new_element;
}

void writeCoordinates(QString file, std::vector<std::pair<QString, QString>> array) {
	QFile fileOut(file);
	fileOut.open(QFile::WriteOnly);
	QTextStream writeStream(&fileOut);

	for (int i = 0; i < array.size(); i++) {
		writeStream << array[i].first << " " << array[i].second << " ";
	}
}



	void setCoordinates(int timeVideo, int numCadrVideo, int numCadrBall, QString in, QString ballIn, QString outBall, QString outEye) {

		QFile fileIn(in);
		fileIn.open(QFile::ReadOnly | QFile::Truncate);
		QTextStream readStream(&fileIn);

		QString str = "123";

		int freqCadr = (numCadrBall / (numCadrVideo * (timeVideo / 1000)));
		freqCadr++;
		int i = 0;

		QFile data(ballIn);
		data.open(QFile::ReadOnly | QFile::Truncate);
		QTextStream readStream1(&data);

		std::vector<std::pair<QString, QString> > ball;
		std::vector<std::pair<QString, QString> > eye;


		while (readStream.readLineInto(&str)) {
			//QString time = setTimeEyes(&str);
			eye.push_back(setTimeEyes(str));

			for (int i = 0; i < freqCadr; i++) {
				readStream1.readLineInto(&str);
			}
			ball.push_back(setTimeEyes(str));
		}


		writeCoordinates(outBall, ball);
		writeCoordinates(outEye, eye);
	}
