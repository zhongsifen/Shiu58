//
//  Shiu.hpp
//  Shiu
//
//  Created by SIFEN ZHONG on 13/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Shiu_hpp
#define Shiu_hpp

#include <opencv2/core.hpp>
#include "cascadedetect.hpp"

class Shiu {
	int status;
	cv::CascadeClassifier cf;
	cv::Rect roi;
	cv::Rect box;
public:
	Shiu() { this->status = 0; }
	Shiu(std::string filename);
	
	bool detect(cv::Mat& g, cv::Rect& box);
	bool detect_list(cv::Mat& g, std::vector<cv::Rect>& list);
	bool detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& box);
	
	bool detect(cv::Mat& g, cv::Rect& box, int& level, double& weight);	
};

#endif /* Shiu_hpp */
