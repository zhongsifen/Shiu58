//
//  mainSkin.cpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 20/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

const std::string _data("/Users/zhongsifen/Work/Shiu58/data/");
//const std::string _name("20170915140730.mp4");
const std::string _name("20170915140822.mp4");
//const std::string _name("20170915140930.mp4");
const std::string _path(_data + _name);

#define WITH_FILE
//#define WITH_REC

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	Mat f, w, mask;
	VideoCapture cap;
#if defined(WITH_FILE)
	cap.open(_path);
#else
	cap.open(0);
#endif
	if (!cap.isOpened()) return -1;
	ret = cap.read(f);		if (!ret) return -1;
#if defined(WITH_REC)
	VideoWriter rec;
	rec.open(_data + "rec264.avi", VideoWriter::fourcc('X','2','6','4'), 25.0, Size(f.cols, f.rows));	if (!rec.isOpened()) return  -1;
#endif

	Shiu58 shiu;
	shiu.setup();

	while (true) {
		ret = cap.read(f);		if (!ret) break;
		w = f.clone();
		shiu.run(f);
		shiu.show(f, w);
		imshow("labal", w);
#if defined(WITH_REC)
		rec.write(w);
#endif
		key = waitKey(1);		if (key == 27) break;
	}
	
#if defined(WITH_REC)
	rec.release();
#endif
	cap.release();
	
	std::cout << "Hello, World!\n";
	return 0;
}
