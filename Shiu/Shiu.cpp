//
//  Shiu.cpp
//  Shiu
//
//  Created by SIFEN ZHONG on 13/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu.hpp"
using namespace cv;

Shiu::Shiu(std::string filename)
{
	this->status = 0;
	
	bool ret = this->cf.load(filename);		if (!ret) return;
	
	this->status = 1;
}

bool
Shiu::detect(cv::Mat& g, cv::Rect& box)
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
Shiu::detect_list(cv::Mat& g, std::vector<cv::Rect>& list)
{
	if (this->status < 1) return false;
	
	this->cf.detectMultiScale(g, list);
	int n = (int)list.size();		if (n < 1) return false;
	
	this->status = 2;
	
	return true;
}

bool
Shiu::detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& box)
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
Shiu::detect(cv::Mat& g, cv::Rect& box, int& level, double& weight) {
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
