/*
 * Mandelbrot.hpp
 *
 *  Created on: Jun 26, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_OPENCV_SAMPLES_MANDELBROT_HPP_
#define INCLUDE_OPENCV_SAMPLES_MANDELBROT_HPP_

#include "Runnable/Runnable.hpp"

namespace locv
{

class Run_OCV_Mandelbrot : public Runnable
{
public:
	Run_OCV_Mandelbrot();
	~Run_OCV_Mandelbrot();

	Runnable::RES_t run(void);

private:
	Runnable::RES_t runSample(void);
};

}



#endif /* INCLUDE_OPENCV_SAMPLES_MANDELBROT_HPP_ */
