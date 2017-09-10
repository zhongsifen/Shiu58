//
//  ShiuPalm.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 6/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuPalm.hpp"
using namespace cv;

bool
ShiuPalm::init(std::vector<Point>& contour) {
	_contour = contour;
	_area = contourArea(_contour);
	Moments mm = moments(_contour);
	_center = Point((int)round(mm.m10/mm.m00), (int)round(mm.m01/mm.m00));
	_squre = Rect(_center - Point(32, 32), Size(64, 64));
	
	return true;
}

bool
ShiuPalm::show(cv::Mat& img) {
	for (int i=0; i<_contour.size(); ++i) {
		circle(img, _contour[i], 3, Scalar(0xF0, 0x00, 0x00));
	}
	for (int i=1; i<_contour.size(); ++i) {
		line(img, _contour[i-1], _contour[i], Scalar(0xF0, 0x00, 0x00));
	}
	circle(img, _center, 4, Scalar(0x00, 0x00, 0xF0));
	rectangle(img, _squre, Scalar(0x00, 0xF0, 0xF0));
	
	return true;
}
