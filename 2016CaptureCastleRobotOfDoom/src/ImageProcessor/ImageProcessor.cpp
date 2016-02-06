/*
 * ImageProcessor.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(Image* image) {
	this->image = image;
}

ImageProcessor::~ImageProcessor() {
	delete image;
}

float ImageProcessor::RGBtoHue(int r , int g , int b) {
	float f_red = r / 255. , f_green = g / 255. , f_blue = b / 255.;
	float color_max = max(max(f_red , f_green) , f_blue);
	float delta = color_max - min(min(f_red , f_green) , f_blue);
	float h = 60;
	if(delta == 0)
		h = 0;
	else if(color_max == f_red)
		h *= fmod((f_green - f_blue) / delta , 6);
	else if(color_max == f_green)
		h *= (f_blue - f_red) / delta + 2;
	else if(color_max == f_green)
		h *= (f_red - f_green) / delta + 4;
	return h / 360.;
}
