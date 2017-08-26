//
//  Shiu58.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"
using namespace std;
using namespace cv;

bool
Shiu58::load(string filename) {
	_status = 0;
	bool ret = _cf.load(filename);	if (!ret) return false;
	_status = 1;
	
	return true;
}

bool
Shiu58::setup(Mat& frame) {
	
	return true;
}

bool
Shiu58::run(Mat& frame) {
	_f = frame;
	cvt(_f, _g, _h, _mask);
	bool ret = detect(_g, _box, _level, _weight);	if (!ret) return false;
	
	return true;
}

bool
Shiu58::cvt(Mat& f, Mat& g, Mat& h, Mat& mask) {
	Mat u(f.rows, f.cols, CV_32FC3);
	cvtColor(f, u, COLOR_BGR2HSV);
	inRange(u, Scalar(0, 55, 0), Scalar(28, 175, 255), mask);
	std::vector<Mat> hsv;
	split(u, hsv);
	blur(hsv[2], g, Size(3, 3));
	medianBlur(g, g, 5);
	h = hsv[0];
//	inRange(h, Scalar(0), Scalar(28), mask);
	
	return true;
}
#if 0
cv::InRangeS(ctx->temp_image3,
			 cv::Scalar(0, 55, 90, 255),
			 cv::Scalar(28, 175, 230, 255),
			 ctx->thr_image);

/* Apply morphological opening */
cv::MorphologyEx(ctx->thr_image, ctx->thr_image, NULL, ctx->kernel,
				 cv::_MOP_OPEN, 1);
cv::Smooth(ctx->thr_image, ctx->thr_image, cv::_GAUSSIAN, 3, 3, 0, 0);
#endif
bool
Shiu58::detect(Mat& g, Rect& box, int& level, double& weight) {
	if (_status < 1) return false;

	Mat h = g;
	std::vector<Rect> list;
	std::vector<int> level_list;
	std::vector<double> weight_list;
	_cf.detectMultiScale(h, list, level_list, weight_list, 1.1, 3, 0, Size(), Size(), true);
	int n = (int)list.size();		if (n < 1) return false;
	box = list[0];
	level = level_list[0];
	weight = weight_list[0];
	for (int i=1; i<n; i++) {
		if (weight_list[i] > weight) {
			box = list[i];
			level = level_list[i];
			weight = weight_list[i];
		}
	}
	
	_status = 2;
	
	return true;
}

bool
Shiu58::show(Mat& frame) {
	rectangle(frame, _box, Scalar(0xFF, 0x00, 0xFF));
//	rectangle(frame, _roi, Scalar(0x00, 0x00, 0xFF));
	
	return true;
}
