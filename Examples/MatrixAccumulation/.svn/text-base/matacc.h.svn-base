#ifndef __MATMULT_H__
#define __MATMULT_H__

//#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#ifdef OSX
#include <cl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <sys/time.h>

//For our program, we use a small number of additional C++ headers, which are agnostic to OpenCL.

//#include <cstdio>
//#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
//#include <iterator>
#include <DeviceInfo.h>

inline void checkErr(cl_int err, const char * name);
inline double wsecond();
typedef unsigned int uint;


#endif  // __MATMULT_H__

