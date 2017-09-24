//
//  Shiu.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 20/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Shiu_hpp
#define Shiu_hpp

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class Shiu {
	cv::Rect _box;
	cv::Mat _mask;
	
	std::vector<cv::Point> _contour;
	std::vector<int> _hull;
	std::vector<cv::Vec4i> _defect;
	double _area;
	cv::Point _center;

public:
	void set(cv::Mat& label, cv::Rect& box);
	void show(cv::Mat& img);
};

#endif /* Shiu_hpp */
