//
//  Shiu58.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Shiu58_hpp
#define Shiu58_hpp

#include <opencv2/core.hpp>

class Shiu58 {
	cv::Mat _f;
	cv::Mat _label;
	int _n;
	cv::Mat _mask;
	std::vector<cv::Rect> _rois;
	
public:
	bool process(cv::Mat& f);
	void show(cv::Mat& f, cv::Mat& w);
};

#endif /* ShiuProc_hpp */
