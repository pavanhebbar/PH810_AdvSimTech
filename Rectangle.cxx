#include "Rectangle.h"

Rectangle::Rectangle()
{
	_length = 0;
	_breadth = 0;
}

Rectangle::Rectangle(float length, float breadth)
{
	_length = length;
	_breadth = breadth;
}

Rectangle::~Rectangle()
{
}

void Rectangle::setdim(float length, float breadth)
{
	_length = length;
	_breadth = breadth;
}

float *Rectangle::getdim()
{
	float dim[2];
	dim[0] = _length;
	dim[1] = _breadth;
	return dim;
}

void Rectangle::findarea()
{
	_area = _length*_breadth;
}

float Rectangle::getarea()
{
	return _area;
}