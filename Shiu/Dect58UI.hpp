// Dect58.hpp

#ifndef _Dect58_h_
#define _Dect58_h_

#include "_opencv2.hpp"	
#include <iostream>
#include <fstream>

namespace Dect58UI {

	const static std::string RES("/Users/zhongsifen/Work/Dect58/res/");
	const static std::string HAND("/Users/zhongsifen/Work/data/Hand/B/");
	
	const cv::Scalar COLOR_0000FF = cv::Scalar(0x00, 0x00, 0xFF);
	const cv::Scalar COLOR_00FF00 = cv::Scalar(0x00, 0xFF, 0x00);
	const cv::Scalar COLOR_FF0000 = cv::Scalar(0xFF, 0x00, 0x00);


	bool read_mat(std::ifstream& s, cv::Mat& a);
	bool write_mat(std::ofstream& s, cv::Mat& a);
	bool show_rect(cv::Mat& im, cv::Rect& rect, cv::Scalar color);
	bool show_point(cv::Mat& im, cv::Point& pt, cv::Scalar color);
	bool show_points(cv::Mat& im, std::vector<cv::Point>& points, cv::Scalar color);
	bool show_points(cv::Mat& im, cv::Mat& points, cv::Scalar color);
	bool show_shape(cv::Mat& im, cv::Mat& shape, int health=10);
	
};

#endif
