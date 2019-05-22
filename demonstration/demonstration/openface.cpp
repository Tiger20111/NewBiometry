//code this file Bezlepkin Matthew
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include <QTextStream>
#include <qfile.h>
#include <QWidget>


using namespace std;
using namespace cv;


class VideoProcesser {
	QString inputfilename, demonstrarion_input;
	QString outputfilename;
	bool is_digit(char a) {
		if (a >= '0' && a <= '9')
			return true;
		else
			return false;
	}
	double extract_double_from_string(QString s) {
		double x = 0;
		int i = 0;
		while (i < s.length() && s[i].digitValue() != -1) {
			x *= 10;

			x += s[i].digitValue();
			++i;
		}
		if (s[i] != '.') {
			cout << "NOOOOOOO";
			return -1000000.0;
		}
		++i;
		double d = 10.0;
		while (i < s.length() && s[i].digitValue() != -1) {

			double a = s[i].digitValue();
			x += a / d;
			d *= 10;
			++i;
		}
		return x;
	}
	int extract_int_from_string(QString s) {
		int x = 0;
		int i = 0;
		while (i < s.length() && s[i].digitValue() != -1) {
			x *= 10;
			x += s[i].digitValue();
			++i;
		}
		return x;
	}

	/*pair<vector<double>, vector<double> > get_eye_marks_from_photo() {
		vector<QString> v;
		string s;
		freopen("image_5.csv", "r", stdin);
		while (!feof(stdin)) {
			cin >> s;
			v.push_back(s);
		}
		cout << v.size() << endl;
		cout << v[711] << endl;
		vector<double> eye_marks_x(56), eye_marks_y(56);
		vector<vector<QString> > eye_marks_strings(56, vector<QString>(2));
		for (int i = 0; i < 56; ++i) {
			eye_marks_strings[i][0] = v[10 + i + v.size() / 2];
		}
		for (int i = 0; i < 56; ++i) {
			eye_marks_strings[i][1] = v[66 + i + v.size() / 2];
		}
		for (int i = 0; i < 56; ++i) {
			eye_marks_x[i] = extract_double_from_string(eye_marks_strings[i][0]);
			eye_marks_y[i] = extract_double_from_string(eye_marks_strings[i][1]);
		}
		return make_pair(eye_marks_x, eye_marks_y);
	}
	*/
	pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > get_eye_marks_from_video(QString inputstream) {
		vector<QString> v;
		QString s;
		QFile fileIn(inputstream);
		fileIn.open(QFile::ReadOnly | QFile::Truncate);
		QTextStream readStream(&fileIn);
		int j = 0, k = 0;
		char c;
		s = "123";
		while (s != "") {
			readStream >> s;
			v.push_back(s);
			++j;
		}
		int sz = v.size() / 714 - 1;
		vector< vector<double> > eye_marks_x(sz, vector<double>(56)), eye_marks_y(sz, vector<double>(56));
		vector<double> time_stamps(sz);
		vector<int> frames(sz);
		vector<vector<QString> > eye_marks_strings1(sz, vector<QString>(56)), eye_marks_strings2(sz, vector<QString>(56));
		vector<QString> time_stamps_strings(sz);
		vector<QString> frames_strings(sz);
		for (int j = 0; j < sz; ++j) {
			for (int i = 0; i < 56; ++i) {
				eye_marks_strings1[j][i] = v[(j + 1) * 714 + 13 + i];
				eye_marks_strings2[j][i] = v[69 + i + (j + 1) * 714];
			}
			time_stamps_strings[j] = v[(j + 1) * 714 + 2];
			frames_strings[j] = v[(j + 1) * 714];
		}
		for (int j = 0; j < sz; ++j) {
			for (int i = 0; i < 56; ++i) {
				eye_marks_x[j][i] = extract_double_from_string(eye_marks_strings1[j][i]);
				eye_marks_y[j][i] = extract_double_from_string(eye_marks_strings2[j][i]);
			}
			time_stamps[j] = extract_double_from_string(time_stamps_strings[j]);
			frames[j] = extract_int_from_string(frames_strings[j]);
		}
		return make_pair(make_pair(eye_marks_x, eye_marks_y), make_pair(frames, time_stamps));
	}

