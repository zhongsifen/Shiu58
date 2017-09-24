//
//  Shiu58.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

void
Shiu58::setup() {
	
}

void
Shiu58::run(cv::Mat& f) {
	_f = f;

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
	
	_shius.reserve(n);
	_shius.clear();
	for (int i=1; i<n; ++i) {
		int area = stats.at<int>(i, CC_STAT_AREA);
		if (area < _area_thre) {
			compare(label, i, mat1, CMP_EQ);
			label.setTo(0, mat1);
		}
		else {
			Shiu* shiu = new Shiu;
			shiu->set(label, *new Rect(Point(stats.at<int>(i, CC_STAT_LEFT), stats.at<int>(i, CC_STAT_TOP)), Size(stats.at<int>(i, CC_STAT_WIDTH), stats.at<int>(i, CC_STAT_HEIGHT))));
			_shius.push_back(*shiu);
		}
	}
}

void
Shiu58::show(cv::Mat& f, cv::Mat& w) {
	w = _f.clone();

	for (int i=0; i<_shius.size(); ++i) {
		_shius[i].show(w);
	}
}
