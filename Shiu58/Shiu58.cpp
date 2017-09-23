//
//  Shiu58.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuProc.hpp"
#include "Shiu.hpp"
#include "ShiuCc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

bool
Shiu58::process(cv::Mat& f) {
	_f = f;
	
	pyrDown(_f, _f);
	pyrDown(_f, _f);
	
	Mat bgr[3], r, g, b;
	split(_f, bgr);
	bgr[0].convertTo(b, CV_32F);
	bgr[1].convertTo(g, CV_32F);
	bgr[2].convertTo(r, CV_32F);
	
	Mat mask;
	Mat mat1;
	compare(r, 40.0F, mask, CMP_GT);
	compare(g, r*0.85F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(b, r*0.80F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare((g-b), (r-b)*0.750F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	
	Mat morph = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(mask, mask, MORPH_OPEN,  morph);
	morphologyEx(mask, mask, MORPH_CLOSE, morph);
	blur(mask, mask, Size(3, 3));

//	CC_STAT_LEFT   = 0, //!< The leftmost (x) coordinate which is the inclusive start of the bounding
//	//!< box in the horizontal direction.
//	CC_STAT_TOP    = 1, //!< The topmost (y) coordinate which is the inclusive start of the bounding
//	//!< box in the vertical direction.
//	CC_STAT_WIDTH  = 2, //!< The horizontal size of the bounding box
//	CC_STAT_HEIGHT = 3, //!< The vertical size of the bounding box

	Mat label;
	Mat stats;
	Mat centroids;
	int n = connectedComponentsWithStats(mask, label, stats, centroids);
	std::vector<Rect> rois;
	_rois.reserve(n);
	for (int i=1; i<n; ++i) {
		int area = stats.at<int>(i, CC_STAT_AREA);
		if (area < 16*16) {
			compare(label, i, mat1, CMP_EQ);
			label.setTo(0, mat1);
		}
		else {
			_rois.push_back(*new Rect(Point(stats.at<int>(i, CC_STAT_TOP), stats.at<int>(i, CC_STAT_LEFT)), Size(stats.at<int>(i, CC_STAT_WIDTH), stats.at<int>(i, CC_STAT_HEIGHT))));
			
		}
	}
	compare(label, 0, mask, CMP_GT);
	_label = label;
	_n = n;

	Mat w;
	_f.copyTo(w, mask);

	std::vector<std::vector<Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(label, contours, hierarchy, RETR_FLOODFILL, CHAIN_APPROX_SIMPLE);
	int size = (int)contours.size();
	std::vector<Shiu> shius(size);
	
	for (int i=0; i<size; ++i) {
		shius[i].setContour(contours[i]);
		shius[i].show(w);
	}
	imshow("fingers", w);
	
	
	return true;
}

void
Shiu58::show(cv::Mat& f, cv::Mat& w) {
	std::vector<Vec3b> colors(_n);
	colors[0] = Vec3b(0, 0, 0);
	for(int i = 1; i < _n; ++i) {
		colors[i] = Vec3b( (rand()&0xFF), (rand()&0xFF), (rand()&0xFF) );
	}
	w.create(_label.size(), CV_8UC3);
	for(int r = 0; r < w.rows; ++r){
		for(int c = 0; c < w.cols; ++c){
			int label = _label.at<int>(r, c);
			w.at<Vec3b>(r, c) = colors[label];
		}
	}
}


