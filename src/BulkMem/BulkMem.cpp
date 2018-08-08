
#include "BulkMem/BulkMem.hpp"

using namespace locv;

template<typename _T> BulkMem<_T>::i_t BulkMem<_T>::TOTAL_SIZE = 0;

template<typename _T>
BulkMem<_T>::BulkMem(i_t nDim, i_t* dim, bool faked)
{
    mNDim = nDim;
    mDim = new i_t[mNDim];
    mSize = 1;
    for ( i_t i = 0; i < mNDim; ++i )
    {
        mSize *= dim[i];
        mDim[i] = dim[i];
    }

    mFaked = faked;
    if ( false == mFaked )
    {
        ptr = new _T[ mSize ];
    }
}

template<typename _T> 
BulkMem< _T >::~BulkMem()
{
    if ( ptr != NULL && false == mFaked )
    {
        delete [] ptr; ptr = NULL;
    }

    if ( mDim != NULL )
    {
        delete [] mDim; mDim = NULL;
    }
}

template<typename _T>
_T* BulkMem<_T>::get(void)
{
    return ptr;
}

template<typename _T>
bool BulkMem<_T>::is_faked(void)
{
    return mFaked;
}