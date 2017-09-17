//
//  ShiuPalm.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 6/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuPalm_hpp
#define ShiuPalm_hpp

#include "Shiu58.hpp"
#include "ShiuFinger.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class ShiuPalm {
	std::vector<cv::Point> _contour;
	double _area;
	cv::Point _center;
	cv::Rect _squre;
	double _red, _blu, _grn;
	double _hue, _sat, _val;
	
	ShiuFinger _finger;
public:
	bool init(std::vector<cv::Point>& contour);
	double cert();
	bool show(cv::Mat& img);
	
};

#endif /* ShiuPalm_hpp */
