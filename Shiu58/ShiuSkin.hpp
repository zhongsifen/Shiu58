//
//  ShiuSkin.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuSkin_hpp
#define ShiuSkin_hpp

#include <opencv2/core.hpp>

namespace ShiuSkin {
	const int erode1 = 5;
	const int dilate1 = 3;
	const int erode2 = 5;
	const int dilate2 = 3;

	bool color(cv::Mat& f, cv::Mat& mask);
	bool density(cv::Mat& img, cv::Mat& imgFilter);
	bool geometry(cv::Mat& img, cv::Mat& imgFilter);
	
	bool finger(cv::Mat& f, cv::Mat& mask, std::vector<cv::Point>& contour);
}

#endif /* ShiuSkin_hpp */
