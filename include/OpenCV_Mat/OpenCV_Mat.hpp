/*
 * OpenCV_Mat.hpp
 *
 *  Created on: Jun 24, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_OPENCV_MAT_HPP_
#define INCLUDE_OPENCV_MAT_HPP_


#include <opencv2/core.hpp>

#include "Runnable/Runnable.hpp"

namespace locv
{

class Run_OpenCV_Mat : public Runnable
{
public:
	Run_OpenCV_Mat();
	~Run_OpenCV_Mat();

	Runnable::RES_t run(void);
};

}

#endif /* INCLUDE_OPENCV_MAT_HPP_ */
