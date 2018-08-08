/*
 * BulkMem.hpp
 *
 *  Created on: Aug 7, 2018
 *      Author: yyhu
 */

#ifndef INCLUDE_BULKMEM_BULKMEM_HPP_
#define INCLUDE_BULKMEM_BULKMEM_HPP_

#include <iostream>
#include <string>
#include <sstream>

#include "LOCVException/LOCVException.hpp"

namespace locv
{

template<class _T>
class BulkMem
{
public:
    typedef unsigned long i_t;

public:
    BulkMem(i_t nDim, i_t* dim, bool faked = false);
    ~BulkMem();

    _T* get(void);

    bool is_faked(void);

public:
    _T* ptr;

protected:
    i_t mSize;
    i_t mNDim;
    i_t* mDim;
    bool mFaked;

    static i_t TOTAL_SIZE;

private:
    BulkMem(const BulkMem& bm) { }    
    BulkMem(BulkMem& bm) { }    
};

}

#endif /* INCLUDE_BULKMEM_BULKMEM_HPP_ */
