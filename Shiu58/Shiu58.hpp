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

const std::string RES("/Users/zhongsifen/Work/Shiu58/res/");
const std::string palm("haarcascades/palm.xml");
const std::string palm_closed("haarcascades/closed_frontal_palm.xml");
const std::string face("haarcascades/haarcascade_frontalface_alt2.xml");
const std::string gest("haarcascades/aGest.xml");
const std::string fist("haarcascades/fist.xml");

class Shiu58 {
	int _status;
	cv::CascadeClassifier _cf;
	
	cv::Mat _f;
	cv::Mat _g;
	cv::Mat _h;

	int _level;
	double _weight;
	cv::Rect _roi;
	cv::Rect _box;

	cv::Mat _f_reset;
	cv::Rect _roi_reset;
	
public:
	Shiu58() { _status = 0; }
	bool load(std::string filename = RES+fist);
	bool setup(cv::Mat& frame);
	bool run(cv::Mat& frame);
	bool show(cv::Mat& frame);

	bool cvt(cv::Mat& f, cv::Mat& g, cv::Mat& h);
	bool detect(cv::Mat& g, cv::Rect& box, int& level, double& weight);
//	bool show(cv::Mat& w, cv::Rect& roi, cv::Rect& box);
};

#endif /* Shiu58_hpp */
