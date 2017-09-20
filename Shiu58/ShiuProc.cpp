//
//  ShiuProc.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuProc.hpp"
#include "ShiuPalm.hpp"
#include "ShiuFinger.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

bool
ShiuProc::process(Mat& f, Mat& mask) {
	mask.create(f.rows, f.cols, CV_8UC1);
	mask = Scalar(0xFF);
	
//	medianBlur(f, f, 11);
	
	Mat bgr[3], r, g, b;
	split(f, bgr);
	bgr[0].convertTo(b, CV_32F);
	bgr[1].convertTo(g, CV_32F);
	bgr[2].convertTo(r, CV_32F);
	Mat mat1, mat2;
	Mat rb = r - b;
	Mat gb = g - b;
	compare(r, 40.0F, mat1, CMP_GT); bitwise_and(mask, mat1, mask);
	compare(g, r*0.85F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(b, r*0.80F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(gb, rb*0.750F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
//	inRange(b, g*0.75F, g*1.05F, mat1); bitwise_and(mask, mat1, mask);
	
	morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	blur(mask, mask, Size(3, 3));
	
	Mat w;
	f.copyTo(w, mask);

	std::vector<std::vector<Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	int size = (int)contours.size();
	std::vector<ShiuPalm> palms(size);
	std::vector<ShiuFinger> fingers(size);
	
	for (int i=0; i<size; ++i) {
		palms[i].init(contours[i]);
		if (palms[i].cert() < 0.5) continue;
		palms[i].show(w);
		
		fingers[i].init(contours[i]);
		fingers[i].show(w);
	}
	imshow("fingers", w);
	
	
	return true;
}

