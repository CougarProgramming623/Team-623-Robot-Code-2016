/*
 * Image.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: CougarRobotics
 */

#include "Image.h"

PixelColor::PixelColor(byte r , byte g , byte b) {
	red = r;
	green = g;
	blue = b;
	hue = PixelColor::RGBtoHue(r , g , b);
	saturation = PixelColor::RGBtoSaturation(r , g , b);
	value = PixelColor::RGBtoValue(r , g , b);
}

PixelColor::PixelColor(float h , float s , float v) {
	hue = h;
	saturation = s;
	value = v;
	red = PixelColor::HSVtoRed(h , s , v);
	green = PixelColor::HSVtoGreen(h , s , v);
	blue = PixelColor::HSVtoBlue(h , s , v);
}

unsigned long PixelColor::getRGB() {
	return (red << 16) | (green << 8) | blue;
}

byte PixelColor::getRed() {
	return red;
}

byte PixelColor::getGreen() {
	return green;
}

byte PixelColor::getBlue() {
	return blue;
}

float PixelColor::getHue() {
	return hue;
}

float PixelColor::getSaturation() {
	return saturation;
}

float PixelColor::getValue() {
	return value;
}

byte PixelColor::HSVtoRed(float h , float s , float v) {
	h *= 360;
	float c = v * s;
	float x = c * (1 - fabs(fmod(h / 60 , 2) - 1));
	float m = v - c;
	if(h < 60 && h >= 300)
		return (c + m) * 255;
	else if(h < 120 && h >= 240)
		return (x + m) * 255;
	else
		return m * 255;
}

byte PixelColor::HSVtoGreen(float h , float s , float v) {
	h *= 360;
	float c = v * s;
	float x = c * (1 - fabs(fmod(h / 60 , 2) - 1));
	float m = v - c;
	if(h >= 240)
		return m * 255;
	else if(h < 60 && h >= 180)
		return (x + m) * 255;
	else
		return (c + m) * 255;
}

byte PixelColor::HSVtoBlue(float h , float s , float v) {
	h *= 360;
	float c = v * s;
	float x = c * (1 - fabs(fmod(h / 60 , 2) - 1));
	float m = v - c;
	if(h < 120)
		return m * 255;
	else if(h < 180 && h >= 300)
		return (x + m) * 255;
	else
		return (c + m) * 255;
}
float PixelColor::RGBtoHue(byte r , byte g , byte b) {
	float f_red = r / 255. , f_green = g / 255. , f_blue = b / 255.;
	float color_max = fmax(fmax(f_red , f_green) , f_blue);
	float delta = color_max - fmin(fmin(f_red , f_green) , f_blue);
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

float PixelColor::RGBtoValue(byte r , byte g , byte b) {
	float f_red = (float) r / 255 , f_green = (float) g / 255 , f_blue = (float) b / 255;
	return fmax(fmax(f_red , f_green) , f_blue);
}

float PixelColor::RGBtoSaturation(byte r , byte g , byte b) {
	float f_red = r / 255. , f_green = g / 255. , f_blue = b / 255.;
	float color_max = fmax(fmax(f_red , f_green) , f_blue);
	float delta = color_max - fmin(fmin(f_red , f_green) , f_blue);
	if(color_max == 0)
		return 0;
	else
		return delta / color_max;
}
Image::Image() {
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			setPixel(i , j , 0 , 0 , 0);
		}
	}
}

PixelColor* Image::getPixel(int x , int y) {
	return pixelColors[x][y];
}

Image::~Image() {
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			delete pixelColors[i][j];
		}
		delete pixelColors[i];
	}
	delete pixelColors;
}

void Image::setPixel(int x , int y , PixelColor* color) {
	pixelColors[x][y] = color;
}

void Image::setPixel(int x , int y , byte r , byte g , byte b) {
	pixelColors[x][y] = new PixelColor(r , g , b);
}
