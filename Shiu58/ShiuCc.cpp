//
//  ShiuCc.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 21/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuCc.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

namespace ShuiCc {
	bool cc(Mat& bw, Mat& labelImage, Mat& stats, Mat& centroids, int& nLabels) {
		labelImage.create(bw.size(), CV_32S);
		nLabels = connectedComponentsWithStats(bw, labelImage, stats, centroids);
		
		return true;
	}
	
	bool clean(cv::Mat& bw, cv::Mat& labelImage, int& nLabels) {
		std::vector<int> area(nLabels);
		
		for (int i=0; i<nLabels; ++i) {
			
		}
		
		return true;
	}
	
	void show(Mat& labelImage, int nLabels, Mat& dst) {
		std::vector<Vec3b> colors(nLabels);
		colors[0] = Vec3b(0, 0, 0);//background
		for(int label = 1; label < nLabels; ++label){
			colors[label] = Vec3b( (rand()&0xFF), (rand()&0xFF), (rand()&0xFF) );
		}
		dst.create(labelImage.size(), CV_8UC3);
		for(int r = 0; r < dst.rows; ++r){
			for(int c = 0; c < dst.cols; ++c){
				int label = labelImage.at<int>(r, c);
				Vec3b &pixel = dst.at<Vec3b>(r, c);
				pixel = colors[label];
			}
		}
	}

}

