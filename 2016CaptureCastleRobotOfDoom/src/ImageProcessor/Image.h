/*
 * Image.h
 *
 *  Created on: Feb 7, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_IMAGEPROCESSOR_IMAGE_H_
#define SRC_IMAGEPROCESSOR_IMAGE_H_

#include <string.h>
#include <math.h>

using namespace std;

typedef unsigned char byte;

#define WIDTH 320
#define HEIGHT 240

class PixelColor {
	private:
		byte red , green , blue;
		float hue , saturation , value;
		static float RGBtoHue(byte , byte , byte);
		static float RGBtoSaturation(byte , byte , byte);
		static float RGBtoValue(byte , byte , byte);
		static byte HSVtoRed(float , float , float);
		static byte HSVtoGreen(float , float , float);
		static byte HSVtoBlue(float , float , float);
	public:
		PixelColor(byte , byte , byte);
		PixelColor(float , float , float);
		byte getRed();
		byte getGreen();
		byte getBlue();
		unsigned long getRGB();
		float getHue();
		float getSaturation();
		float getValue();
};

class Image {
	private:
		PixelColor* pixelColors[WIDTH][HEIGHT];
	public:
		Image();
		~Image();
		void setPixel(int , int , byte , byte , byte);
		void setPixel(int , int , PixelColor*);
		PixelColor* getPixel(int , int);
};

#endif /* SRC_IMAGEPROCESSOR_IMAGE_H_ */
