//
//  ShiuDetect.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 30/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuDetect.hpp"
using namespace std;
using namespace cv;

bool
ShiuDetect::load(string filename) {
	_status = 0;
	bool ret = _cf.load(filename);	if (!ret) return false;
	_status = 1;
	
	return true;
}

bool
ShiuDetect::detect(Mat& g, std::vector<Rect>& box_list, std::vector<int>& level_list, std::vector<double>& weight_list) {
	if (_status < 1) return false;
	
	_cf.detectMultiScale(g, box_list, level_list, weight_list, 1.1, 3, 0, Size(), Size(), true);
	int n = (int)box_list.size();		if (n < 1) return false;
	
	_status = 2;
	
	return true;
}

bool
ShiuDetect::detect(Mat& g, Rect& box, int& level, double& weight) {
	if (_status < 1) return false;
	
	std::vector<Rect> box_list;
	std::vector<int> level_list;
	std::vector<double> weight_list;
	detect(g, box_list, level_list, weight_list);
	int n = (int)box_list.size();		if (n < 1) return false;
	box = box_list[0];
	level = level_list[0];
	weight = weight_list[0];
	for (int i=1; i<n; i++) {
		if (weight_list[i] > weight) {
			box = box_list[i];
			level = level_list[i];
			weight = weight_list[i];
		}
	}
	
	_status = 2;
	
	return true;
}
