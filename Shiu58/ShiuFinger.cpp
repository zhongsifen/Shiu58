//
//  ShiuFinger.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 8/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuFinger.hpp"
using namespace cv;

float _distance(Point p0, Point p1) {
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrtf(dx*dx + dy*dy);
}

bool
ShiuFinger::init(std::vector<Point>& contour) {
	_contour = contour;
	convexHull(_contour, _hull);
	convexityDefects(_contour, _hull, _defect);
	
	return true;
}

bool
ShiuFinger::show(cv::Mat& img) {
	if (_defect.size() < 1) return false;
	
	for (int i=0; i<_defect.size(); ++i) {
		Point p0 = _contour[_defect[i][0]];
		Point p1 = _contour[_defect[i][1]];
		float width = _distance(p0, p1);
		float depth = (float)_defect[i][2];
		if (depth > width*2) {
			circle(img, _contour[_defect[i][0]], 3, Scalar(0x00, 0x00, 0xF0));
			circle(img, _contour[_defect[i][1]], 3, Scalar(0x00, 0x00, 0xF0));
			circle(img, _contour[_defect[i][2]], 3, Scalar(0xF0, 0xF0, 0x00));
			line(img, _contour[_defect[i][0]], _contour[_defect[i][2]], Scalar(0x00, 0xF0, 0x00));
			line(img, _contour[_defect[i][1]], _contour[_defect[i][2]], Scalar(0x00, 0xF0, 0x00));
		}
	}
	
	return true;
}
