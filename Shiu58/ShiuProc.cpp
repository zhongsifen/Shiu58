//
//  ShiuProc.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "ShiuProc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

bool
ShiuProc::color(Mat& f, Mat& mask) {
	mask.create(f.rows, f.cols, CV_8UC1);
	mask = Scalar(0xFF);
	Mat bgr[3], r, g, b;
	split(f, bgr);
	bgr[0].convertTo(b, CV_32F);
	bgr[1].convertTo(g, CV_32F);
	bgr[2].convertTo(r, CV_32F);
	Mat mat1, mat2;
	compare(r, 48.0, mat1, CMP_GT); bitwise_and(mask, mat1, mask);
	compare(b, r*0.8750, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	compare(g, r*0.9375, mat1, CMP_LT); bitwise_and(mask, mat1, mask);
	
//	divide(b, mat1, b);
//	divide(g, mat1, g);
//	divide(r, mat1, r);
//	b.convertTo(bgr[0], CV_8U, 200.0);
//	g.convertTo(bgr[1], CV_8U, 200.0);
//	r.convertTo(bgr[2], CV_8U, 200.0);
//	merge(bgr, 3, f);
//	subtract(r, g, mat1); compare(mat1, Scalar( 6), mat1, CMP_GT); 	bitwise_and(mask, mat1, mask);
//	subtract(r, b, mat2); compare(mat2, Scalar(18), mat2, CMP_GT); 	bitwise_and(mask, mat2, mask);

//	bitwise_and(bltr, gltr, mask);
//	inRange(bgr[2], Scalar(95), Scalar(250), rirg);
//	bitwise_and(mask, rirg, mask);
	
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
ShiuProc::finger(Mat& f, Mat& mask, std::vector<Point>& contour) {
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	if (contours.size() < 1) return false;
	int idx = 0;
	contour = contours[idx];
	double area = contourArea(contour);
	drawContours(f, contours, 0, Scalar(0xFF, 0x00, 0xFF));
	for (int i=1; i<contours.size(); ++i) {
		double a = contourArea(contours[i]);
		if (a > area) {
			idx = i;
			contour = contours[idx];
			area = a;
		}
		drawContours(f, contours, i, Scalar(0xFF, 0x00, 0xFF));
	}
	
//	drawContours(f, contours, idx, Scalar(0xFF, 0x00, 0xFF));
	
	return true;
}

