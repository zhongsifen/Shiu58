//
//  ShiuDetect.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 30/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuDetect_hpp
#define ShiuDetect_hpp

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "cascadedetect.hpp"

const std::string RES("/Users/zhongsifen/Work/Shiu58/res/");
const std::string palm("haarcascades/palm.xml");
const std::string palm_closed("haarcascades/closed_frontal_palm.xml");
const std::string face("haarcascades/haarcascade_frontalface_alt2.xml");
const std::string gest("haarcascades/aGest.xml");
const std::string fist("haarcascades/fist.xml");

class ShiuDetect {
	int _status;
	cv::CascadeClassifier _cf;
	
public:
	ShiuDetect() { _status = 0; }
	bool load(std::string filename = RES+palm);
	bool detect(cv::Mat& g, std::vector<cv::Rect>& box_list, std::vector<int>& level_list, std::vector<double>& weight_list);
	bool detect(cv::Mat& g, cv::Rect& box, int& level, double& weight);
	bool show(cv::Mat& img, cv::Rect& box);
	bool show(cv::Mat& img, std::vector<cv::Rect>& box_list);
};

#endif /* ShiuDetect_hpp */
