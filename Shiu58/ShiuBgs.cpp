//
//  ShiuBgs.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 26/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuBgs.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
using namespace cv;

namespace ShiuBgs {
	Ptr<BackgroundSubtractor> bg_model =

	createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();
//	createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>();
	
	bool bg(Mat& img, Mat& fgmask, Mat& fgimg, Mat& bgimg) {
		bg_model->apply(img, fgmask, 0.5);
		GaussianBlur(fgmask, fgmask, Size(5, 5), 3.5);
		threshold(fgmask, fgmask, 10, 255, THRESH_BINARY);
		fgimg = Scalar::all(0);
		img.copyTo(fgimg, fgmask);
		bg_model->getBackgroundImage(bgimg);
		
		return true;
	}
}
