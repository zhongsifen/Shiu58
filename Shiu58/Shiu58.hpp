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
#include "Shiu.hpp"

class Shiu58 {
	const int _area_thre = 16*16;
	cv::Mat _f;

	std::vector<Shiu> _shius;
	
public:
	void setup();
	void run(cv::Mat& f);
	void show(cv::Mat& f, cv::Mat& w);
};

#endif /* ShiuProc_hpp */
