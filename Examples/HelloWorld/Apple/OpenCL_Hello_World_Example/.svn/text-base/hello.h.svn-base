#ifndef HELLO_H_
#define HELLO_H_

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

inline void checkErr(cl_int err, const char * name);
inline double wsecond();

#endif /* HELLO_H_ */
