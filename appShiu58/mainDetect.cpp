//
//  main.cpp
//  appShiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"
#include "ShiuDetect.hpp"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

const std::string _data("/Users/zhongsifen/Work/Shiu58/data/");
const std::string _name("20170915140730.mp4");
const std::string _path(_data + _name);

//#define WITH_FILE

int mainDetect(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';

	Mat f, g, h, w, z, mask, notmask;
	std::vector<Point> contour;
	std::vector<int> hull;
	
	std::vector<Mat> hsl;
	
	const int waittime = 1;
	VideoCapture cap;
#if defined(WITH_FILE)
	cap.open(_path);
#else
	cap.open(0);
#endif
	if (!cap.isOpened()) return -1;
#if defined(WITH_REC)
	VideoWriter rec;
	rec.open(_data + "rec264.avi", VideoWriter::fourcc('X','2','6','4'), 25.0, Size(f.cols, f.rows));	if (!rec.isOpened()) return  -1;
#endif
	
	std::vector<Rect> box_list;
	std::vector<int> level_list;
	std::vector<double> weight_list;
	ShiuDetect dect;
	dect.load();
	
	do {
		ret = cap.read(f);		if (!ret) break;
		
		medianBlur(f, f, 5);
		
		Mat bgr[3], r, g, b;
		split(f, bgr);
//		bgr[0].convertTo(b, CV_32F);
//		bgr[1].convertTo(g, CV_32F);
//		bgr[2].convertTo(r, CV_32F);
		r = bgr[2];

		w = f.clone();
//		w = Scalar(0xFF, 0xFF, 0xFF);
		
		dect.detect(r, box_list, level_list, weight_list); 
		
#if defined(WITH_REC)
		rec.write(w);
#endif
		imshow("detect", w);
		key = waitKey(waittime);		if (key == 27) break;
		if (key == 's') {
			imwrite("frame_w.png", w);
			imwrite(_data + "frame_z.png", z);
		}
	} while (1);

#if defined(WITH_REC)
	rec.release();
#endif
	cap.release();
	
	std::cout << "Hello, World!\n";
	return 0;
}
