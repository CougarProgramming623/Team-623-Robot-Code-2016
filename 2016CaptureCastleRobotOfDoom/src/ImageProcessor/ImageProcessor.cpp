/*
 * ImageProcessor.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(Image* image) {
	center = NULL;
	this->image = image;
	horizontal = new list<ImageVector>();
	vertical = new list<ImageVector>();
}

ImageProcessor::~ImageProcessor() {
	delete image;
	delete horizontal;
	delete vertical;
}

Point ImageProcessor::getCenter() {
	if(center == NULL)
		findCenter();
	return center;
}

double ImageProcessor::getAverage(AVG_ARG arg , int x , int y) {
	double total = 0;
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;
			switch(arg) {
				case ORIGINAL:
					total += image->getPixel(x + i , y + j)->getRGB();
					break;
				case MASKED:
					total += maskedImage[x + i][y + j] ? 0xFFFFFF : 0x000000;
					break;
			}
		}
	}
	return total / 8;
}

void ImageProcessor::applyMask() {
	PixelColor* color = NULL;
	byte h = 0 , v = 0;
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			color = image->getPixel(i , j);
			h = (byte) (color->getHue() * 0xFF) & MASK;
			v = (byte) (color->getValue() * 0xFF);
			maskedImage[i][j] = (h >= 0x10 && v < 0x80);
		}
	}
}

void ImageProcessor::process() {
	list<Point>* points = new list<Point>();
	horizontal->clear();
	vertical->clear();
	ImageVector *horizontal = new ImageVector(1 , 0) , *vertical = new ImageVector(0 , 1);
	for(int i = 1; i < WIDTH - 1; i++) {
		for(int j = 1; j < HEIGHT - 1; j++) {
			double w = .8;
			int avg = (int) (w * getAverage(ORIGINAL , i , j) + (1 - w) * getAverage(MASKED , i , j));
			if(avg > 0xFFFFFF * 8)
				points->push_back(new Point(i , j));
		}
	}
	list<Point>::iterator pointIteratori = points->end();
	int size = points->size();
	int filter = size / 120;
	for(int i = size - 1; i >= 0; i++) {
		list<Point>::iterator pointIteratorj = points->end();
		for(int j = i - 1; j >= 0; j++) {
			if(i % filter == 0 || (*pointIteratorj).equals(*pointIteratori)) {
				points->pop_back();
				break;
			}
			pointIteratori--;
			pointIteratorj--;
		}
	}
	pointIteratori = points->begin();
	for(unsigned int i = 0; i < points->size(); i++) {
		list<Point>::iterator pointIteratorj = points->begin();
		for(unsigned int j = 0; j < points->size(); j++) {
			ImageVector* vector = new ImageVector(*pointIteratori , *pointIteratorj);
			if(fabs(vector->getAngleDegree(horizontal) - 90) < 5) {
				this->vertical->push_back(*vector);
			}
			if(fabs(vector->getAngleDegree(vertical) - 90) < 5) {
				this->horizontal->push_back(*vector);
			}
			pointIteratorj++;
		}
		pointIteratori++;
	}
}

ImageVector& ImageVector::operator=(const ImageVector vector) {
	this->dx = vector.dx;
	this->dy = vector.dy;
	this->pointInital = vector.pointInital;
	this->pointFinal = vector.pointFinal;
	this->pointMiddle = vector.pointMiddle;
	return *this;
}

void ImageProcessor::findCenter() {
	double x , y;
	ImageVector *h , *v1 , *v2;
	bool flag = true;
	for(list<ImageVector>::iterator i = horizontal->begin(); i != horizontal->end(); i++) {
		if(flag || h->getMagnitude() > (*i).getMagnitude()) {
			flag = false;
			h = *i;
		}
	}
}
