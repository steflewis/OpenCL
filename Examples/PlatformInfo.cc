#include "PlatformInfo.h"

PlatformInfo::PlatformInfo() {
    	    infotbl["CL_PLATFORM_PROFILE"]=CL_PLATFORM_PROFILE;
    	    infotbl["CL_PLATFORM_VERSION"]=CL_PLATFORM_VERSION ;
    	    infotbl["CL_PLATFORM_NAME"]=CL_PLATFORM_NAME ;
    	    infotbl["CL_PLATFORM_VENDOR"]=CL_PLATFORM_VENDOR ;
    	    infotbl["CL_PLATFORM_EXTENSIONS"]=CL_PLATFORM_EXTENSIONS ;
        };

void PlatformInfo::show(const cl::vector<cl::Platform>& platformList, int platformIdx) {
	cl_int err;
    std::cout << "\nPlatform Info:"<< std::endl;

    for (std::map<std::string,int>::iterator iter_=infotbl.begin(); iter_!=infotbl.end();iter_++) {
        std::string infostr = (*iter_).first;
        int infocode=(*iter_).second;
        const cl::Platform& platform=platformList[platformIdx];

            std::string info;
            err=platform.getInfo(infocode,&info);
            string_props[infostr]=info;
            std::cout <<infostr << "\t"<< info << "\n";
        if (err != CL_SUCCESS && err!=CL_TRUE) {
            std::cerr << "ERROR: " << infostr <<" ["<< infocode  <<"]"<< " (" << err << ")" << std::endl;
//            exit( EXIT_FAILURE);
        }
    }
    std::cout << std::endl;
  
}

void PlatformInfo::show(const cl::Platform& platform) {
	cl_int err;
    std::cout << "\nPlatform Info:"<< std::endl;

    for (std::map<std::string,int>::iterator iter_=infotbl.begin(); iter_!=infotbl.end();iter_++) {
        std::string infostr = (*iter_).first;
        int infocode=(*iter_).second;

            std::string info;
            err=platform.getInfo(infocode,&info);
            string_props[infostr]=info;
            std::cout <<infostr << "\t"<< info << "\n";
        if (err != CL_SUCCESS && err!=CL_TRUE) {
            std::cerr << "ERROR: " << infostr <<" ["<< infocode  <<"]"<< " (" << err << ")" << std::endl;
//            exit( EXIT_FAILURE);
        }
    }
    std::cout << std::endl;

}

