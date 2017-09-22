//
//  main.cpp
//  appShiu58
//
//  Created by SIFEN ZHONG on 23/8/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include <iostream>

int mainDetect(int argc, const char * argv[]);
int mainBgs(int argc, const char * argv[]);
int mainSkin(int argc, const char * argv[]);

int main(int argc, const char * argv[]) {
	mainSkin(argc, argv);
	
	std::cout << "Hello, World!\n";
	return 0;
	
}
