/*
 * hello.cc
 *
 *  Created on: Apr 14, 2011
 *      Author: wim
 *      http://developer.amd.com/gpu/amdappsdk/documentation/pages/TutorialOpenCL.aspx
 */

#include "hello.h"

/*
A common property of most OpenCL™ API calls is that they either return an error code (type cl_int) as the result of the function itself, or they store the error code at a location passed by the user as a parameter to the call. As with any API call that can fail, it is important, for the application to check its behavior correctly in the case of error. For the most part we will not concern ourselves with recovering from an error; for simplicity, we define a function, checkErr, to see that a certain call has completed successfully. OpenCL™ returns the value CL_SUCCESS in this case. If it is not, it outputs a user message and exits; otherwise, it simply returns.
 */

inline void checkErr(cl_int err, const char * name) {
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
		exit( EXIT_FAILURE);
	}
}
/*
OpenCL™ Contexts

The first step to initializing and using OpenCL™ is to create a context. The rest of the OpenCL™ work (creating devices and memory, compiling and running programs) is performed within this context. A context can have a number of associated devices (for example, CPU or GPU devices), and, within a context, OpenCL™ guarantees a relaxed memory consistency between devices. We will look at this in detail in a later tutorial; for now, we use a single device, CL_DEVICE_TYPE_CPU, for the CPU device. We could have used CL_DEVICE_TYPE_GPU or some other support device type, assuming that the OpenCL™ implementation supports that device. But before we can create a context we must first queue the OpenCL™ runtime to determine which platforms, i.e. different vendor's OpenCL™ implementations, are present. The class cl::Platform provides the static method cl::Platform::get for this and returns a list of platforms. For now we select the first platform and use this to create a context. The constructor cl::Context should be successful and, in this case, the value of err is CL_SUCCESS.
 */
