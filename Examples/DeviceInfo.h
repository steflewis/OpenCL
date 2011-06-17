#ifndef __DEVICE_INFO_H__
#define __DEVICE_INFO_H__
#include <map>
#include <string>
#include <iostream>
#include "cl.hpp"

enum InfoType {UINT, ULONG, STRING};

class InfoTuple {
    public:
        int infocode;
        InfoType infotype;
    InfoTuple() {};
    InfoTuple(int ic_,InfoType it_) : infocode(ic_), infotype(it_) {};
};

class DeviceInfo {
    private:
        std::map<std::string,InfoTuple> infotbl;
        std::map<std::string,unsigned int> uint_props;
        std::map<std::string,unsigned long> ulong_props;
        std::map<std::string,std::string> string_props;
    public:
        void show(const cl::Device& );

    DeviceInfo() {
        infotbl["CL_DEVICE_VENDOR_ID"]=InfoTuple(CL_DEVICE_VENDOR_ID,UINT);
        infotbl["CL_DEVICE_MAX_COMPUTE_UNITS"]=InfoTuple(CL_DEVICE_MAX_COMPUTE_UNITS,UINT);
        infotbl["CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS"]=InfoTuple(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,UINT);
        //infotbl["CL_DEVICE_MAX_WORK_GROUP_SIZE"]=InfoTuple(CL_DEVICE_MAX_WORK_GROUP_SIZE,UINT);
        //infotbl["CL_DEVICE_MAX_WORK_ITEM_SIZES"]=InfoTuple(CL_DEVICE_MAX_WORK_ITEM_SIZES,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,UINT);
        infotbl["CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE"]=InfoTuple(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,UINT);
        infotbl["CL_DEVICE_MAX_CLOCK_FREQUENCY"]=InfoTuple(CL_DEVICE_MAX_CLOCK_FREQUENCY,UINT);
        infotbl["CL_DEVICE_ADDRESS_BITS"]=InfoTuple(CL_DEVICE_ADDRESS_BITS,UINT);
        infotbl["CL_DEVICE_MAX_READ_IMAGE_ARGS"]=InfoTuple(CL_DEVICE_MAX_READ_IMAGE_ARGS,UINT);
        infotbl["CL_DEVICE_MAX_WRITE_IMAGE_ARGS"]=InfoTuple(CL_DEVICE_MAX_WRITE_IMAGE_ARGS,UINT);
        infotbl["CL_DEVICE_MAX_MEM_ALLOC_SIZE"]=InfoTuple(CL_DEVICE_MAX_MEM_ALLOC_SIZE,ULONG);
        //infotbl["CL_DEVICE_IMAGE2D_MAX_WIDTH"]=InfoTuple(CL_DEVICE_IMAGE2D_MAX_WIDTH,UINT);
        //infotbl["CL_DEVICE_IMAGE2D_MAX_HEIGHT"]=InfoTuple(CL_DEVICE_IMAGE2D_MAX_HEIGHT,UINT);
        //infotbl["CL_DEVICE_IMAGE3D_MAX_WIDTH"]=InfoTuple(CL_DEVICE_IMAGE3D_MAX_WIDTH,UINT);
        //infotbl["CL_DEVICE_IMAGE3D_MAX_HEIGHT"]=InfoTuple(CL_DEVICE_IMAGE3D_MAX_HEIGHT,UINT);
        //infotbl["CL_DEVICE_IMAGE3D_MAX_DEPTH"]=InfoTuple(CL_DEVICE_IMAGE3D_MAX_DEPTH,UINT);
        infotbl["CL_DEVICE_IMAGE_SUPPORT"]=InfoTuple(CL_DEVICE_IMAGE_SUPPORT,UINT);
        //infotbl["CL_DEVICE_MAX_PARAMETER_SIZE"]=InfoTuple(CL_DEVICE_MAX_PARAMETER_SIZE,UINT);
        infotbl["CL_DEVICE_MAX_SAMPLERS"]=InfoTuple(CL_DEVICE_MAX_SAMPLERS,UINT);
        infotbl["CL_DEVICE_MEM_BASE_ADDR_ALIGN"]=InfoTuple(CL_DEVICE_MEM_BASE_ADDR_ALIGN,UINT);
        infotbl["CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE"]=InfoTuple(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,UINT);
        //infotbl["CL_DEVICE_SINGLE_FP_CONFIG"]=InfoTuple(CL_DEVICE_SINGLE_FP_CONFIG,UINT);
        //infotbl["CL_DEVICE_GLOBAL_MEM_CACHE_TYPE"]=InfoTuple(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,UINT);
        infotbl["CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE"]=InfoTuple(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,UINT);
        infotbl["CL_DEVICE_GLOBAL_MEM_CACHE_SIZE"]=InfoTuple(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,ULONG);
        infotbl["CL_DEVICE_GLOBAL_MEM_SIZE"]=InfoTuple(CL_DEVICE_GLOBAL_MEM_SIZE,ULONG);
        infotbl["CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE"]=InfoTuple(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,ULONG);
        infotbl["CL_DEVICE_MAX_CONSTANT_ARGS"]=InfoTuple(CL_DEVICE_MAX_CONSTANT_ARGS,UINT);
        //infotbl["CL_DEVICE_LOCAL_MEM_TYPE"]=InfoTuple(CL_DEVICE_LOCAL_MEM_TYPE,UINT);
        infotbl["CL_DEVICE_LOCAL_MEM_SIZE"]=InfoTuple(CL_DEVICE_LOCAL_MEM_SIZE,ULONG);
        //infotbl["CL_DEVICE_ERROR_CORRECTION_SUPPORT"]=InfoTuple(CL_DEVICE_ERROR_CORRECTION_SUPPORT,UINT);
        //infotbl["CL_DEVICE_PROFILING_TIMER_RESOLUTION"]=InfoTuple(CL_DEVICE_PROFILING_TIMER_RESOLUTION,UINT);
        //infotbl["CL_DEVICE_ENDIAN_LITTLE"]=InfoTuple(CL_DEVICE_ENDIAN_LITTLE,UINT);
        //infotbl["CL_DEVICE_AVAILABLE"]=InfoTuple(CL_DEVICE_AVAILABLE,UINT);
        //infotbl["CL_DEVICE_COMPILER_AVAILABLE"]=InfoTuple(CL_DEVICE_COMPILER_AVAILABLE,UINT);
        //infotbl["CL_DEVICE_EXECUTION_CAPABILITIES"]=InfoTuple(CL_DEVICE_EXECUTION_CAPABILITIES,UINT);
        //infotbl["CL_DEVICE_QUEUE_PROPERTIES"]=InfoTuple(CL_DEVICE_QUEUE_PROPERTIES,UINT);
        infotbl["CL_DEVICE_NAME"]=InfoTuple(CL_DEVICE_NAME,STRING);
        infotbl["CL_DEVICE_VENDOR"]=InfoTuple(CL_DEVICE_VENDOR,STRING);
        infotbl["CL_DRIVER_VERSION"]=InfoTuple(CL_DRIVER_VERSION,STRING);
        infotbl["CL_DEVICE_PROFILE"]=InfoTuple(CL_DEVICE_PROFILE,STRING);
        infotbl["CL_DEVICE_VERSION"]=InfoTuple(CL_DEVICE_VERSION,STRING);
        infotbl["CL_DEVICE_EXTENSIONS"]=InfoTuple(CL_DEVICE_EXTENSIONS,STRING);
        //infotbl["CL_DEVICE_PLATFORM"]=InfoTuple(CL_DEVICE_PLATFORM,UINT);
    };
    unsigned int max_compute_units(const cl::Device&);
    bool isGPU(const cl::Device&);
    bool isCPU(const cl::Device&);
};


#endif //  __DEVICE_INFO_H__
