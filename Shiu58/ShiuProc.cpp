//
//  ShiuProc.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuProc.hpp"
#include "ShiuPalm.hpp"
#include "ShiuFinger.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

bool
ShiuProc::color(Mat& f, Mat& mask) {
	mask.create(f.rows, f.cols, CV_8UC1);
	mask = Scalar(0xFF);
	
	medianBlur(f, f, 11);
	
	Mat bgr[3], r, g, b;
	split(f, bgr);
	bgr[0].convertTo(b, CV_32F);
	bgr[1].convertTo(g, CV_32F);
	bgr[2].convertTo(r, CV_32F);
	Mat mat1, mat2;
	compare(r, 64.0F, mat1, CMP_GT); bitwise_and(mask, mat1, mask);
	compare(g, r*0.95F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(b, r*0.90F, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	
	morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
	blur(mask, mask, Size(3, 3));
	
	return true;
}

bool
ShiuProc::density(Mat& img, Mat& imgFilter)
{
	Mat sum;
	sum = Mat::zeros(img.rows, img.cols, CV_8UC1);
	uchar op;
	int erode, dilate;
	for (int i = 0; i < img.rows; i += 4) //Cycle over horizontal clusters
	{
		for (int j = 0; j < img.cols; j += 4) //Cycle over vertical clusters
		{
			for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
			{
				for (int l = 0; l < 4; l++) //Cycle vertically within cluster
				{
					if (imgFilter.at<uchar>(i + k, j + l) != 0) sum.at<uchar>(i, j)++;
				}
			}
			if (sum.at<uchar>(i, j) == 0 || i == 0 || j == 0 || i == (img.rows - 4) || j == (img.cols - 4)) op = 0;
			else if (sum.at<uchar>(i, j) > 0 &&  sum.at<uchar>(i, j) < 16) op = 128;
			else op = 255;
			for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
			{
				for (int l = 0; l < 4; l++) //Cycle vertically within cluster
				{
					imgFilter.at<uchar>(i + k, j + l) = op;
				}
			}
		}
	}
	for (int i = 4; i < (img.rows - 4); i += 4) //Cycle over horizontal clusters
	{
		for (int j = 4; j < (img.cols -4); j += 4) //Cycle over vertical clusters
		{
			erode = 0;
			if (imgFilter.at<uchar>(i, j) == 255)
			{
				for (int k = -4; k < 5; k += 4)
				{
					for (int l = -4; l < 5; l += 4)
					{
						if (imgFilter.at<uchar>(i + k, j + l) == 255) erode++;
					}
				}
				if (erode < erode1)
				{
					for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
					{
						for (int l = 0; l < 4; l++) //Cycle vertically within cluster
						{
							imgFilter.at<uchar>(i + k, j + l) = 0;
						}
					}
				}
			}
		}
	}
	for (int i = 4; i < (img.rows - 4); i += 4) //Cycle over horizontal clusters
	{
		for (int j = 4; j < (img.cols - 4); j += 4) //Cycle over vertical clusters
		{
			dilate = 0;
			if (imgFilter.at<uchar>(i, j) < 255)
			{
				for (int k = -4; k < 5; k += 4)
				{
					for (int l = -4; l < 5; l += 4)
					{
						if (imgFilter.at<uchar>(i + k, j + l) == 255) dilate++;
					}
				}
				if (dilate > dilate1)
				{
					for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
					{
						for (int l = 0; l < 4; l++) //Cycle vertically within cluster
						{
							imgFilter.at<uchar>(i + k, j + l) = 255;
						}
					}
				}
			}
			for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
			{
				for (int l = 0; l < 4; l++) //Cycle vertically within cluster
				{
					if (imgFilter.at<uchar>(i + k, j + l) != 255) imgFilter.at<uchar>(i + k, j + l) = 0;
				}
			}
		}
	}
	
	return true;
}

bool
ShiuProc::geometry(Mat& img, Mat& imgFilter) {
	int erode, dilate;
	for (int i = 4; i < (img.rows - 4); i+=4) //Cycle over horizontal clusters
	{
		for (int j = 4; j < (img.cols - 4); j+=4) //Cycle over vertical clusters
		{
			erode = 0;
			if (imgFilter.at<uchar>(i, j) == 255)
			{
				for (int k = -4; k < 5; k += 4)
				{
					for (int l = -4; l < 5; l += 4)
					{
						if (imgFilter.at<uchar>(i + k, j + l) == 255) erode++;
					}
				}
				if (erode < erode2)
				{
					for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
					{
						for (int l = 0; l < 4; l++) //Cycle vertically within cluster
						{
							imgFilter.at<uchar>(i + k, j + l) = 0;
						}
					}
				}
			}
		}
	}
	for (int i = 4; i < (img.rows - 4); i+=4) //Cycle over horizontal clusters
	{
		for (int j = 4; j < (img.cols - 4); j+=4) //Cycle over vertical clusters
		{
			dilate = 0;
			if (imgFilter.at<uchar>(i, j) < 255)
			{
				for (int k = -4; k < 5; k += 4)
				{
					for (int l = -4; l < 5; l += 4)
					{
						if (imgFilter.at<uchar>(i + k, j + l) == 255) dilate++;
					}
				}
				if (dilate > dilate2)
				{
					for (int k = 0; k < 4; k++) //Cycle horizontally within cluster
					{
						for (int l = 0; l < 4; l++) //Cycle vertically within cluster
						{
							imgFilter.at<uchar>(i + k, j + l) = 255;
						}
					}
				}
			}
		}
	}
	
	return true;
}

bool
ShiuProc::finger(Mat& f, Mat& mask, std::vector<Point>& contour, std::vector<int>& hull) {
	std::vector<std::vector<Point>> contour_list;
	std::vector<Vec4i> hierarchy;

	findContours(mask, contour_list, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	int size =	(int)contour_list.size(); if (size < 1) return false;
	std::vector<ShiuPalm> palm_list(size);
	for (int i=0; i<size; ++i) {
		palm_list[i].init(contour_list[i]);
		palm_list[i].show(f);
	}
//	std::vector<ShiuFinger> finger_list(size);
//	for (int i=0; i<finger_list.size(); ++i) {
//		finger_list[i].init(contour_list[i]);
//		finger_list[i].show(f);
//	}

//	std::vector<double> area_list(size);
//	std::vector<std::vector<int>> hull_list(size);
//	std::vector<std::vector<Vec4i>> defect_list(size);
//	int idx = -1;
//	double area = 0;
//	for (int i=0; i<size; ++i) {
//		area_list[i] = contourArea(contour_list[i]);
//		convexHull(contour_list[i], hull_list[i]);
//		if (hull_list[i].size() < 3) continue;
//		convexityDefects(contour_list[i], hull_list[i], defect_list[i]);
//		
//		if (area_list[i] > area) idx = i;
//	}
//	
//	contour = contour_list[idx];
//	hull = hull_list[idx];
	
	return true;
}

