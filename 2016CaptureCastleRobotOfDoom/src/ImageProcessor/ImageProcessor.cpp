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

//Gets center of the goal on the masked image
Point ImageProcessor::getCenter() {
	if(center == NULL)
		findCenter();
	return center;
}

//Question: What does this method do?
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
					total += maskedImage[x + i][y + j] ? 1 : 0; //Depending on the color of the pixel the masked image makes it white or black
			}
		}
	}
	return total / 8;
}

//Applies the mask to the 2D array
void ImageProcessor::applyMask() {
	PixelColor* color = NULL;
	byte hue = 0 , value = 0;
	for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			color = image->getPixel(i , j);
			hue = (byte) (color->getHue() * 0xFF) & MASK;
			value = (byte) (color->getValue() * 0xFF);
			maskedImage[i][j] = (hue >= 0x10 && value < 0x80);
		}
	}
}

//I need you to walk me through this so that I understand how it works (mainly because I want to know)
void ImageProcessor::process() {
	list<Point>* points = new list<Point>();
	horizontal->clear();
	vertical->clear();
	ImageVector *horizontalVector = new ImageVector(1 , 0) , *verticalVector = new ImageVector(0 , 1);
	for(int i = 1; i < WIDTH - 1; i++) {
		for(int j = 1; j < HEIGHT - 1; j++) {
			double weight = .8;
			int avg = (int) (weight * getAverage(ORIGINAL , i , j) + (1 - weight) * getAverage(MASKED , i , j));
			if(avg > 8)
				points->push_back(new Point(i , j));
		}
	}
	int size = points->size();
	int filter = size / 120;
	list<Point>::iterator pointIteratori = points->end();
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
			if(fabs(vector->getAngleDegree(horizontalVector) - 90) < 5) {
				vertical->push_back(*vector);
			}
			if(fabs(vector->getAngleDegree(verticalVector) - 90) < 5) {
				horizontal->push_back(*vector);
			}
			pointIteratorj++;
		}
		pointIteratori++;
	}
}

void ImageProcessor::findCenter() {
	double x , y;
	ImageVector *h = NULL , *v1 = NULL , *v2 = NULL;
	Point *ph , *pv1 , *pv2;
	bool flag = true;
	for(list<ImageVector>::iterator i = horizontal->begin(); i != horizontal->end(); i++) {
		if(flag || h->getMagnitude() < (*i).getMagnitude()) {
			flag = false;
			*h = *i;
		}
	}
	ph = h->getMiddle();
	flag = true;
	for(list<ImageVector>::iterator i = horizontal->begin(); i != horizontal->end(); i++) {
		if(ph->distace((*i).getMiddle()) < 100 * SCALE) {
			if(flag || v1->getMagnitude() < (*i).getMagnitude()) {
				flag = false;
				*v1 = *i;
			}
		}
	}
	pv1 = v1->getMiddle();
	double d = h->getMagnitude();
	flag = true;
	for(list<ImageVector>::iterator i = horizontal->begin(); i != horizontal->end(); i++) {
		if(ph->distace((*i).getMiddle()) < 100 * SCALE) {
			if(fabs(pv1->getX() - (*i).getMiddle()->getX()) > d && ph->distace((*i).getMiddle()) < 120 * SCALE) {
				if(flag || v2->getMagnitude() < (*i).getMagnitude()) {
					flag = false;
					*v2 = *i;
				}
			}
		}
	}
	pv2 = v2->getMiddle();
	x = pv1->getX() + pv2->getX();
	y = pv1->getY() + pv2->getY();
	center = new Point(x / 2 , y / 2);
}
