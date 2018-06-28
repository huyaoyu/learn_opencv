/*
 * MutualInformation.cpp
 *
 *  Created on: Jun 28, 2018
 *      Author: yyhu
 */

#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "MutualInformation/MutualInformation.hpp"

using namespace locv;

Run_MutualInformation::Run_MutualInformation()
: Runnable("MutualInformation")
{

}

Run_MutualInformation::~Run_MutualInformation()
{

}

static void mutual_information(cv::InputArray _s1, cv::InputArray _s2, cv::OutputArray _dst)
{
	// Get the Mat objects.

	cv::Mat s1 = _s1.getMat();
	cv::Mat s2 = _s2.getMat();
	_dst.create( s1.size(), CV_8UC2 );
	cv::Mat dst = _dst.getMat();

	// Copy the data into a new Mat object.


	cv::merge( , 2, dst );
}

Runnable::RES_t Run_MutualInformation::run(void)
{
	Runnable::RES_t res = Runnable::OK;

	this->show_header();

	// Filenames.
	std::string filenames[2];
	filenames[0] = "../data/MutualInformation/left.bmp";
	filenames[1] = "../data/MutualInformation/right.bmp";

	// Read these two images.
	cv::Mat srcImgs[2];

	srcImgs[0] = imread( filenames[0], cv::IMREAD_COLOR );
	srcImgs[1] = imread( filenames[1], cv::IMREAD_COLOR );

	// Generate grey scale images.
	cv::Mat greyImgs[2];

	cv::cvtColor(srcImgs[0], greyImgs[0], cv::COLOR_BGR2GRAY, 1);
	cv::cvtColor(srcImgs[1], greyImgs[1], cv::COLOR_BGR2GRAY, 1);

	// Show the grey images.
	namedWindow("Greyscale image left", cv::WINDOW_AUTOSIZE );
	imshow("Greyscale image left", greyImgs[0] );

	std::cout << "Channels in left image is " << greyImgs[0].channels() << std::endl;

	namedWindow("Greyscale image right", cv::WINDOW_AUTOSIZE );
	imshow("Greyscale image right", greyImgs[1] );

	std::cout << "Channels in right image is " << greyImgs[1].channels() << std::endl;

	cv::Mat twoCn;
	mutual_information( greyImgs[0], greyImgs[1], twoCn );

	cv::waitKey(0);

	this->show_footer();

	return res;
}