	double extract_center_marks_from_frame(vector<double> eye_marks, int num) {
		vector<double> sight_marks_1(8), sight_marks_2(8);
		vector<double> big_circle_marks_1(8), big_circle_marks_2(8);
		for (int i = 0; i < 8; ++i) {
			sight_marks_1[i] = eye_marks[i + 20];
			sight_marks_2[i] = eye_marks[i + 48];
			big_circle_marks_1[i] = eye_marks[i];
			big_circle_marks_2[i] = eye_marks[i + 28];
		}
		vector<double>x(4, 0);
		for (int i = 0; i < 8; ++i) {
			x[0] += sight_marks_1[i];
			x[1] += sight_marks_2[i];
			x[2] += big_circle_marks_1[i];
			x[3] += big_circle_marks_2[i];
		}
		x[0] /= 8;
		x[1] /= 8;
		x[2] /= 8;
		x[3] /= 8;
		return x[num];
	}
	vector<double> extract_center_marks_from_video(vector<vector<double> > eye_marks, int num) {
		int sz = eye_marks.size(), n = eye_marks[0].size();
		vector<double> x(sz);
		for (int j = 0; j < sz; ++j) {
			x[j] = extract_center_marks_from_frame(eye_marks[j], num);
		}
		return x;
	}

	//���������� �� �������
	vector<pair<double, double> > extract_key_points_from_video(vector<double> x, vector<double> y, vector<double> t, double left_border = 0, double right_border = 0, double delta = 0) {
		int n = t.size();
		vector<pair<double, int> > num_t(n);
		for (int i = 0; i < n; ++i) {
			num_t[i] = make_pair(t[i], i);
		}
		sort(num_t.begin(), num_t.end());

		vector<double> sorted_x(n), sorted_y(n);
		for (int i = 0; i < n; ++i) {
			sorted_x[i] = x[num_t[i].second];
			sorted_y[i] = y[num_t[i].second];
		}
		vector<double> starts(4), ends(4);
		int main_start, main_end;
		double main_start_t, main_end_t;
		int i1 = 0, i2 = n - 1;
		while (i1 < n && num_t[i1].first < num_t[0].first + left_border)
			++i1;
		while (i2 >= 0 && num_t[i2].first >= num_t[n - 1].first - right_border)
			--i2;
		main_end = i2;
		main_start = i1;
		main_start_t = num_t[i1].first;
		main_end_t = num_t[i2].first;
		starts[0] = main_start_t;
		starts[2] = (main_start_t + main_end_t) / 2;
		starts[1] = (main_start_t + starts[2]) / 2;
		starts[3] = (starts[2] + main_end_t) / 2;
		ends[0] = starts[1];
		ends[1] = starts[2];
		ends[2] = starts[3];
		ends[3] = main_end_t;
		for (int i = 0; i < 4; ++i) {
			if (i !=3) ends[i] -= delta;
			if (i != 0) starts[i] += delta;
		}
		if (i1 >= n || i2 < 0 || i2 <= i1) {
			cout << "TIME_ERROR!!!!!!";
		}
		vector<int> frame_nums(4, 0);
		vector<pair<double, double> > ans(4, make_pair(0.0, 0.0));
		for (int i = 0; i < n; ++i) {
			double tt = num_t[i].first;
			for (int j = 0; j < 4; ++j) {
				if (tt >= starts[j] && tt < ends[j]) {
					ans[j].first += sorted_x[i];
					ans[j].second += sorted_y[i];
					++frame_nums[j];
				}
			}
		}
		for (int i = 0; i < 4; ++i) {
			ans[i].first /= frame_nums[i];
			ans[i].second /= frame_nums[i];
		}
		return ans;
	}

