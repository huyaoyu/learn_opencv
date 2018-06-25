/*
 * main.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: yyhu
 */

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "OpenCV_Mat/OpenCV_Mat.hpp"

int main(void)
{
	std::cout << "Hello OpenCV!" << std::endl;

	// Create a vector.
	std::vector<locv::Runnable*> vecRunnables;

	// Create a new object.
	locv::Run_OpenCV_Mat runOpenCVMat("runOpenCVMat");
	vecRunnables.push_back( &runOpenCVMat );

	// Run the Runnable object.
	std::vector<locv::Runnable*>::iterator iter;

	for( iter = vecRunnables.begin(); iter != vecRunnables.end(); ++iter )
	{
		(*iter)->run();
	}

	return 0;
}

