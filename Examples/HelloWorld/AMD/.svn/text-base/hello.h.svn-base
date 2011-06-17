/*
 * hello.h
 *
 *  Created on: Apr 14, 2011
 *      Author: wim
 *      http://developer.amd.com/gpu/amdappsdk/documentation/pages/TutorialOpenCL.aspx
 */

#ifndef HELLO_H_
#define HELLO_H_

#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#ifdef OSX
#include "cl.hpp"
#else
#include <CL/cl.hpp>
#endif

//For our program, we use a small number of additional C++ headers, which are agnostic to OpenCL.

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

//As we will dynamically request an OpenCL device to return the "Hello World\n" string, we define it as a constant to use in calculations.

const std::string hw("Hello_World\n");

inline void checkErr(cl_int err, const char * name);

#endif /* HELLO_H_ */