	Mat build_transformation_matrix(vector<double> end_vec_x, vector<double> end_vec_y) {
		vector<Point2f> end_vec_point(4);
		for (int i = 0; i < 4; ++i) {
			end_vec_point[i] = Point2f(end_vec_x[i], end_vec_y[i]);
		}

		Point2f A_(100, 100), B_(1820, 100), C_(1820, 880), D_(100, 880);
		vector<Point2f> start_vec_point_2f(4);
		start_vec_point_2f[0] = A_;
		start_vec_point_2f[1] = B_;
		start_vec_point_2f[2] = C_;
		start_vec_point_2f[3] = D_;

		return getPerspectiveTransform(end_vec_point, start_vec_point_2f);
	}

	pair<vector<double>, vector<double> > get_stimul_eye_screen_coordinates(vector<double> x, vector<double> y, Mat transform_matrix) {
		int n = x.size();
		vector<Point2f> start_Points(n);
		for (int i = 0; i < n; ++i) {
			start_Points[i] = Point2f(x[i], y[i]);
		}
		vector<Point2f> result_Points = start_Points;
		perspectiveTransform(start_Points, result_Points, transform_matrix);
		vector<double> x_(n), y_(n);
		for (int i = 0; i < n; ++i) {
			x_[i] = result_Points[i].x;
			y_[i] = result_Points[i].y;
		}
		return make_pair(x_, y_);
	}
public:
	VideoProcesser(QString in, QString dem, QString out) {
		inputfilename = in;
		outputfilename = out;
		demonstrarion_input = dem;
	}
	/*void solve(double callibration_time = 20.0) {
		pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > eye_marks_v = get_eye_marks_from_video();
		vector<double> eye_x_coordinates = extract_center_marks_from_video(eye_marks_v.first.first, 0), eye_y_coordinates = extract_center_marks_from_video(eye_marks_v.first.second, 0);
		vector<double> t = eye_marks_v.second.second;
		vector<pair<double, double> > callibration_points = extract_key_points_from_video(eye_x_coordinates, eye_y_coordinates, t, 0.0, 40.0, 0.0);
		vector<double> callib_point_x(4), callib_point_y(4);
		for (int i = 0; i < 4; i++) {
			callib_point_x[i] = callibration_points[i].first;
			callib_point_y[i] = callibration_points[i].second;
		}
		int i1 = 0;
		vector<double> stimul_eye_marks_x, stimul_eye_marks_y;
		while (i1 < t.size() && t[i1] < callibration_time)
			++i1;
		int start_stimulating_num = i1;
		while (i1 < t.size()) {
			stimul_eye_marks_x.push_back(eye_x_coordinates[i1]);
			stimul_eye_marks_y.push_back(eye_y_coordinates[i1]);
			++i1;
		}
		Mat perspective_mat = build_transformation_matrix(callib_point_x, callib_point_y);
		pair<vector<double>, vector<double> > ans = get_stimul_eye_screen_coordinates(stimul_eye_marks_x, stimul_eye_marks_y, perspective_mat);

		QFile fileOut(output_file);
		QTextStream writeStream(&fileOut);
		if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
			return;

		for (int i = 0; i < ans.first.size; ++i) {
			writeStream << t[start_stimulating_num + i] << ans.first[i] << " " << ans.second[i] << "\n";
		}
		return;
	}*/
	void solve_2inputs() {
		QString calibration_input_file = inputfilename, demonstrarion_input_file = demonstrarion_input;

		pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > eye_marks__calibration_v = get_eye_marks_from_video(calibration_input_file);
		vector<double> calibration_eye_x_coordinates = extract_center_marks_from_video(eye_marks__calibration_v.first.first, 0), calibration_eye_y_coordinates = extract_center_marks_from_video(eye_marks__calibration_v.first.second, 0);
		vector<double> calibration_t = eye_marks__calibration_v.second.second;
		vector<pair<double, double> > callibration_points = extract_key_points_from_video(calibration_eye_x_coordinates, calibration_eye_y_coordinates, calibration_t, 1.3, 0.0, 0.3);
		vector<double> callib_point_x(4), callib_point_y(4);
		for (int i = 0; i < 4; i++) {
			callib_point_x[i] = callibration_points[i].first;
			callib_point_y[i] = callibration_points[i].second;
		}

		QString openface_calib_out_string("C:/Users/Tiger20111/Documents/biometry/openfaceCalib.txt");
		QFile openFace_calib_out_file(openface_calib_out_string);
		QTextStream openFace_calib_out_stream(&openFace_calib_out_file);
		if (!openFace_calib_out_file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		for (int i = 0; i < calibration_t.size(); ++i) {
			openFace_calib_out_stream  << calibration_t[i]  << " " << calibration_eye_x_coordinates[i] << " " << calibration_eye_y_coordinates[i] << " \n ";
		}

		/*QString centerout("C:/Users/Tiger20111/Documents/biometry/centers.txt");
		QFile Center(centerout);
		QTextStream writeStreamC(&Center);
		if (!Center.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		for (int i = 0; i < 4; ++i) {
			writeStreamC << callib_point_x[i] << " " << callib_point_y[i] << "  |  ";
		}
		*/
		pair<pair<vector<vector<double> >, vector<vector<double> > >, pair<vector<int>, vector<double> > > eye_marks__demonstration_v = get_eye_marks_from_video(demonstrarion_input_file);
		vector<double> demonstration_eye_x_coordinates = extract_center_marks_from_video(eye_marks__demonstration_v.first.first, 0), demonstration_eye_y_coordinates = extract_center_marks_from_video(eye_marks__demonstration_v.first.second, 0);
		vector<double> demonstration_t = eye_marks__demonstration_v.second.second;
		vector<double> stimul_eye_marks_x = demonstration_eye_x_coordinates, stimul_eye_marks_y = demonstration_eye_y_coordinates;

		Mat perspective_mat = build_transformation_matrix(callib_point_x, callib_point_y);
		QString output_openface_demonstration_name("C:/Users/Tiger20111/Documents/biometry/output_openFace_demo.txt");
		QFile output_openface_demonstration_file(output_openface_demonstration_name);
		QTextStream output_openface_demonstration_Stream(&output_openface_demonstration_file);
		if (!output_openface_demonstration_file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		for (int i = 0; i < demonstration_t.size(); ++i) {
			output_openface_demonstration_Stream << demonstration_t[i] << " " << stimul_eye_marks_x[i] << " " << stimul_eye_marks_y[i] << "\n";
		}
		pair<vector<double>, vector<double> > ans = get_stimul_eye_screen_coordinates(stimul_eye_marks_x, stimul_eye_marks_y, perspective_mat);

		/*pair<vector<double>, vector<double> > demo = get_stimul_eye_screen_coordinates(callib_point_x, callib_point_y, perspective_mat);


		QString demout("C:/Users/Tiger20111/Documents/biometry/democenters.txt");
		QFile DemCenter(demout);
		QTextStream writeStreamD(&DemCenter);
		if (!DemCenter.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		for (int i = 0; i < 4; ++i) {
			writeStreamD << demo.first[i] << " " << demo.second[i] << "  |  ";
		}
		*/

		QString output_file = outputfilename;
		//QString output_file = "C:/Users/Tiger20111/Documents/biometry/123.txt";

		QFile fileOut(output_file);
		QTextStream writeStream(&fileOut);
		if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		double minX = 100.0, maxX = 0.0, minY = 100.0, maxY = 0.0;


		for (int i = 0; i < ans.first.size(); ++i) {
			writeStream << demonstration_t[i]<< " " << ans.first[i] << " " << ans.second[i] << "\n";
			if (ans.first[i] < minX)
				minX = ans.first[i];
			if (ans.first[i] > maxX)
				maxX = ans.first[i];
			if (ans.second[i] < minY)
				minY = ans.second[i];
			if (ans.second[i] < minY)
				minY = ans.second[i];
		}
		writeStream << 0.0 << " " << minX << " " << maxX << " " << minY << " " << maxY << "\n";
		writeStream << 0.0 << " " << minX << " " << maxX << " " << minY << " " << maxY << "\n";

		writeStream.flush();

		return;

	}
};
