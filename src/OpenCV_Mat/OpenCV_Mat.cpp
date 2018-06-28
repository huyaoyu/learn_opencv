/*
 * OpenCV_Mat.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: yyhu
 */

#include <iostream>

#include <opencv2/core/core.hpp>

#include "OpenCV_Mat/OpenCV_Mat.hpp"

using namespace locv;

Run_OpenCV_Mat::Run_OpenCV_Mat()
: Runnable("OpenCV_Mat")
{

}

Run_OpenCV_Mat::~Run_OpenCV_Mat()
{

}

Runnable::RES_t Run_OpenCV_Mat::run(void)
{
	this->show_header();

	cv::Mat A = ( cv::Mat_<unsigned char>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9 );

	std::cout << "A = " << std::endl << A << std::endl << std::endl;

	// Test the t() function.
	std::cout << "A.t() = " << std::endl << A.t() << std::endl << std::endl;
	std::cout << "After transposition, A = " << std::endl << A << std::endl << std::endl;

	// Test the t() function with assignment.
	cv::Mat B = A.t();

	std::cout << "B = " << std::endl << B << std::endl << std::endl;
	B.at<unsigned char>(1,2) = 10;

	std::cout << "After assigning value to B." << std::endl;
	std::cout << "A = " << std::endl << A << std::endl;
	std::cout << "B = " << std::endl << B << std::endl;

	// Test arithmetic operations.
	cv::Mat C = A.clone();

	C += 1;

	std::cout << "C += 1 -> " << std::endl << C << std::endl << std::endl;

	C -= 1;

	std::cout << "C -= 1 -> " << std::endl << C << std::endl << std::endl;

	C *= 10;

	std::cout << "C *= 10 -> " << std::endl << C << std::endl << std::endl;

	C = A.clone();

	C += A;

	std::cout << "C += A -> " << std::endl << C << std::endl << std::endl;

	C -= A;

	std::cout << "C -= A -> " << std::endl << C << std::endl << std::endl;

	C = A.clone();
	C += 250;

	std::cout << "C += 250 -> " << std::endl << C << std::endl << std::endl;

	C = A.clone();
	C -= 250;

	std::cout << "C -= 250 -> " << std::endl << C << std::endl << std::endl;

	C = A.clone();
	C *= 100;

	std::cout << "C *= 100 -> " << std::endl << C << std::endl << std::endl;

	cv::Mat D;
	A.convertTo(D, CV_32FC1); // Only CV_32FC1, CV_32FC2, CV_64FC1 and, CV_64FC2 could be used to do matrix multiplication.

	std::cout << "D = " << std::endl << D << std::endl << std::endl;

	D *= D;

	std::cout << "D *= D -> " << std::endl << D << std::endl << std::endl;

	cv::Mat DD = A.clone();
	std::cout << "DD.type() = " << DD.type() << std::endl;
	std::cout << "DD = " << std::endl << DD << std::endl << std::endl;
	DD.convertTo(DD, CV_64FC1);
	std::cout << "DD.type() = " << DD.type() << std::endl;
	std::cout << "DD = " << std::endl << DD << std::endl << std::endl;

	DD *= 100;
	std::cout << "DD *= 100 -> " << std::endl << DD << std::endl << std::endl;

	DD.convertTo(DD, CV_8UC1);
	std::cout << "DD convert to CV_8UC1  -> "<< std::endl << DD << std::endl << std::endl;

	DD = A.clone();
	DD.convertTo(DD, CV_64FC1);
	DD -= 250;
	std::cout << "DD convert to CV_64FC1, -= 250 -> " << std::endl
			  << DD << std::endl << std::endl;
	DD.convertTo(DD, CV_8UC1);
	std::cout << "DD convert to CV_8UC1 -> " << std::endl
			  << DD << std::endl << std::endl;

	cv::Mat E;
//	E = D + A; // This will cause a runtime exception.
//	std::cout << "E.type() = " << E.type() << std::endl << std::endl;

	cv::add( A, D, E, cv::Mat(), CV_32SC1 );
	std::cout << "E = A + D -> " << E << std::endl << std::endl;
	std::cout << "E.type() = " << E.type() << std::endl << std::endl;

	B = 250;

	cv::add(B, D, E, cv::Mat(), CV_32SC1);
	std::cout << "B = 250, E = B + D with CV_32SC1 -> " << std::endl << E << std::endl << std::endl;

	cv::add(B, D, E, cv::Mat(), CV_8UC1);
	std::cout << "B = 250, E = B + D with CV_8UC1 -> " << std::endl << E << std::endl << std::endl;

	this->show_footer();

	return Runnable::OK;
}
