#include "matacc.h";


inline void checkErr(cl_int err, const char * name) {
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
		exit( EXIT_FAILURE);
	}
}

double wsecond()
{
        struct timeval sampletime;
        double         time;

        gettimeofday( &sampletime, NULL );
        time = sampletime.tv_sec + (sampletime.tv_usec / 1000000.0);
        return( time*1000.0 ); // return time in ms
}


// Use a static data size for simplicity
//
//#define WIDTH 1024
// 1024*1024 gives segmentation fault when using static allocation, because it's on the stack
// 32M is the max because CL_DEVICE_MAX_MEM_ALLOC_SIZE = 128MB for my iMac, and a cl_float is 4 bytes.

int main(void)
{



    // this array uses stack memory because it's declared inside of a function. 
    // So the size of the stack determines the max array size! 
    //cl_float data[DATA_SIZE];              // original data set given to device
    //cl_float results[DATA_SIZE];           // results returned from device


    const uint mSize = WIDTH*WIDTH;
    const uint mWidth = WIDTH;

    // Create the data sets   
    cl_float* mA=(cl_float*)malloc(sizeof(cl_float)*mSize);


   
    for(unsigned int i = 0; i < mSize; i++) {
        mA[i] = (cl_float)(1.0/(float)mSize);

    }
#if REF!=0
    cl_float mCref=0.0;
    double tstartref=wsecond();

    for (uint i = 0; i<mWidth; i++) {
    	for (uint j = 0; j<mWidth; j++) {
			mCref+=mA[i*mWidth+j];
		}
	}

    double tstopref=wsecond();
#ifdef VERBOSE
    std::cout << "Execution time for reference: "<<(tstopref-tstartref)<<" ms\n";
#else
    std::cout << (tstopref-tstartref); //<<"\n";
#endif
#endif
#if REF!=2
    //--------------------------------------------------------------------------------
    //---- Here starts the actual OpenCL part
    //--------------------------------------------------------------------------------
    cl_int err;                            // error code returned from api calls
    // First check the Platform
    cl::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    checkErr(platformList.size() != 0 ? CL_SUCCESS : -1, "cl::Platform::get");
//    std::cerr << "Platform number is: " << platformList.size() << std::endl;
    std::string platformVendor;
    platformList[0].getInfo((cl_platform_info) CL_PLATFORM_VENDOR,
            &platformVendor);
//    std::cerr << "Platform is by: " << platformVendor << "\n";

    // Use the platform info as input for the Context    
    cl_context_properties cprops[3] = { CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platformList[0])(), 0 };
#ifndef CPU
//    std::cout << "\nUsing GPU\n";
    cl::Context context(CL_DEVICE_TYPE_GPU, cprops, NULL, NULL, &err); // CPU-only 
#else
//    std::cout << "\nUsing CPU\n";
    cl::Context context(CL_DEVICE_TYPE_CPU, cprops, NULL, NULL, &err); // CPU-only 
