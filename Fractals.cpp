#include <iostream>
#include <vector>
#include <cstdlib>

#define __CL_ENABLE_EXCEPTIONS
#include "CL/cl.hpp"

#include "PNG.hpp"
#include "ColorMapping.hpp"

int main(int argc, char *argv[]) {
	try {
		// image dimensions
		size_t width = 1600;
		size_t height = 1200;
		
		// Variables
		double x = 0;  
		double y = 0;
		size_t iterate = 0;
		size_t max_iterate = 1000;
		double xtemp = 0;
		double x0_scaled = 0;
		double y0_scaled = 0;

		// allocate vector of RGB pixels
		std::vector<png::Pixel<png::RGB> > image(width * height);
		//std::cout << "After allocation" << std::endl;
		//
		// TODO: fractal calculation

		// These for loops select the pixel.
		// y0 and x0 will be the scaled coordinates of the pixel.
		// i.e. to be scaled later.
		for(size_t y0 = 0; y0 < height; ++y0){
		  for(size_t x0 = 0; x0 < width; ++x0){

		    double h = 0;
		    x = 0;
		    y = 0;

		    x0_scaled = (double)x0 / (double)width;
		    y0_scaled = (double)y0 / (double)height;

		    iterate = 0;

		    while( ( ( (x*x)+(y*y) ) <= (2*2)) && (iterate < max_iterate) ){
		      xtemp = (x*x) - (y*y) + x0_scaled;
		      y = 2*x*y + y0_scaled;
		      x = xtemp;
		      iterate++;
		    }

		    if (iterate == max_iterate){
		      h = 1;
		    }else{
		      h = (double)iterate / (double)max_iterate;
		    }
		    
		    png::Pixel<png::RGB>& pixel = image[y0*width+x0];		    
		    ColorMapping::HSVtoRGB(h, pixel);
		    //image[y*width+x]=pixel;
		  }
		}
		// write image
		png::Image::writeFile("fractal.png", image, width, height);
	} catch(cl::Error& err) {
		std::cerr << "OpenCL error: " << err.what() << "(" << err.err() <<
			")" << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
