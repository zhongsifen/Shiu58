//
//  Shiu58.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

float
ShiuX::dist(Point p0, Point p1) {
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrtf(dx*dx + dy*dy);
}

void
ShiuX::showPoint(cv::Mat& img, cv::Point& point, int radius, const cv::Scalar& color) {
	circle(img, point, radius, color);
}
					  
void
ShiuX::showPointLine(cv::Mat& show, std::vector<cv::Point>& point_list, int radius, const cv::Scalar& colorPoint, const cv::Scalar& colorLine) {
	for (int i=0; i<point_list.size(); ++i) {
		circle(show, point_list[i], radius, colorPoint);
	}
	for (int i=1; i<point_list.size(); ++i) {
		line(show, point_list[i-1], point_list[i], colorLine);
	}
}

static void refineSegments(const Mat& img, Mat& mask, Mat& dst)
{
	int niters = 3;
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	Mat temp;
	
	dilate(mask, temp, Mat(), Point(-1,-1), niters);
	erode(temp, temp, Mat(), Point(-1,-1), niters*2);
	dilate(temp, temp, Mat(), Point(-1,-1), niters);
	
	findContours( temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE );
	
	dst = Mat::zeros(img.size(), CV_8UC3);
	
	if( contours.size() == 0 )
		return;
	
	// iterate through all the top-level contours,
	// draw each connected component with its own random color
	int idx = 0, largestComp = 0;
	double maxArea = 0;
	
	for( ; idx >= 0; idx = hierarchy[idx][0] )
	{
		const vector<Point>& c = contours[idx];
		double area = fabs(contourArea(Mat(c)));
		if( area > maxArea )
		{
			maxArea = area;
			largestComp = idx;
		}
	}
	Scalar color( 0, 0, 255 );
	drawContours( dst, contours, largestComp, color); // FILLED, LINE_8, hierarchy );
}

bool
Shiu58::setup(Mat& frame) {
	
	return true;
}

bool
Shiu58::run(Mat& frame) {
	_f = frame;
//	cvt(_f, _g, _h);
	_bgs.apply(_f, _mask, _fgimg, _bgimg);
//	refineSegments(_fgimg, _mask, _fgimg);
	
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

bool
Shiu58::show(Mat& frame) {
	rectangle(frame, _box, Scalar(0xFF, 0x00, 0xFF));
//	rectangle(frame, _roi, Scalar(0x00, 0x00, 0xFF));
	
	return true;
}

bool
Shiu58::show_bgs() {
	imshow("ShiuBgs", _fgimg);
	
	return true;
}
