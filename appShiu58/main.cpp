//
//  main.cpp
//  appShiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"
#include "ShiuBgs.hpp"
#include "ShiuSkin.hpp"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

const std::string _data("/Users/zhongsifen/Work/Shiu58/data/");
const std::string _name("20170830172101.mp4");
const std::string _path(_data + _name);

int main_file(int argc, const char * argv[]) {
	Mat f = imread(_data + "frame.png");
	Mat mask;
	std::vector<Point> contour;
	
	ShiuSkin::color(f, mask);
	ShiuSkin::density(f, mask);
	ShiuSkin::geometry(f, mask);
	ShiuSkin::finger(f, mask, contour);
	Mat w(f.rows, f.cols, f.type());
	w = Scalar(0xFF, 0xFF, 0xFF);
	f.copyTo(w, mask);
	imshow("frame", w);
	waitKey();
	
	return 0;
}

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';

	Shiu58 shiu;
	
	Mat f, g, h, w, z, mask, notmask;
	std::vector<Point> contour;
	std::vector<Mat> hsl;
	
//	Rect box;
//	int level=0;
//	double weight=0;
	const int waittime = 1;
	VideoCapture cap;
	cap.open(_path);
//	cap.open(0);
	if (!cap.isOpened()) return -1;
	ret = cap.read(f);		if (!ret) return -1;

	VideoWriter rec;
	rec.open(_data + "rec264.mov", VideoWriter::fourcc('X','2','6','4'), 25.0, Size(f.cols, f.rows));	if (!rec.isOpened()) return  -1;
	do {
		ret = cap.read(f);		if (!ret) break;
		w = f.clone();
		z = f.clone();

		ShiuSkin::color(f, mask);
		ShiuSkin::density(f, mask);
		ShiuSkin::geometry(f, mask);
		ShiuSkin::finger(f, mask, contour);
		bitwise_not(mask, notmask);
		w = Scalar(0xFF, 0xFF, 0xFF);
		z = Scalar(0x00);
		f.copyTo(w, mask);
		f.copyTo(z, notmask);
//		shiu.run(f);
//		shiu.show_bgs();
		rec.write(w);
		imshow("mask", w);
//		imshow("not", z);
		key = waitKey(waittime);		if (key == 27) break;
//		if (key == 's') imwrite(_data + "frame.png", f);
	} while (1);

	rec.release();
	cap.release();
	
	std::cout << "Hello, World!\n";
	return 0;
}
