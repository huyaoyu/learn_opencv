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

static void show_floating_point_number_image(cv::InputArray _src, const std::string& winName)
{
	cv::Mat src = _src.getMat();

	namedWindow(winName.c_str(), cv::WINDOW_NORMAL);
	double minV = 0.0, maxV = 0.0;
	cv::minMaxLoc(src, &minV, &maxV);

	cv::Mat shifted = (src - minV) / (maxV - minV);

	cv::minMaxLoc(shifted, &minV, &maxV);

	cv::imshow(winName.c_str(), shifted);
}

template<typename T>
void flush_small_positive_values(cv::InputOutputArray _m, T limit, T v = -1)
{
	if ( v <= 0 )
	{
		v = limit;
	}

	cv::Mat m = _m.getMat();

	for ( int i = 0; i < m.rows; ++i )
	{
		for ( int j = 0; j< m.cols; ++j )
		{
			if ( m.at<T>(i, j) <= limit )
			{
				m.at<T>(i, j) = v;
			}
		}
	}
}

/***
 * \param _src Must be using the type of CV_8UC1.
 */
template<typename T>
static int warp(cv::InputArray _src, cv::InputArray _D, cv::OutputArray _dst)
{
	// Check if _src is of type CV_8UC1.
	cv::Mat src = _src.getMat();
	int srcType = src.type();

	if ( CV_8UC1 != srcType )
	{
		std::cout << "Error. Input mat must be of type CV_8UC1." << std::endl;
		return -1;
	}

	// Check the dimensions.
	cv::Mat D = _D.getMat();

	if ( src.rows != D.rows || src.cols != D.cols )
	{
		std::cout << "Error. The source image and the D map should have the same sizes." << std::endl;
		return -1;
	}

	// Allocate memory for _dst.
	_dst.create( src.rows, src.cols, CV_8UC1 );

	int d = 0;
	int i2 = 0;

	for ( int i = 0; i < src.rows; ++i )
	{
		for ( int j = 0; j < src.cols; ++j )
		{
			// Disparity.
			d = (int)( D.at<T>(i,j) );

			if ( d <= 0 )
			{
				d = 0;
			}
			else if ( j - d <= 0 )
			{
				d = j;
			}

			i2 = j - d;

			// Assign

		}
	}


}

static void mutual_information(cv::InputArray _s1, cv::InputArray _s2, cv::OutputArray _dst, int intensityBins = 256)
{
	// Get the Mat objects.

	cv::Mat s1 = _s1.getMat();
	cv::Mat s2 = _s2.getMat();

	cv::Mat histDst;

	// Compute the histogram.
	cv::Mat inputMats[] = {s1, s2};
	// Prepare arguments for cv::calcHist().
	int channels[] = { 0 ,1 };
	int histSize[] = { intensityBins, intensityBins };
	Run_MutualInformation::real range0[] = { 0.0, (Run_MutualInformation::real)(intensityBins) };
	Run_MutualInformation::real range1[] = { 0.0, (Run_MutualInformation::real)(intensityBins) };
	const Run_MutualInformation::real* ranges[] = {range0, range1};

	cv::calcHist( inputMats, 2, channels, cv::Mat(), histDst, 2, histSize, ranges, true, false);

	int imageSize = s1.rows * s1.cols;
	Run_MutualInformation::real f = 1.0 / imageSize;

	histDst *= f;

	// Gaussian convolution with GaussianBlur.
	cv::Mat GBDst;
//	cv::GaussianBlur( histDst, GBDst, cv::Size( 7, 7 ), 0, 0, cv::BORDER_CONSTANT );
	cv::GaussianBlur( histDst, GBDst, cv::Size( 7, 7 ), 0, 0 );

	// Logarithm.
	cv::Mat logDst;
	// Direct log() without any modification for the zero value in GBDst will cause problem.
	// The current version of OpenCV, 3.4.1, behaves differently with the 2.x version.
	// cv::log() gaves undefined value if the input is negative, zero, NaN and Inf.

	flush_small_positive_values<Run_MutualInformation::real>(GBDst, 1e-20);
	cv::log( GBDst, logDst );
	logDst *= -1;

	// Gaussian convolution with GaussianBlur, again.
//	cv::GaussianBlur( logDst, GBDst, cv::Size( 7, 7), 0, 0, cv::BORDER_CONSTANT );
	cv::GaussianBlur( logDst, GBDst, cv::Size( 7, 7), 0, 0 );

	// Divide by the size of the image.
	GBDst *= f;

	_dst.assign(GBDst);

	std::cout << "Test output." << std::endl;
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
	namedWindow("Greyscale image left", cv::WINDOW_NORMAL );
	cv::imshow("Greyscale image left", greyImgs[0] );

	std::cout << "Channels in left image is " << greyImgs[0].channels() << std::endl;

//	std::cout << greyImgs[0] << std::endl;

	namedWindow("Greyscale image right", cv::WINDOW_NORMAL );
	cv::imshow("Greyscale image right", greyImgs[1] );

	std::cout << "Channels in right image is " << greyImgs[1].channels() << std::endl;

	cv::Mat mi;
	mutual_information( greyImgs[0], greyImgs[1], mi );

	show_floating_point_number_image(mi, "mi");

	cv::waitKey(0);

	this->show_footer();

	return res;
}
