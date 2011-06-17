#ifndef COLORMAPPING_HPP
#define COLORMAPPING_HPP

#include <sstream>
#include <stdexcept>

#include "PNG.hpp"

class ColorMapping {
	public:
		// h, s and v have to be normalized to [0, 1]
		static inline void HSVtoRGB(double h, double s, double v,
			png::Pixel<png::RGB>& rgb) {

#ifdef DEBUG
			if(h < 0 || h > 1) {
				std::stringstream strm;
				strm << "ColorMapping::HSVtoRGB(): invalid value for h: " << h;
				throw std::runtime_error(strm.str().c_str());
			}

			if(s < 0 || s > 1) {
				std::stringstream strm;
				strm << "ColorMapping::HSVtoRGB(): invalid value for s: " << s;
				throw std::runtime_error(strm.str().c_str());
			}

			if(v < 0 || v > 1) {
				std::stringstream strm;
				strm << "ColorMapping::HSVtoRGB(): invalid value for v: " << v;
				throw std::runtime_error(strm.str().c_str());
			}
#else
			if(h < 0)
				h = 0;

			if(h > 1)
				h = 1;

			if(s < 0)
				s = 0;

			if(s > 1)
				s = 1;

			if(v < 0)
				v = 0;

			if(v > 1)
				v = 1;
#endif // DEBUG

			if(h == 0) {
				rgb.red() = 0;
				rgb.green() = 0;
				rgb.blue() = 0;

				return;
			}

			h = h * 6;

			// clamp h
			if(h == 6)
				h = 0;

			unsigned int i = h;
			double f = h - i;
			double p = v * (1 - s);
			double q = v * (1 - s * f);
			double t = v * (1 - s * (1 - f));


			double r, g, b;

			switch(i) {
				case 0:	r = v;
						g = t;
						b = p;
						break;

				case 1:	r = q;
						g = v;
						b = p;
						break;

				case 2:	r = p;
						g = v;
						b = t;
						break;

				case 3:	r = p;
						g = q;
						b = v;
						break;

				case 4:	r = t;
						g = p;
						b = v;
						break;

				case 5:	r = v;
						g = p;
						b = q;
						break;

				default:
#ifdef DEBUG
					std::stringstream strm;
					strm << "ColorMapping::HSVtoRGB(): failed to convert " <<
						"colors";

					throw std::runtime_error(strm.str().c_str());
#endif
					r = 0;
					g = 0;
					b = 0;
			}

			rgb.red() = r * 255;
			rgb.green() = g * 255;
			rgb.blue() = b * 255;
		}

		static inline void HSVtoRGB(double h, png::Pixel<png::RGB>& rgb) {
			return HSVtoRGB(h, 1.0, 1.0, rgb);
		}
};

#endif // COLORMAPPING_HPP
