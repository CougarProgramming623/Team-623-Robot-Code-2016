/*
 * ImageProcessor.h
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_
#define SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_
#include <list>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "image.h"

using namespace std;

//Define Constants!!!
#define MASK 0x40
#define WIDTH 320
#define HEIGHT 240
#define SCALE .5

enum AVG_ARG {
	ORIGINAL, MASKED
};

class Point {
	private:
		double x , y;
	public:
		Point(double , double);
		Point(Point*);
		Point(int[]);
		Point(double[]);
		double getX();
		double getY();
		double distace(Point*);
		bool equals(Point*);
		bool equals(Point);
};

class ImageVector {
	private:
		Point *pointInital , *pointFinal , *pointMiddle;
		double dx , dy;
	public:
		ImageVector& operator=(const ImageVector);
		ImageVector(Point* , Point*);
		ImageVector(Point& , Point&);
		ImageVector(double , double);
		ImageVector(double , double , double , double);
		Point* getMiddle();
		double getMagnitude();
		double getAngleRadian(ImageVector*);
		double getAngleDegree(ImageVector*);
		double dot(ImageVector*);
		double det(ImageVector*);
		double getDX();
		double getDY();
};

class ImageProcessor {
	private:
		Point* center;
		Image* image;
		list<ImageVector>*horizontal , *vertical;
		bool maskedImage[WIDTH][HEIGHT] , processedImage[WIDTH][HEIGHT];
		double getAverage(AVG_ARG , int , int);
	public:
		ImageProcessor(Image* image);
		~ImageProcessor();
		void applyMask();
		void process();
		void findCenter();
		Point getCenter();
};

#endif /* SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_ */
