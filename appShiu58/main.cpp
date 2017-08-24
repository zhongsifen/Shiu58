//
//  main.cpp
//  appShiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Shiu58.hpp"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';

	Shiu58 shiu;
	ret = shiu.load();	if (!ret) return -1;
	
	Mat f, g, h, w;
	std::vector<Mat> hsl;
	
//	Rect box;
//	int level=0;
//	double weight=0;
	const int waittime = 5;
	VideoCapture cap;
	cap.open(0);		if (!cap.isOpened()) return -1;
	ret = cap.read(f);		if (!ret) return -1;

	do {
		ret = cap.read(f);		if (!ret) continue;
		w = f.clone();
		
		ret = shiu.run(f);
		
		if (ret) {
			shiu.show(w);
			imshow("Shiu58", w);
		}
		key = waitKey(waittime);		if (key == 'q') break;
	} while (1);

	std::cout << "Hello, World!\n";
	return 0;
}
