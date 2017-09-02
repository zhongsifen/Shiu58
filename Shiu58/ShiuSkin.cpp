//
//  ShiuSkin.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuSkin.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

bool
ShiuSkin::detect(Mat& f, Mat& mask) {
	mask.create(f.rows, f.cols, CV_8UC1);
	mask = Scalar(0xFF);
	Mat bgr[3], r, g, b;
	split(f, bgr);
	bgr[0].convertTo(b, CV_32F);
	bgr[1].convertTo(g, CV_32F);
	bgr[2].convertTo(r, CV_32F);
	Mat mat1, mat2;
	compare(r, 48.0, mat1, CMP_GT); bitwise_and(mask, mat1, mask);
	compare(b, r*0.8750, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(g, r*0.9375, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	
//	divide(b, mat1, b);
//	divide(g, mat1, g);
//	divide(r, mat1, r);
//	b.convertTo(bgr[0], CV_8U, 200.0);
//	g.convertTo(bgr[1], CV_8U, 200.0);
//	r.convertTo(bgr[2], CV_8U, 200.0);
//	merge(bgr, 3, f);
//	subtract(r, g, mat1); compare(mat1, Scalar( 6), mat1, CMP_GT); 	bitwise_and(mask, mat1, mask);
//	subtract(r, b, mat2); compare(mat2, Scalar(18), mat2, CMP_GT); 	bitwise_and(mask, mat2, mask);

//	bitwise_and(bltr, gltr, mask);
//	inRange(bgr[2], Scalar(95), Scalar(250), rirg);
//	bitwise_and(mask, rirg, mask);
	
	return true;
}
