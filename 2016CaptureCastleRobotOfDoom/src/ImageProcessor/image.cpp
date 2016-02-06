/*
 Christopher Ginac

 image.cpp
 */

#include <stdlib.h>
#include <iostream>
#include "image.h"
#include <cmath>
using namespace std;

Image::Image()
/* Creates an Image 0x0 */
{
	ROWS = 0;
	COLUMNS = 0;
	GRAY_LEVELS = 0;

	pixelVal = NULL;
}

Image::Image(int numRows , int numCols , int grayLevels)
/* Creates an Image of numRows x numCols and creates the arrays for it*/
{

	ROWS = numRows;
	COLUMNS = numCols;
	GRAY_LEVELS = grayLevels;

	pixelVal = new int *[ROWS];
	for(int i = 0; i < ROWS; i++) {
		pixelVal[i] = new int[COLUMNS];
		for(int j = 0; j < COLUMNS; j++)
			pixelVal[i][j] = 0;
	}
}

Image::~Image()
/*destroy image*/
{
	ROWS = 0;
	COLUMNS = 0;
	GRAY_LEVELS = 0;

	for(int i = 0; i < ROWS; i++)
		delete pixelVal[ROWS];

	delete pixelVal;
}

Image::Image(const Image& oldImage)
/*copies oldImage into new Image object*/
{
	ROWS = oldImage.ROWS;
	COLUMNS = oldImage.COLUMNS;
	GRAY_LEVELS = oldImage.GRAY_LEVELS;

	pixelVal = new int*[ROWS];
	for(int i = 0; i < ROWS; i++) {
		pixelVal[i] = new int[COLUMNS];
		for(int j = 0; j < COLUMNS; j++)
			pixelVal[i][j] = oldImage.pixelVal[i][j];
	}
}

void Image::operator=(const Image& oldImage)
/*copies oldImage into whatever you = it to*/
{
	ROWS = oldImage.ROWS;
	COLUMNS = oldImage.COLUMNS;
	GRAY_LEVELS = oldImage.GRAY_LEVELS;

	pixelVal = new int*[ROWS];
	for(int i = 0; i < ROWS; i++) {
		pixelVal[i] = new int[COLUMNS];
		for(int j = 0; j < COLUMNS; j++)
			pixelVal[i][j] = oldImage.pixelVal[i][j];
	}
}

void Image::setImageInfo(int numRows , int numCols , int maxVal)
/*sets the number of rows, columns and graylevels*/
{
	ROWS = numRows;
	COLUMNS = numCols;
	GRAY_LEVELS = maxVal;
}

void Image::getImageInfo(int &numRows , int &numCols , int &maxVal)
/*returns the number of rows, columns and gray levels*/
{
	numRows = ROWS;
	numCols = COLUMNS;
	maxVal = GRAY_LEVELS;
}

int Image::getPixelVal(int row , int col)
/*returns the gray value of a specific pixel*/
{
	return pixelVal[row][col];
}

void Image::setPixelVal(int row , int col , int value)
/*sets the gray value of a specific pixel*/
{
	pixelVal[row][col] = value;
}

bool Image::inBounds(int row , int col)
/*checks to see if a pixel is within the image, returns true or false*/
{
	if(row >= ROWS || row < 0 || col >= COLUMNS || col < 0)
		return false;
	//else
	return true;
}

void Image::getSubImage(int upperLeftRow , int upperLeftCol , int lowerRightRow , int lowerRightCol , Image& oldImage)
/*Pulls a sub image out of oldImage based on users values, and then stores it
 in oldImage*/
{
	int width , height;

	width = lowerRightCol - upperLeftCol;
	height = lowerRightRow - upperLeftRow;

	Image tempImage(height , width , GRAY_LEVELS);

	for(int i = upperLeftRow; i < lowerRightRow; i++) {
		for(int j = upperLeftCol; j < lowerRightCol; j++)
			tempImage.pixelVal[i - upperLeftRow][j - upperLeftCol] = oldImage.pixelVal[i][j];
	}

	oldImage = tempImage;
}

int Image::meanGray()
/*returns the mean gray levels of the Image*/
{
	int totalGray = 0;

	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLUMNS; j++)
			totalGray += pixelVal[i][j];
	}

	int cells = COLUMNS * ROWS;

	return (totalGray / cells);
}

