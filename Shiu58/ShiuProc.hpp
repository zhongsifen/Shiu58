//
//  ShiuProc.hpp
//  Shiu58
//
//  Created by SIFEN ZHONG on 1/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef ShiuProc_hpp
#define ShiuProc_hpp

#include "ShiuPalm.hpp"
#include "ShiuFinger.hpp"
#include <opencv2/core.hpp>

namespace ShiuProc {
	bool process(cv::Mat& f, cv::Mat& mask);
};

#endif /* ShiuProc_hpp */
