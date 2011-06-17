// http://developer.amd.com/gpu/amdappsdk/documentation/pages/TutorialOpenCL.aspx

/*
   Finally, to make the program complete an implementation for the device program (hello_kernel.cl), requires defining the external entry point, hello. The kernel implementation is straightforward: it calculates a unique index as a function of the launch domain using get_global_id(), it uses it as an index into the string, hw, then writes its value to the output array, out.
*/
#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
__constant char hw[] = "Hello World\n";

__kernel void hello(__global char * out)
{
    size_t tid = get_global_id(0);
    out[tid] = hw[tid];
}

/*
For robustness, it would make sense to check that the thread id (tid) is not out of range of the hw; for now, we assume that the corresponding call to queue.enqueueNDRangeKernel() is correct.
*/
