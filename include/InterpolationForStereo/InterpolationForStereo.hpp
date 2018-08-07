/*
 * InterpolationForStereo.hpp
 *
 *  Created on: Aug 6, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_INTERPOLATIONFORSTEREO_INTERPOLATIONFORSTEREO_HPP_
#define INCLUDE_INTERPOLATIONFORSTEREO_INTERPOLATIONFORSTEREO_HPP_

#include <vector>

#include "Runnable/Runnable.hpp"

namespace locv
{

class Run_InterpolationForStereo : public Runnable
{
public:
	typedef float real;

    typedef struct Vec
    {
        real x;
        real y;
    } Vec_t;

    typedef enum
    {
        SIDE_0 = 0,
        SIDE_1 = 1,
        SIDE_2 = 2,
        SIDE_3 = 3
    } Side_t;

public:
	Run_InterpolationForStereo();
	~Run_InterpolationForStereo();

	Runnable::RES_t run(void);

    void set_image_size(int h, int w);
    void set_n_angles(int n);

protected:
    Runnable::RES_t put_sides( Vec_t& r, Side_t& s0, Side_t& s1 );

public:
    const int IDX_H; // Height index.
    const int IDX_W; // Width index.
    const real SMALL_VALUE;

private:
    int mNR;
    std::vector<Vec_t> mR;
    int mImageSize[2];
};

}

#endif /* INCLUDE_INTERPOLATIONFORSTEREO_INTERPOLATIONFORSTEREO_HPP_ */