void Image::enlargeImage(int value , Image& oldImage)
/*enlarges Image and stores it in tempImage, resizes oldImage and stores the 
 larger image in oldImage*/
{
	int rows , cols , gray;
	int pixel;
	int enlargeRow , enlargeCol;

	rows = oldImage.ROWS * value;
	cols = oldImage.COLUMNS * value;
	gray = oldImage.GRAY_LEVELS;

	Image tempImage(rows , cols , gray);

	for(int i = 0; i < oldImage.ROWS; i++) {
		for(int j = 0; j < oldImage.COLUMNS; j++) {
			pixel = oldImage.pixelVal[i][j];
			enlargeRow = i * value;
			enlargeCol = j * value;
			for(int c = enlargeRow; c < (enlargeRow + value); c++) {
				for(int d = enlargeCol; d < (enlargeCol + value); d++) {
					tempImage.pixelVal[c][d] = pixel;
				}
			}
		}
	}

	oldImage = tempImage;
}

void Image::shrinkImage(int value , Image& oldImage)
/*Shrinks image as storing it in tempImage, resizes oldImage, and stores it in
 oldImage*/
{
	int rows , cols , gray;

	rows = oldImage.ROWS / value;
	cols = oldImage.COLUMNS / value;
	gray = oldImage.GRAY_LEVELS;

	Image tempImage(rows , cols , gray);

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++)
			tempImage.pixelVal[i][j] = oldImage.pixelVal[i * value][j * value];
	}
	oldImage = tempImage;
}

void Image::reflectImage(bool flag , Image& oldImage)
/*Reflects the Image based on users input*/
{
	int rows = oldImage.ROWS;
	int cols = oldImage.COLUMNS;
	Image tempImage(oldImage);
	if(flag == true) //horizontal reflection
	{
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++)
				tempImage.pixelVal[rows - (i + 1)][j] = oldImage.pixelVal[i][j];
		}
	}
	else //vertical reflection
	{
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++)
				tempImage.pixelVal[i][cols - (j + 1)] = oldImage.pixelVal[i][j];
		}
	}

	oldImage = tempImage;
}

void Image::translateImage(int value , Image& oldImage)
/*translates image down and right based on user value*/
{
	int rows = oldImage.ROWS;
	int cols = oldImage.COLUMNS;
	Image tempImage(ROWS , COLUMNS , GRAY_LEVELS);

	for(int i = 0; i < (rows - value); i++) {
		for(int j = 0; j < (cols - value); j++)
			tempImage.pixelVal[i + value][j + value] = oldImage.pixelVal[i][j];
	}

	oldImage = tempImage;
}

void Image::rotateImage(int theta , Image& oldImage)
/*based on users input and rotates it around the center of the image.*/
{
	int r0 , c0;
	int r1 , c1;
	int rows , cols;
	rows = oldImage.ROWS;
	cols = oldImage.COLUMNS;
	Image tempImage(rows , cols , oldImage.GRAY_LEVELS);

	float rads = (theta * 3.14159265) / 180.0;

	r0 = rows / 2;
	c0 = cols / 2;

	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			r1 = (int) (r0 + ((r - r0) * cos(rads)) - ((c - c0) * sin(rads)));
			c1 = (int) (c0 + ((r - r0) * sin(rads)) + ((c - c0) * cos(rads)));

			if(inBounds(r1 , c1)) {
				tempImage.pixelVal[r1][c1] = oldImage.pixelVal[r][c];
			}
		}
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(tempImage.pixelVal[i][j] == 0)
				tempImage.pixelVal[i][j] = tempImage.pixelVal[i][j + 1];
		}
	}
	oldImage = tempImage;
}

Image Image::operator+(const Image &oldImage)
/*adds images together, half one image, half the other*/
{
	Image tempImage(oldImage);

	int rows , cols;
	rows = oldImage.ROWS;
	cols = oldImage.COLUMNS;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++)
			tempImage.pixelVal[i][j] = (pixelVal[i][j] + oldImage.pixelVal[i][j]) / 2;
	}

	return tempImage;
}

Image Image::operator-(const Image& oldImage)
/*subtracts images from each other*/
{
	Image tempImage(oldImage);

	int rows , cols;
	rows = oldImage.ROWS;
	cols = oldImage.COLUMNS;
	int tempGray = 0;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {

			tempGray = abs(pixelVal[i][j] - oldImage.pixelVal[i][j]);
			if(tempGray < 35) // accounts for sensor flux
				tempGray = 0;
			tempImage.pixelVal[i][j] = tempGray;
		}

	}

	return tempImage;
}

void Image::negateImage(Image& oldImage)
/*negates image*/
{
	Image tempImage(ROWS , COLUMNS , GRAY_LEVELS);

	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < GRAY_LEVELS; j++)
			tempImage.pixelVal[i][j] = 0xFF - pixelVal[i][j];
	}

	oldImage = tempImage;
}
