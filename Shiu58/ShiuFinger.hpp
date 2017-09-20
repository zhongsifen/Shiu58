//
//  ShiuFinger.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 8/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuFinger_hpp
#define ShiuFinger_hpp

#include "Shiu58.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class ShiuFinger {
	std::vector<cv::Point> _contour;
	std::vector<int> _hull;
	std::vector<cv::Vec4i> _defect;
	double _area;
	double _red, _blu, _grn;
	double _hue, _sat, _val;
public:
	bool init(std::vector<cv::Point>& contour);
	bool show(cv::Mat& img);
	
};

#endif /* ShiuFinger_hpp */
