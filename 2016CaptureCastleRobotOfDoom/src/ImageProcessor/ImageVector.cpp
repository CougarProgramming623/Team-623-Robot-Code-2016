/*
 * ImageVector.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#include "ImageProcessor.h"
#include <math.h>

//Constructors
ImageVector::ImageVector(double x1 , double y1 , double x2 , double y2) {
	pointInital = new Point(x1 , y1);
	pointFinal = new Point(x2 , y2);
	pointMiddle = new Point((pointInital->getX() + pointFinal->getX()) / 2 , (pointInital->getY() + pointFinal->getY()) / 2);
	dx = pointInital->getX() - pointFinal->getX();
	dy = pointInital->getY() - pointFinal->getY();
}

ImageVector::ImageVector(Point* inital , Point* end)
		: ImageVector(inital->getX() , inital->getY() , end->getX() , end->getY()) {
}

ImageVector::ImageVector(Point& inital , Point& end)
		: ImageVector(inital.getX() , inital.getY() , end.getX() , end.getY()) {
}

ImageVector::ImageVector(double x , double y)
		: ImageVector(x , y , 0 , 0) {
}
//End Constructors

double ImageVector::getDX() {
	return dx;
}

double ImageVector::getDY() {
	return dy;
}

double ImageVector::getMagnitude() {
	return sqrt((long double) (dx * dx + dy * dy));
}

//Gets Dot Product
double ImageVector::dot(ImageVector* vector) {
	return dx * vector->dx + dy * vector->dy;
}

//Gets determinant
double ImageVector::det(ImageVector* vector) {
	return dx * vector->dy - dy * vector->dx;
}

Point* ImageVector::getMiddle() {
	return pointMiddle;
}

double ImageVector::getAngleRadian(ImageVector* vector) {
	double value = 2 * M_PI * atan2(det(vector) , dot(vector));
	return value;
}

double ImageVector::getAngleDegree(ImageVector* vector) {
	return getAngleRadian(vector) * 180 / M_PI;
}

//Allows one to set the value of one vector to the current one
ImageVector& ImageVector::operator=(const ImageVector vector) {
	this->dx = vector.dx;
	this->dy = vector.dy;
	this->pointInital = vector.pointInital;
	this->pointFinal = vector.pointFinal;
	this->pointMiddle = vector.pointMiddle;
	return *this;
}
