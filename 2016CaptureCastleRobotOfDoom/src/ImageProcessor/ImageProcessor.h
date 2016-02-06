/*
 * ImageProcessor.h
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#ifndef SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_
#define SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_
//Define Constants!!!
#define MASK 0x40
#define WIDTH 320
#define HEIGHT 240
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "image.h"

using namespace std;

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
};

class ImageVector {
	private:
		Point *pointInital , *pointFinal , *pointMiddle;
		double dx , dy;
	public:
		ImageVector(Point* , Point*);
		ImageVector(double , double);
		ImageVector(double , double , double , double);
		double getMagnitude();
		Point* getMiddle();
		double getAngleRadian(ImageVector*);
		double getAngleDegree(ImageVector*);
		double dot(ImageVector*);
		double det(ImageVector*);
		double getDX();
		double getDY();
};

class ImageProcessor {
	private:
		Image* image;
		bool maskedImage[320][240] , processedImage[320][240];
		vector<ImageVector>horizontal , vertical;
		double getAverage();
	public:
		ImageProcessor(Image* image);
		~ImageProcessor();
		void applyMask();
		void process();
		void findCenter();
		float RGBtoHue(int , int , int);
};

#endif /* SRC_SUBSYSTEMS_IMAGEPROCESSOR_H_ */
