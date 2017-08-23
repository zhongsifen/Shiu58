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
#include "cascadedetect.hpp"

const std::string RES("../res/");
const std::string palm("haarcascades/palm.xml");
class Shiu58 {
	int status;
	cv::CascadeClassifier cf;
	
	cv::Mat f;
	cv::Mat g;
	cv::Mat h;
	
	float weight;
	cv::Rect roi;
	cv::Rect box;

public:
	Shiu58() { status = 0; setup(); }
	bool setup(std::string filename = RES+palm);
	bool run(cv::Mat& f);

	bool detect(cv::Mat& g, cv::Rect& box);
	bool detect_list(cv::Mat& g, std::vector<cv::Rect>& list);
	bool detect_roi(cv::Mat& g, cv::Rect& roi, cv::Rect& box);
	
	bool detect(cv::Mat& g, cv::Rect& box, int& level, double& weight);

	void show();
};

#endif /* Shiu58_hpp */