#endif 
    checkErr(err, "Context::Context()");

    cl::vector<cl::Device> devices;
    devices = context.getInfo<CL_CONTEXT_DEVICES>();
    checkErr( devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");

    // Get info
    DeviceInfo info;
#ifdef DEVINFO
    info.show(devices.front());
#endif

    unsigned int nunits=info.max_compute_units( devices.front() );
    cl_float* mC=(cl_float*)malloc(sizeof(cl_float)*nunits);
    // Now load the kernel
    // How about a nice class 
    // KernelLoader kl(string filename);
    // cl::Kernel KernelLoader::build(string kernel_name, cl::Context context, cl::Devices devices);
    std::ifstream file("matacc.cl");
    checkErr(file.is_open() ? CL_SUCCESS:-1, "matacc.cl");

    std::string prog(
            std::istreambuf_iterator<char>(file),
            (std::istreambuf_iterator<char>())
            );

    cl::Program::Sources source(1, std::make_pair(prog.c_str(), prog.length()+1));

    cl::Program program(context, source);
    err = program.build(devices,"");
    checkErr(file.is_open() ? CL_SUCCESS : -1, "Program::build()");
#if KERNEL==2
    cl::Kernel kernel(program, "mataccKernel2", &err);
#elif KERNEL==3
    cl::Kernel kernel(program, "mataccKernel3", &err);
#elif KERNEL==4
    cl::Kernel kernel(program, "mataccKernel4", &err);
#elif KERNEL==5
    cl::Kernel kernel(program, "mataccKernel5", &err);
#elif KERNEL==6
    cl::Kernel kernel(program, "mataccKernel6", &err);
#elif KERNEL==7
    cl::Kernel kernel(program, "mataccKernel7", &err);
#elif KERNEL==8
    cl::Kernel kernel(program, "mataccKernel8", &err);
#elif KERNEL==9
    cl::Kernel kernel(program, "mataccKernel9", &err);
#elif KERNEL==10
    cl::Kernel kernel(program, "mataccKernel10", &err);
#elif KERNEL==11
    cl::Kernel kernel(program, "mataccKernel11", &err);
#elif KERNEL==12
    cl::Kernel kernel(program, "mataccKernel12", &err);
#elif KERNEL==13
    cl::Kernel kernel(program, "mataccKernel13", &err);
#else
    cl::Kernel kernel(program, "mataccKernel1", &err);
#endif    
    checkErr(err, "Kernel::Kernel()");

#if MRMODE==0
#define CL_MEM_READ_MODE CL_MEM_COPY_HOST_PTR
#elif MRMODE==1
#define CL_MEM_READ_MODE (CL_MEM_COPY_HOST_PTR | CL_MEM_ALLOC_HOST_PTR)
#elif MRMODE==2
#define CL_MEM_READ_MODE CL_MEM_USE_HOST_PTR
#else
#define CL_MEM_READ_MODE CL_MEM_COPY_HOST_PTR
#endif
    // Create the buffers
    cl::Buffer mA_buf(
            context,
            CL_MEM_READ_ONLY | CL_MEM_READ_MODE,
            sizeof(cl_float) * mSize,
            mA,
            &err);
    checkErr(err, "Buffer::Buffer input()");

    cl::Buffer mC_buf(
            context,
            CL_MEM_WRITE_ONLY,
            sizeof(cl_float)*nunits,
            NULL,
            &err);
    checkErr(err, "Buffer::Buffer output()");

    // setArg takes the index of the argument and a value of the same type as the kernel argument 
    err = kernel.setArg(0, mA_buf );
    checkErr(err, "Kernel::setArg(0)");

    err = kernel.setArg(1, mC_buf);
    checkErr(err, "Kernel::setArg(2)");

    err = kernel.setArg(2, mWidth);
    checkErr(err, "Kernel::setArg(2)");

    // Create the CommandQueue
    cl::CommandQueue queue(context, devices[0], 0, &err);
    checkErr(err, "CommandQueue::CommandQueue()");


    // This is the actual "run" command. The 3 NDranges are
    // offset, global and local    
    cl::Event event;
    err = queue.enqueueNDRangeKernel(
            kernel, 
            cl::NullRange,
#if KERNEL<7
            cl::NDRange(nunits),
            cl::NDRange(1),
#elif KERNEL<=8
            cl::NDRange(nunits*64), // 4 compute units
            cl::NDRange(16), // 16 threads
#elif KERNEL==9
            cl::NDRange(nunits*64), // 2 compute units
            cl::NDRange(32), // 32 threads
#elif KERNEL==10
            cl::NDRange(nunits*16), // 2 compute units
            cl::NDRange(16), // 16 threads
#elif KERNEL==12
            cl::NDRange(nunits*16), // 2 compute units
            cl::NDRange(16), // 16 threads
#elif KERNEL==13
            cl::NDRange(nunits*128), // 2 compute units
            cl::NDRange(64), // 64 threads
#elif KERNEL==11
            cl::NDRange(nunits), // 2 compute units
            cl::NDRange(1), // single thread
#endif
            NULL, 
            &event);
    checkErr(err, "CommandQueue::enqueueNDRangeKernel()");

    double tstart=wsecond();

    event.wait();  // segfaults here!  

    // Read back the results
       err = queue.enqueueReadBuffer(
            mC_buf,
            CL_TRUE,
            0,
            sizeof(cl_float)*nunits,
            mC);
    checkErr(err, "CommandQueue::enqueueReadBuffer()");

    double tstop=wsecond();
#endif
    //--------------------------------------------------------------------------------
    //----  Here ends the actual OpenCL part
    //--------------------------------------------------------------------------------
#ifdef VERBOSE
#if REF==1
    float mCtot=0.0;
    for (unsigned int i=0;i<nunits;i++) {
    	mCtot+=mC[i];
    }
    unsigned int correct=0;               // number of correct results returned
        if(mCtot == mCref) {
            correct++;
        }
    std::cout << mCtot <<"<>"<< mCref<<"\n";
#endif
#if REF!=2
    std::cout << "OpenCL execution time "<<(tstop-tstart)<<" ms\n";
#endif
#else
#if REF!=2
    std::cout << (tstop-tstart);//<<"\n";
#endif
#endif
    free(mA);
#if REF!=2
    free(mC);
#endif
    return EXIT_SUCCESS;

}
