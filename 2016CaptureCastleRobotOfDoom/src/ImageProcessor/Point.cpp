/*
 * Point.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: CougarRobotics
 */

#include "ImageProcessor.h"

Point::Point(double x , double y) {
	this->x = x;
	this->y = y;
}

Point::Point(Point* point)
		: Point(point->x , point->y) {
}

Point::Point(double point[])
		: Point(point[0] , point[1]) {
}

Point::Point(int point[])
		: Point(point[0] , point[1]) {
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

double Point::distace(Point* point) {
	return sqrt(pow(point->x - x , 2) + pow(point->y - y , 2));
}

bool Point::equals(Point* point) {
	return point->x == x && point->y == y;
}
