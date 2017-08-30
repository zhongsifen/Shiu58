//
//  ShiuBgs.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 26/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuBgs.hpp"
#include <opencv2/imgproc.hpp>
using namespace cv;

bool ShiuBgs::apply(Mat& img, Mat& mask, Mat& fgimg, Mat& bgimg) {
	_mog2->apply(img, mask, 0.5);
	_mog2->getBackgroundImage(bgimg);

	GaussianBlur(mask, mask, Size(5, 5), 3.5);
	threshold(mask, mask, 10, 255, THRESH_BINARY);
	erode(mask, mask, Mat(), Point(-1,-1), 3);
	fgimg = Scalar::all(0);
	img.copyTo(fgimg, mask);
	
	return true;
}
