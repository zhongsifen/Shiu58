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
Shiu58::setup(string filename) {
	status = 0;
	bool ret = this->cf.load(filename);	if (!ret) return false;
	status = 1;
	
	return true;
}

bool
Shiu58::run(Mat& f) {
	this->f = f;
	bool ret = false;
	
	return true;
}

bool
Shiu58::detect(cv::Mat& g, cv::Rect& box)
{
	if (this->status < 1) return false;
	
	std::vector<Rect> list;
	this->cf.detectMultiScale(g, list);
	int n = (int)list.size();		if (n < 1) return false;
	box = list[0];
	for (int i=1; i<n; i++) {
		if (list[i].area() > box.area()) {
			box = list[i];
		}
	}
	
	this->status = 2;
	
	return true;
}

bool
Shiu58::detect_list(cv::Mat& g, std::vector<cv::Rect>& list)
{
	if (this->status < 1) return false;
	
	this->cf.detectMultiScale(g, list);
	int n = (int)list.size();		if (n < 1) return false;
	
	this->status = 2;
	
	return true;
}

bool
Shiu58::detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& box)
{
	if (this->status < 1) return false;
	
	cv::Mat h = g(roi);
	
	std::vector<Rect> list;
	this->cf.detectMultiScale(h, list);
	int n = (int)list.size();		if (n < 1) return false;
	box = list[0];
	for (int i=1; i<n; i++) {
		if (list[i].area() > box.area()) {
			box = list[i];
		}
	}
	
	box.x += roi.x;
	box.y += roi.y;
	
	this->status = 2;
	
	return true;
}

bool
Shiu58::detect(cv::Mat& g, cv::Rect& box, int& level, double& weight) {
	if (this->status < 1) return false;
	
	std::vector<Rect> list;
	std::vector<int> level_list;
	std::vector<double> weight_list;
	this->cf.detectMultiScale(g, list, level_list, weight_list, 1.1, 3, 0, Size(), Size(), true);
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
	
	this->status = 2;
	
	return true;
}

#if 0

void
Shiu58::show_rect(cv::Mat& im, cv::Rect& rect, cv::Scalar color)
{
	rectangle(im, rect, color);
}

void
Shiu58::show_point(cv::Mat& im, cv::Point& pt, cv::Scalar color)
{
	const int radius=4;
	const int thickness=1;
	
	cv::circle(im, pt, radius, color, thickness);
	
	return true;
}

bool
Shiu58::show_points(cv::Mat& im, std::vector<cv::Point>& points, cv::Scalar color)
{
	const int radius=2;
	const int thickness=1;
	
	int size = (int)points.size();
	for (int i = 0; i < size; i++) {
		cv::circle(im, points[i], radius, color, thickness);
	}
	
	return true;
}

bool
Shiu58::show_points(cv::Mat& im, cv::Mat& points, cv::Scalar color)
{
	const int radius=2;
	const int thickness=1;
	
	int n = (int)points.total() / 2;
	double* s = (double*)points.data;
	for (int i = 0; i < n; i++) {
		cv::circle(im, cv::Point(s[i], s[n+i]), radius, color, thickness);
	}
	
	return true;
}

#endif
