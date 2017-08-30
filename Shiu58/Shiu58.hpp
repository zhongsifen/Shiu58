//
//  Shiu58.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Shiu58_hpp
#define Shiu58_hpp

#include "ShiuDetect.hpp"
#include "ShiuBgs.hpp"
#include <opencv2/core.hpp>

class Shiu58 {
	int _status;

	ShiuDetect _detect;
	ShiuBgs _bgs;
	
	cv::Mat _f;
	cv::Mat _g;
	cv::Mat _h;
	cv::Mat _mask;
	cv::Mat _fgimg;
	cv::Mat _bgimg;

	int _level;
	double _weight;
	cv::Rect _roi;
	cv::Rect _box;

	cv::Mat _f_reset;
	cv::Rect _roi_reset;
	
public:
	Shiu58() { _status = 0; }
	bool setup(cv::Mat& frame);
	bool run(cv::Mat& frame);
	bool show(cv::Mat& frame);

	bool cvt(cv::Mat& f, cv::Mat& g, cv::Mat& h, cv::Mat& mask);
	bool show_bgs();
	
};

#endif /* Shiu58_hpp */
