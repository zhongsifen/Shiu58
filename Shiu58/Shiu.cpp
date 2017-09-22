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
Shiu::setContour(std::vector<cv::Point>& contour) {
	_contour = contour;
	convexHull(_contour, _hull);
	convexityDefects(_contour, _hull, _defect);

	Moments mm = moments(_contour);
	_area = mm.m00;
	_center = Point((int)round(mm.m10/mm.m00), (int)round(mm.m01/mm.m00));
}

void
Shiu::setRect(cv::Rect& rect) {
	
}

float _dist(Point p0, Point p1) {
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrtf(dx*dx + dy*dy);
}

void
Shiu::show(cv::Mat& img) {

	Scalar colorFinger(0x00, 0x00, 0xF0);
	for (int i=0; i<_defect.size(); ++i) {
		Point p0 = _contour[_defect[i][0]];
		Point p1 = _contour[_defect[i][1]];
		float width = _dist(p0, p1);
		float depth = (float)_defect[i][2];
		if (depth > width*2) {
			circle(img, _contour[_defect[i][0]], 3, colorFinger);
			circle(img, _contour[_defect[i][1]], 3, colorFinger);
			circle(img, _contour[_defect[i][2]], 3, colorFinger);
			line(img, _contour[_defect[i][0]], _contour[_defect[i][2]], colorFinger);
			line(img, _contour[_defect[i][1]], _contour[_defect[i][2]], colorFinger);
		}
	}
	
}
