/*
 * Histogram.cpp
 *
 *  Created on: Jun 27, 2018
 *      Author: yyhu
 */

#include <iostream>
#include <vector>

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "OpenCV_Samples/Histogram.hpp"

using namespace std;
using namespace cv;
using namespace locv;

Run_OCV_Histogram::Run_OCV_Histogram()
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(DEFAULT_NAME)
{

}

Run_OCV_Histogram::Run_OCV_Histogram(const std::string& name)
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(name)
{

}

Run_OCV_Histogram::Run_OCV_Histogram(std::string& name)
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(name)
{

}

Run_OCV_Histogram::~Run_OCV_Histogram()
{

}

Runnable::RES_t Run_OCV_Histogram::run(void)
{
	this->show_header();

	Runnable::RES_t res = runSample();

	this->show_footer();

	return res;
}

Runnable::RES_t Run_OCV_Histogram::runSample(void)
{
	Mat src, dst;

	/// Load image
	String imageName( "../data/Landscape.jpg" ); // by default

	src = imread( imageName, IMREAD_COLOR );

	if( src.empty() )
	{
		cout << "Input image not found." << endl;
		return Runnable::ERROR;
	}

	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split( src, bgr_planes );

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
	  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
					   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
					   Scalar( 255, 0, 0), 2, 8, 0  );
	  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
					   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
					   Scalar( 0, 255, 0), 2, 8, 0  );
	  line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
					   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
					   Scalar( 0, 0, 255), 2, 8, 0  );
	}

	/// Display
	namedWindow("calcHist Demo", WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

	cout << "Please close the histogram window." << endl;

	waitKey(0);

	cout << endl;

	return Runnable::OK;
}
