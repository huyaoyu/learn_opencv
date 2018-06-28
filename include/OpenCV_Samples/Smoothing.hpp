/*
 * Smoothing.hpp
 *
 *  Created on: Jun 26, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_OPENCV_SAMPLES_SMOOTHING_HPP_
#define INCLUDE_OPENCV_SAMPLES_SMOOTHING_HPP_

#include <string>

#include "opencv2/core.hpp"

#include "Runnable/Runnable.hpp"

namespace locv
{

class Run_OCV_Smoothing : public Runnable
{
public:
	Run_OCV_Smoothing();
	~Run_OCV_Smoothing();

	Runnable::RES_t run(void);

private:
	Runnable::RES_t runSample(void);

private:
	/// File-wise variables
	int DELAY_CAPTION;
	int DELAY_BLUR;
	int MAX_KERNEL_LENGTH;

	std::string window_name;

	std::string filename;

	cv::Mat src;
	cv::Mat dst;
};

}



#endif /* INCLUDE_OPENCV_SAMPLES_SMOOTHING_HPP_ */
