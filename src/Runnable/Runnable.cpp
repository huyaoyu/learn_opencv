/*
 * Runnable.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: yyhu
 */

#include "Runnable/Runnable.hpp"

using namespace locv;

Runnable::Runnable(std::string& name)
: mName(name)
{

}

Runnable::Runnable(const std::string& name)
: mName(name)
{

}

Runnable::~Runnable(void)
{

}

void Runnable::set_name(std::string& name)
{
	mName = name;
}

std::string& Runnable::get_name(void)
{
	return mName;
}

void Runnable::show_header(void)
{
	std::cout << "=== " << mName << " ===" << std::endl << std::endl;
}

void Runnable::show_footer(void)
{
	std::cout <<"=== End of " << mName << " ===" << std::endl << std::endl;
}

Runnable::RES_t Runnable::run(void)
{
	return Runnable::OK;
}
