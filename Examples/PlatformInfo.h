#ifndef __PLATFORM_INFO_H__
#define __PLATFORM_INFO_H__
#include <map>
#include <string>
#include <iostream>
#include "cl.hpp"


class PlatformInfo {
    private:
        std::map<std::string,int> infotbl;
        std::map<std::string,unsigned int> uint_props;
        std::map<std::string,unsigned long> ulong_props;
        std::map<std::string,std::string> string_props;
//        const cl::vector<cl::Platform>& platformList;
    public:
        void show(const cl::vector<cl::Platform>& pl_, int platformIdx);
        void show(const cl::Platform& platform);

        PlatformInfo() ;

};


#endif //  __PLATFORM_INFO_H__
