//
//  Shiu.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 20/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu.hpp"
using namespace cv;

void
Shiu::set(cv::Mat& label, cv::Rect& box) {
	_box = box;
	Mat h = label(_box);
	std::vector<std::vector<Point>> contours;
	findContours(h, contours, RETR_FLOODFILL, CHAIN_APPROX_SIMPLE, _box.tl());
	int size = (int)contours.size(); if (size < 1) return;
	int t=0;
	double area = contourArea(contours[t]);
	for (int k=1; k<contours.size(); ++k) {
		if (area < contourArea(contours[k])) {
			t = k;
			area = contourArea(contours[t]);
		}
	}
	_contour = contours[t];
	convexHull(_contour, _hull);
	convexityDefects(_contour, _hull, _defect);	
	Moments mm = moments(_contour);
	_area = mm.m00;
	_center = Point((int)round(mm.m10/mm.m00), (int)round(mm.m01/mm.m00));
}

void
Shiu::show(cv::Mat& img) {

	Scalar colorBox(0xF0, 0xF0, 0xF0);
	Scalar colorHull(0x00, 0x00, 0xF0);
	Scalar colorDefect(0x00, 0x00, 0xF0);

	rectangle(img, _box, colorBox);

	for (int i=0; i<_hull.size(); ++i) {
		
	}
	for (int i=0; i<_defect.size(); ++i) {
		Point p0 = _contour[_defect[i][0]];
		Point p1 = _contour[_defect[i][1]];
		double width = norm(p0 - p1);
		double depth = _defect[i][2];
		if (depth > width*2) {
			circle(img, _contour[_defect[i][0]], 3, colorDefect);
			circle(img, _contour[_defect[i][1]], 3, colorDefect);
			circle(img, _contour[_defect[i][2]], 3, colorDefect);
			line(img, _contour[_defect[i][0]], _contour[_defect[i][2]], colorDefect);
			line(img, _contour[_defect[i][1]], _contour[_defect[i][2]], colorDefect);
		}
	}
	
}
