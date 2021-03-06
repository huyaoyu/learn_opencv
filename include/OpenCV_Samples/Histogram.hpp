/*
 * Histogram.hpp
 *
 *  Created on: Jun 27, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_OPENCV_SAMPLES_HISTOGRAM_HPP_
#define INCLUDE_OPENCV_SAMPLES_HISTOGRAM_HPP_


#include "Runnable/Runnable.hpp"

namespace locv
{

class Run_OCV_Histogram : public Runnable
{
public:
	Run_OCV_Histogram();
	~Run_OCV_Histogram();

	Runnable::RES_t run(void);

private:
	Runnable::RES_t runSample(void);
};

}


#endif /* INCLUDE_OPENCV_SAMPLES_HISTOGRAM_HPP_ */