int main(void) {
	cl_int err;
	cl::vector<cl::Platform> platformList;
	cl::Platform::get(&platformList);
	checkErr(platformList.size() != 0 ? CL_SUCCESS : -1, "cl::Platform::get");
	std::cerr << "Platform number is: " << platformList.size() << std::endl;

	std::string platformVendor;
	platformList[0].getInfo((cl_platform_info) CL_PLATFORM_VENDOR,
			&platformVendor);
	std::cerr << "Platform is by: " << platformVendor << "\n";
	cl_context_properties cprops[3] = { CL_CONTEXT_PLATFORM,
			(cl_context_properties)(platformList[0])(), 0 };
// BEGIN WV    
#ifndef CPU
    std::cout << "\nUsing GPU\n";
	cl::Context context(CL_DEVICE_TYPE_GPU, cprops, NULL, NULL, &err); // GPU-only 
#else
    std::cout << "\nUsing CPU\n";
// END WV    
    cl::Context context(CL_DEVICE_TYPE_CPU, cprops, NULL, NULL, &err); // CPU-only 
#endif // WV
    checkErr(err, "Context::Context()");


/*
Before delving into compute devices, where the 'real' work happens, we first allocate an OpenCL™ buffer to hold the result of the kernel that will be run on the device, i.e. the string "Hello World\n." For now we simply allocate some memory on the host and request that OpenCL™ use this memory directly, passing the flag CL_MEM_USE_HOST_PTR, when creating the buffer. 
 */
	    char * outH = new char[hw.length()+1]; // include \0
	    cl::Buffer outCL(
	        context,
	        CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
	        hw.length()+1,
	        outH,
	        &err);
	    checkErr(err, "Buffer::Buffer()");

/*
OpenCL™ Devices

In OpenCL™ many operations are performed with respect to a given context. For example, buffers (1D regions of memory) and images (2D and 3D regions of memory) allocation are all context operations. But there are also device specific operations. For example, program compilation and kernel execution are on a per device basis, and for these a specific device handle is required. So how do we obtain a handle for a device? We simply query a context for it. OpenCL™ provides the ability to queue information about particular objects, and using the C++ API it comes in the form of object.getInfo<CL_OBJECT_QUERY>(). In the specific case of getting the device from a context:
*/

    cl::vector<cl::Device> devices;
    devices = context.getInfo<CL_CONTEXT_DEVICES>();
    checkErr( devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");

// BEGIN WV

    // the iterator results in an infinite loop, even though devices.size() is 1!
//    for (cl::vector<cl::Device>::iterator iter_=devices.begin();iter_!=devices.end();iter_++) {
//        cl::Device dev=*iter_;
//    }

// The OpenCL C++ Wrapper API Version: 1.1 defines the following fields
    
        cl_device_info info_fields[5]={
            CL_DEVICE_VENDOR,
            CL_DEVICE_PROFILE,
            CL_DEVICE_VERSION,
            CL_DRIVER_VERSION,
        // error: 'CL_DEVICE_OPENCL_C_VERSION' was not declared in this scope
            CL_DEVICE_EXTENSIONS
        };
        std::string info;
        for (int i=0;i<5;i++) {
            err=devices.front().getInfo(info_fields[i],&info);
            checkErr(err, "Device::getInfo()");
            std::cout <<info_fields[i] << "\t"<< info << "\n";
        }
         std::cout << "\n";

// END WV        
/*        
Now that we have the list of associated devices for a context, in this case a single CPU device, we need to load and build the compute program (the program we intend to run on the device, or more generally: devices). The first few lines of the following code simply load the OpenCL™™ device program from disk, convert it to a string, and create a cl::Program::Sources object using the helper constructor. Given an object of type cl::Program::Sources a cl::Program, an object is created and associated with a context, then built for a particular set of devices.
*/

    std::ifstream file("hello_kernel.cl");
    checkErr(file.is_open() ? CL_SUCCESS:-1, "hello_kernel.cl");
 
    std::string prog(
        std::istreambuf_iterator<char>(file),
        (std::istreambuf_iterator<char>())
        );
 
    cl::Program::Sources source(1, std::make_pair(prog.c_str(), prog.length()+1));
 
    cl::Program program(context, source);
    err = program.build(devices,"");
    checkErr(file.is_open() ? CL_SUCCESS : -1, "Program::build()");
/*
A given program can have many entry points, called kernels, and to call one we must build a kernel object. There is assumed to exist a straightforward mapping from kernel names, represented as strings, to a function defined with the __kernel attribute in the compute program. In this case we can build a cl::kernel object, kernel. Kernel arguments are set using the C++ API with kernel.setArg(), which takes the index and value for the particular argument.
*/
    cl::Kernel kernel(program, "hello", &err);
    checkErr(err, "Kernel::Kernel()");
 
    err = kernel.setArg(0, outCL);
    checkErr(err, "Kernel::setArg()");
/*    
Now that the boiler plate code is done, it is time to compute the result (the output buffer with the string “Hello World\n”). All device computations are done using a command queue, which is a virtual interface for the device in question. Each command queue has a one-to-one mapping with a given device; it is created with the associated context using a call to the constructor for the class cl::CommandQueue. Given a cl::CommandQueue queue,kernels can be queued using queue.enqueuNDRangeKernel. This queues a kernel for execution on the associated device. The kernel can be executed on a 1D, 2D, or 3D domain of indexes that execute in parallel, given enough resources. The total number of elements (indexes) in the launch domain is called the global work size; individual elements are known as work-items. Work-items can be grouped into work-groups when communication between work-items is required. Work-groups are defined with a sub-index function (called the local work size), describing the size in each dimension corresponding to the dimensions specified for the global launch domain. There is a lot to consider with respect to kernel launches, and we will cover this in more detail in future tutorials. For now, it is enough to note that for Hello World, each work-item computes a letter in the resulting string; and it is enough to launch hw.length()+1, where hw is the const std::string we defined at the beginning of the program. We need the extra work-item to account for the NULL terminator.
*/
    cl::CommandQueue queue(context, devices[0], 0, &err);
    checkErr(err, "CommandQueue::CommandQueue()");

    cl::Event event;
    err = queue.enqueueNDRangeKernel(
        kernel, 
        cl::NullRange,
        cl::NDRange(hw.length()+1),
        cl::NDRange(1, 1), 
        NULL, 
        &event);
    checkErr(err, "ComamndQueue::enqueueNDRangeKernel()");
/*    
The final argument to the enqueueNDRangeKernel call above was a cl::Event object, which can be used to query the status of the command with which it is associated, (for example, it has completed). It supports the method wait() that blocks until the command has completed. This is required to ensure the kernel has finished execution before reading the result back into host memory with queue.enqueueReadBuffer(). With the compute result back in host memory, it is simply a matter of outputting the result to stdout and exiting the program.
*/
    event.wait();    
    err = queue.enqueueReadBuffer(
        outCL,
        CL_TRUE,
        0,
        hw.length()+1,
        outH);
    checkErr(err, "ComamndQueue::enqueueReadBuffer()");
    std::cout << outH;
    return EXIT_SUCCESS;
}
