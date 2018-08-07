
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "InterpolationForStereo/InterpolationForStereo.hpp"

using namespace locv;

static Run_InterpolationForStereo::Vec_t
get_r_by_angle(Run_InterpolationForStereo::real angle)
{
    // Local struct variable.
    Run_InterpolationForStereo::Vec_t r;
    r.x = cos(angle);
    r.y = sin(angle);

    return r;
}

Run_InterpolationForStereo::Run_InterpolationForStereo()
: Runnable("InterpolationForStereo"),
  IDX_H(0), IDX_W(1), SMALL_VALUE(1e-6),
  mNR(16)
{

}

Run_InterpolationForStereo::~Run_InterpolationForStereo()
{

}

void Run_InterpolationForStereo::set_image_size(int h, int w)
{
    mImageSize[IDX_H] = h;
    mImageSize[IDX_W] = w;
}

void Run_InterpolationForStereo::set_n_angles(int n)
{
    mNR = n;
}

Runnable::RES_t Run_InterpolationForStereo::put_sides( Vec_t& r, Side_t& s0, Side_t& s1 )
{
    real x = ( fabs(r.x) < SMALL_VALUE ) ? 0.0 : r.x;
    real y = ( fabs(r.y) < SMALL_VALUE ) ? 0.0 : r.y;

    if ( 0.0 == x && 0.0 == y )
    {
        std::cout << "The norm of r is zero." << std::endl;
        return Runnable::ERROR;
    }

    if ( x < 0.0 )
    {
        if ( y < 0.0 )
        {
            s0 = SIDE_1;
            s1 = SIDE_2;
        }
        else if ( 0.0 == y )
        {
            s0 = SIDE_1;
            s1 = SIDE_1;
        }
        else
        {
            s0 = SIDE_0;
            s1 = SIDE_1;
        }
    }
    else if ( 0.0 == x )
    {
        if ( y < 0.0 )
        {
            s0 = SIDE_2;
            s1 = SIDE_2;
        }
        else if ( 0.0 == y )
        {
            // Never reached.    
        }
        else
        {
            s0 = SIDE_0;
            s1 = SIDE_0;
        }
    }
    else
    {
        if ( y < 0.0 )
        {
            s0 = SIDE_2;
            s1 = SIDE_3;
        }
        else if ( 0.0 == y )
        {
            s0 = SIDE_3;
            s1 = SIDE_3;
        }
        else
        {
            s0 = SIDE_3;
            s1 = SIDE_0;
        }
    }

    return Runnable::OK;
}

Runnable::RES_t Run_InterpolationForStereo::run(void)
{
	Runnable::RES_t res = Runnable::OK;

	this->show_header();

    // Populate mR;

    real* angleArray = new real[mNR];
    Vec_t r;

    real angleStep = 2 * M_PI / mNR;

    for ( int i = 0; i < mNR; ++i )
    {
        r = get_r_by_angle( 1.0 * i * angleStep );
        mR.push_back(r);
    }

    Side_t s0, s1;

    std::cout << "The content of mR is: " << std::endl;

    std::vector<Vec_t>::iterator iter;
    std::cout << "r.x, r.y, s0, s1" << std::endl;
    std::cout << "[ " << std::endl;
    std::cout << std::scientific;
    std::cout << std::showpos;
    for ( iter = mR.begin(); iter != mR.end(); ++iter )
    {
        put_sides((*iter), s0, s1);
        std::cout << (*iter).x << ", " << (*iter).y 
                  << ", " << s0 << ", " << s1 << std::endl;
    }
    std::cout.unsetf(std::ios::scientific);
    std::cout << "]" << std::endl;

    // Create an image with solid color as the background.
    cv::Mat image(mImageSize[IDX_H], mImageSize[IDX_W], CV_8UC3, cv::Scalar(0));

    // Interpolate on the image.

    // Show the iamge.

    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", image);
    cv::waitKey();

    delete [] angleArray; angleArray = NULL;

	this->show_footer();

	return res;
}
