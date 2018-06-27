/*
 * Smoothing.cpp
 *
 *  Created on: Jun 26, 2018
 *      Author: yyhu
 */

#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "OpenCV_Samples/Smoothing.hpp"

using namespace std;
using namespace cv;
using namespace locv;

/// Function declarations
static int display_dst( int delay , const std::string& winName, InputArray dstArr)
{
	imshow( winName.c_str(), dstArr.getMat() );
	int c = waitKey ( delay );
	if( c >= 0 ) { return -1; }
	return 0;
}

static int display_caption( const std::string& caption , const std::string& winName,
		int delay,
		InputArray srcArr, OutputArray dstArr)
{
	Mat src = srcArr.getMat();

	dstArr.create(src.size(), src.type());
	Mat dst = dstArr.getMat();
	dst = Mat::zeros( src.size(), src.type() );
	putText( dst, caption,
			 Point( src.cols/4, src.rows/2),
			 FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );

	return display_dst(delay, winName, dst);
}

// ========= Class members. ===============

Run_OCV_Smoothing::Run_OCV_Smoothing()
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(DEFAULT_NAME),
  DELAY_CAPTION(1000), DELAY_BLUR(50), MAX_KERNEL_LENGTH(31),
  window_name("Smoothing Demo"), filename("../data/Landscape.jpg")
{

}

Run_OCV_Smoothing::Run_OCV_Smoothing(const std::string& name)
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(name),
  DELAY_CAPTION(1000), DELAY_BLUR(50), MAX_KERNEL_LENGTH(31),
  window_name("Smoothing Demo"), filename("../data/Landscape.jpg")
{

}

Run_OCV_Smoothing::Run_OCV_Smoothing(std::string& name)
: DEFAULT_NAME("OpenCV_Samples_Smoothing"),
  Runnable(name),
  DELAY_CAPTION(1000), DELAY_BLUR(50), MAX_KERNEL_LENGTH(31),
  window_name("Smoothing Demo"), filename("../data/Landscape.jpg")
{

}

Run_OCV_Smoothing::~Run_OCV_Smoothing()
{

}

Runnable::RES_t Run_OCV_Smoothing::run(void)
{
	this->show_header();

	Runnable::RES_t res = runSample();

	this->show_footer();

	return res;
}

Runnable::RES_t Run_OCV_Smoothing::runSample(void)
{
	namedWindow( window_name, WINDOW_AUTOSIZE );

	src = imread( filename, IMREAD_COLOR );
	if(src.empty()){
		cout << " Error opening image\n";
		cout << " Usage: ./Smoothing [image_name -- default ../data/lena.jpg] \n";
		return Runnable::ERROR;
	}

	if( display_caption( "Original Image", window_name, DELAY_CAPTION, src, dst ) != 0 ) { return Runnable::ERROR; }

	dst = src.clone();
	if( display_dst( DELAY_CAPTION, window_name, dst ) != 0 ) { return Runnable::ERROR; }


	/// Applying Homogeneous blur
	if( display_caption( "Homogeneous Blur", window_name, DELAY_CAPTION, src, dst ) != 0 ) { return Runnable::ERROR; }

	cout << "Homogeneous Blur." << endl;

	//![blur]
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		cout << "i = " << i << " / " << MAX_KERNEL_LENGTH << endl;

		blur( src, dst, Size( i, i ), Point(-1,-1) );

		if( display_dst( DELAY_BLUR, window_name, dst ) != 0 ) { return Runnable::ERROR; }
	}
	//![blur]

	/// Applying Gaussian blur
	if( display_caption( "Gaussian Blur", window_name, DELAY_CAPTION, src, dst ) != 0 ) { return Runnable::ERROR; }

	cout << "Gaussian Blur." << endl;

	//![gaussianblur]
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		cout << "i = " << i << " / " << MAX_KERNEL_LENGTH << endl;

		GaussianBlur( src, dst, Size( i, i ), 0, 0, BORDER_CONSTANT);

		if( display_dst( DELAY_BLUR, window_name, dst ) != 0 ) { return Runnable::ERROR; }
	}
	//![gaussianblur]

	/// Applying Median blur
	if( display_caption( "Median Blur", window_name, DELAY_CAPTION, src, dst ) != 0 ) { return Runnable::ERROR; }

	cout << "Median Blur." << endl;

	//![medianblur]
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		cout << "i = " << i << " / " << MAX_KERNEL_LENGTH << endl;

		medianBlur ( src, dst, i );

		if( display_dst( DELAY_BLUR, window_name, dst ) != 0 ) { return Runnable::ERROR; }
	}
	//![medianblur]

	/// Applying Bilateral Filter
	if( display_caption( "Bilateral Blur", window_name, DELAY_CAPTION, src, dst ) != 0 ) { return Runnable::ERROR; }

	cout << "Bilateral Blul." << endl;

	//![bilateralfilter]
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	{
		cout << "i = " << i << " / " << MAX_KERNEL_LENGTH << endl;

		bilateralFilter ( src, dst, i, i*2, i/2 );

		if( display_dst( DELAY_BLUR, window_name, dst ) != 0 ) { return Runnable::ERROR; }
	}
	//![bilateralfilter]

	/// Done
	display_caption( "Done!", window_name, DELAY_CAPTION, src, dst );

	return Runnable::OK;
}
