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

	Mat label;
	Mat stats;
	Mat centroids;
	int n = connectedComponentsWithStats(mask, label, stats, centroids);
	std::vector<Rect> rois;
	_rois.reserve(n);
	_rois.clear();
	for (int i=1; i<n; ++i) {
		int area = stats.at<int>(i, CC_STAT_AREA);
		if (area < 16*16) {
			compare(label, i, mat1, CMP_EQ);
			label.setTo(0, mat1);
		}
		else {
			_rois.push_back(*new Rect(Point(stats.at<int>(i, CC_STAT_LEFT), stats.at<int>(i, CC_STAT_TOP)), Size(stats.at<int>(i, CC_STAT_WIDTH), stats.at<int>(i, CC_STAT_HEIGHT))));

		}
	}
	compare(label, 0, mask, CMP_GT);
	_label = label;

	_contours.reserve(n);
	_contours.clear();
//	std::vector<cv::Vec4i> hierarchy;
	for (int i=0; i<_rois.size(); ++i) {
		Mat h = _label(_rois[i]);
		std::vector<std::vector<Point>> contours;
		findContours(h, contours, RETR_FLOODFILL, CHAIN_APPROX_SIMPLE, _rois[i].tl());
		int size = (int)contours.size(); if (size < 1) continue;
		int t=0;
		double area = contourArea(contours[t]);
		for (int k=1; k<contours.size(); ++k) {
			if (area < contourArea(contours[k])) {
				t = k;
				area = contourArea(contours[t]);
			}
		}
		_contours.push_back(contours[t]);
	}

//	findContours(label, contours, hierarchy, RETR_FLOODFILL, CHAIN_APPROX_SIMPLE);
//	int size = (int)contours.size();
//	std::vector<Shiu> shius(size);
//
//	for (int i=0; i<size; ++i) {
//		shius[i].setContour(contours[i]);
//	}


	return true;
}

void
Shiu58::show(cv::Mat& f, cv::Mat& w) {
	w = _f.clone();
	for (int i=0; i<_rois.size(); ++i) {
		rectangle(w, _rois[i], Scalar(0x00, 0xF0, 0xF0));
	}

	for (int i=0; i<_contours.size(); ++i) {
		std::vector<Point> p = _contours[i];
		for (int k=0; k<p.size(); ++k) {
			circle(w, p[k], 2, Scalar(0x00, 0x00, 0xF0));
		}
	}
}
