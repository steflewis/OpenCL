#ifndef __OCLWRAPPER_H__
#define __OCLWRAPPER_H__

//#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#ifdef OSX
#include <cl.hpp>
#else
#include <CL/cl.hpp>
#endif



//#include <cstdio>
//#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
//#include <iterator>
//#include <Timing.h>
#include <DeviceInfo.h>
#include <PlatformInfo.h>

void checkErr(cl_int err, const char * name);

typedef unsigned int uint;

#if MRMODE==0
#define CL_MEM_READ_MODE CL_MEM_COPY_HOST_PTR
#elif MRMODE==1
#define CL_MEM_READ_MODE (CL_MEM_COPY_HOST_PTR | CL_MEM_ALLOC_HOST_PTR)
#elif MRMODE==2
#define CL_MEM_READ_MODE CL_MEM_USE_HOST_PTR
#else
#define CL_MEM_READ_MODE CL_MEM_COPY_HOST_PTR // default
#endif

class OclWrapper {
	private:
		std::string kernelsource;
		cl::vector<cl::Platform> platformList;
		// This assumes a single context, a single device, a single program and a single kernel
		cl::vector<cl::Device> devices;
		cl::Program* program_p;

		int platformIdx, deviceIdx;
		bool useGPU;
		cl_int err;                            // error code returned from API calls

		void getContextAndDevices();
		void getDevices();

	public:
		cl::Context* context_p;
		cl::Kernel* kernel_p;
		cl::CommandQueue* queue_p;
		int nPlatforms;
		DeviceInfo deviceInfo;
#ifdef PLATINFO
		PlatformInfo platformInfo;
#endif

		OclWrapper (bool use_gpu);
		OclWrapper (bool use_gpu, int deviceIdx);
		OclWrapper ();

		bool hasGPU(int pIdx);
		bool hasCPU(int pIdx);
		int nDevices(int pIdx, std::string dev);
		void selectDevice(int platformIdx, int deviceIdx, bool useGPU);
		void selectDevice(int deviceIdx);
		void selectDevice();
		void selectGPU();
		void selectCPU();

		void buildProgram(const char* ksource);
		void loadKernel(const char* kname);
		void loadKernel(const char* ksource, const char* kname);
		void loadBinary(const char* ksource);
		void storeBinary(const char* ksource);
		void createQueue();
		cl::KernelFunctor enqueueNDRange(const cl::NDRange&,const cl::NDRange&);
		void readBuffer(const cl::Buffer& deviceBuf, int bufSize, void* hostBuf);
		void readBuffer(
		const cl::Buffer& buffer,
		bool blocking_read,
		::size_t offset,
		::size_t size,
		void * ptr,
		const VECTOR_CLASS<cl::Event> * events = NULL,
		cl::Event * event = NULL);

};
#endif  // __OCLWRAPPER_H__
