//
//  ShiuBgs.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 26/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuBgs_hpp
#define ShiuBgs_hpp

#include <opencv2/core.hpp>
#include <opencv2/video/background_segm.hpp>

class ShiuBgs {
	cv::Ptr<cv::BackgroundSubtractor> _model;
	cv::Ptr<cv::BackgroundSubtractorMOG2> _mog2;
public:
	ShiuBgs() {
		_model = cv::createBackgroundSubtractorMOG2().dynamicCast<cv::BackgroundSubtractor>();
		_mog2 = cv::createBackgroundSubtractorMOG2(1000, 16, true);
	}
	
	bool apply(cv::Mat& img, cv::Mat& mask, cv::Mat& fgimg, cv::Mat& bgimg);
};

#endif /* ShiuBgs_hpp */
