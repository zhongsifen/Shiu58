//
//  ShiuCc.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 21/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuCc_hpp
#define ShiuCc_hpp

#include "Shiu58.hpp"

namespace ShuiCc {
	bool cc(cv::Mat& bw, cv::Mat& labelImage, cv::Mat& stats, cv::Mat& centroids, int& nLabels);
	bool clean(cv::Mat& bw, cv::Mat& labelImage, cv::Mat& stats, cv::Mat& centroids, int& nLabels);
	
	void show(cv::Mat& labelImage, int nLabels, cv::Mat& dst);
}

#endif /* ShiuCc_hpp */
