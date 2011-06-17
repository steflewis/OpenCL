// A C++ version of the Apple HelloWorld OpenCL example

#include "hello.h";
#include <DeviceInfo.h>

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
#define DATA_SIZE (24*1024) // *1024)
// 1024*1024 gives segmentation fault when using static allocation, because it's on the stack
// 32M is the max because CL_DEVICE_MAX_MEM_ALLOC_SIZE = 128MB for my iMac, and a float is 4 bytes.

int main(void)
{

    cl_int err;                            // error code returned from api calls

 // this array uses stack memory because it's
  // declared inside of a function. 
     // So the size of the stack determines the max array size! 
    //float data[DATA_SIZE];              // original data set given to device
    //float results[DATA_SIZE];           // results returned from device
    unsigned int correct;               // number of correct results returned

    size_t global;                      // global domain size for our calculation
    size_t local;                       // local domain size for our calculation

//    cl_device_id device_id;             // compute device id 
//    cl_context context;                 // compute context
//    cl_command_queue commands;          // compute command queue
//    cl_program program;                 // compute program
//    cl_kernel kernel;                   // compute kernel
    
//    cl_mem input;                       // device memory used for the input array
//    cl_mem output;                      // device memory used for the output array
    
    // Fill our data set with random float values
    //
    float* results=(float*)malloc(sizeof(float)*DATA_SIZE);
    float* data=(float*)malloc(sizeof(float)*DATA_SIZE);
    const unsigned int count = DATA_SIZE;
    for(unsigned int i = 0; i < count; i++)
        data[i] = rand() / (float)RAND_MAX;

// First check the Platform
	cl::vector<cl::Platform> platformList;
	cl::Platform::get(&platformList);
	checkErr(platformList.size() != 0 ? CL_SUCCESS : -1, "cl::Platform::get");
	std::cerr << "Platform number is: " << platformList.size() << std::endl;
	std::string platformVendor;
	platformList[0].getInfo((cl_platform_info) CL_PLATFORM_VENDOR,
			&platformVendor);
	std::cerr << "Platform is by: " << platformVendor << "\n";

// Use the platform info as input for the Context    
	cl_context_properties cprops[3] = { CL_CONTEXT_PLATFORM,
			(cl_context_properties)(platformList[0])(), 0 };
#ifndef CPU
    std::cout << "\nUsing GPU\n";
	cl::Context context(CL_DEVICE_TYPE_GPU, cprops, NULL, NULL, &err); // CPU-only 
#else
    std::cout << "\nUsing CPU\n"; 
    cl::Context context(CL_DEVICE_TYPE_CPU, cprops, NULL, NULL, &err); // CPU-only 
#endif 
    checkErr(err, "Context::Context()");

    cl::vector<cl::Device> devices;
    devices = context.getInfo<CL_CONTEXT_DEVICES>();
    checkErr( devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");

#ifdef DEVINFO
// Get info
    DeviceInfo info;
    info.show(devices.front());
#endif
// Now load the kernel

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
    cl::Kernel kernel(program, "square", &err);
    checkErr(err, "Kernel::Kernel()");
    

/*    
    // Connect to a compute device
    //
    int gpu = 1;
    err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to create a device group!\n");
        return EXIT_FAILURE;
    }
  
    // Create a compute context 
    //
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    if (!context)
    {
        printf("Error: Failed to create a compute context!\n");
        return EXIT_FAILURE;
    }

    // Create a command commands
    //
    commands = clCreateCommandQueue(context, device_id, 0, &err);
    if (!commands)
    {
        printf("Error: Failed to create a command commands!\n");
        return EXIT_FAILURE;
    }

    // Create the compute program from the source buffer
    //
    program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
    if (!program)
    {
        printf("Error: Failed to create compute program!\n");
        return EXIT_FAILURE;
    }

    // Build the program executable
    //
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        printf("Error: Failed to build program executable!\n");
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(1);
    }

    // Create the compute kernel in the program we wish to run
    //
    kernel = clCreateKernel(program, "square", &err);
    if (!kernel || err != CL_SUCCESS)
    {
        printf("Error: Failed to create compute kernel!\n");
        exit(1);
    }
*/

// Create the buffers
/*
   CL_INVALID_HOST_PTR
     if host_ptr is NULL and CL_MEM_USE_HOST_PTR or CL_MEM_COPY_HOST_PTR are set in flags
     or 
     if host_ptr is not NULL but CL_MEM_COPY_HOST_PTR or CL_MEM_USE_HOST_PTR are not set in flags.
   */
        cl::Buffer input(
                context,
                CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//CL_MEM_USE_HOST_PTR ,//  | CL_MEM_ALLOC_HOST_PTR
                sizeof(float) * count,
                data,
                &err);
        checkErr(err, "Buffer::Buffer input()");

        cl::Buffer output(
                context,
                CL_MEM_WRITE_ONLY,
                sizeof(float) * count,
                NULL,
                &err);
        checkErr(err, "Buffer::Buffer output()");
/*
    // Create the input and output arrays in device memory for our calculation
    //
    input = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * count, NULL, NULL);
    output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * count, NULL, NULL);
    if (!input || !output)
    {
        printf("Error: Failed to allocate device memory!\n");
        exit(1);
    }    
*/

// Surprisingly, in C++ it is not required to do queue.enqueueWriteBuffer()

/*        
    // Write our data set into the input array in device memory 
    //
    err = clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, sizeof(float) * count, data, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to write to source array!\n");
        exit(1);
    }
*/

// setArg takes the index of the argument and a value of the same type as the kernel argument 
    err = kernel.setArg(0, input );
    checkErr(err, "Kernel::setArg(0)");

    err = kernel.setArg(1, output);
    checkErr(err, "Kernel::setArg(1)");

    err = kernel.setArg(2, &count);
    checkErr(err, "Kernel::setArg(2)");
/*    
    // Set the arguments to our compute kernel
    //
    err = 0;
    err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to set kernel arguments! %d\n", err);
        exit(1);
    }
*/

    // Get the maximum work group size for executing the kernel on the device
    //
    err = kernel.getWorkGroupInfo( devices[0],(cl_kernel_work_group_info)CL_KERNEL_WORK_GROUP_SIZE,&local);
    global=count;
    checkErr(err, "Kernel::getWorkGroupInfo");

/*
    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to retrieve kernel work group info! %d\n", err);
        exit(1);
    }
*/
// Create the CommandQueue
   cl::CommandQueue queue(context, devices[0], 0, &err);
    checkErr(err, "CommandQueue::CommandQueue()");

// This is optional, in fact it seems to slow down the process 
/*    
  err = queue.enqueueWriteBuffer(
        input,
        CL_TRUE,
        0,
        sizeof(float) * count,
        data);
    checkErr(err, "CommandQueue::enqueueWriteBuffer()");
*/
    
// This is the actual "run" command. The 3 NDranges are
// offset, global and local    
   cl::Event event;
    err = queue.enqueueNDRangeKernel(
        kernel, 
        cl::NullRange,
        cl::NDRange(global),
        cl::NullRange,
//        cl::NDRange(local), 
        NULL, 
        &event);
    checkErr(err, "CommandQueue::enqueueNDRangeKernel()");

    double tstart=wsecond();
    
    event.wait();    

/*
    // Execute the kernel over the entire range of our 1d input data set
    // using the maximum number of work group items for this device
    //
    global = count;
    err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
    if (err)
    {
        printf("Error: Failed to execute kernel!\n");
        return EXIT_FAILURE;
    }

    // Wait for the command commands to get serviced before reading back results
    //
    clFinish(commands);
*/

// Read back the results

    err = queue.enqueueReadBuffer(
        output,
        CL_TRUE,
        0,
        sizeof(float) * count,
        results);
    checkErr(err, "CommandQueue::enqueueReadBuffer()");
double tstop=wsecond();
    
/*    
    // Read back the results from the device to verify the output
    //
    err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(float) * count, results, 0, NULL, NULL );  
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to read output array! %d\n", err);
        exit(1);
    }
*/    
    // Validate our results
    //
    correct = 0;
    for(unsigned int i = 0; i < count; i++)
    {
        if(results[i] == data[i] * data[i])
            correct++;
    }
    
    std::cout << "Computed '"<<correct<<"/"<<count<<"' correct values!\n";
    std::cout << "Total execution time "<<(tstop-tstart)<<" ms\n";
 
/*
    // Print a brief summary detailing the results
    //
    printf("Computed '%d/%d' correct values!\n", correct, count);
    
    // Shutdown and cleanup
    //
    clReleaseMemObject(input);
    clReleaseMemObject(output);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
*/
    free(data);
    return EXIT_SUCCESS;
}

