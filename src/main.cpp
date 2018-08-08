/*
 * main.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: yyhu
 */

#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "InterpolationForStereo/InterpolationForStereo.hpp"
#include "MutualInformation/MutualInformation.hpp"
#include "StereoDisparity/StereoDisparity.hpp"

#include "OpenCV_Mat/OpenCV_Mat.hpp"
#include "OpenCV_Samples/Histogram.hpp"
#include "OpenCV_Samples/Mandelbrot.hpp"
#include "OpenCV_Samples/Smoothing.hpp"

#define CREATE_ADD_OBJECT(c, n, v) \
	c n;\
	v.push_back( &n );

int main(void)
{
	std::cout << "Hello OpenCV!" << std::endl;

	// Show sizes of types.
	locv::Runnable::show_size_of_types();

	// Create a vector.
	std::vector<locv::Runnable*> vecRunnables;

//	// Create a new object.
//	CREATE_ADD_OBJECT(locv::Run_OpenCV_Mat, runOpenCVMat, vecRunnables);
//
//	// Create a Smoothing object.
//	CREATE_ADD_OBJECT(locv::Run_OCV_Smoothing, runOCVSmoothing, vecRunnables);
//
//	// Create a Mandelbrot object.
//	CREATE_ADD_OBJECT(locv::Run_OCV_Mandelbrot, runOCVMandelbrot, vecRunnables);
//
//	// Create a Histogram object.
//	CREATE_ADD_OBJECT(locv::Run_OCV_Histogram, runOCVHistogram, vecRunnables);

	// // Create a MutualInformation object.
	// CREATE_ADD_OBJECT(locv::Run_MutualInformation, runMutualInformation, vecRunnables);

	// // Create a InterpolationForStereo objec.
	// CREATE_ADD_OBJECT(locv::Run_InterpolationForStereo, runInterpolationForStereo, vecRunnables);
	// runInterpolationForStereo.set_image_size(3008, 4112);

	// Create a StereoDisparity objec.
	CREATE_ADD_OBJECT(locv::Run_StereoDisparity, runStrereoDisparity, vecRunnables);

	// Run the Runnable object.
	std::vector<locv::Runnable*>::iterator iter;

	for( iter = vecRunnables.begin(); iter != vecRunnables.end(); ++iter )
	{
		(*iter)->run();
	}

	return 0;
}

