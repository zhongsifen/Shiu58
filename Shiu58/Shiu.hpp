//
//  Shiu.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 20/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Shiu_hpp
#define Shiu_hpp

#include "Shiu58.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class Shiu {
	cv::Mat _mask;
	
	std::vector<cv::Point> _contour;
	std::vector<int> _hull;
	std::vector<cv::Vec4i> _defect;
	double _area;
	cv::Point _center;

	cv::Rect _squre;
	
	double _red, _blu, _grn;
	double _hue, _sat, _val;

public:
	void setContour(std::vector<cv::Point>& contour);
	void setRect(cv::Rect& rect);
	
	void show(cv::Mat& img);
	
};

#endif /* Shiu_hpp */
