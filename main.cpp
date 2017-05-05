#include <iostream>
#include <Rectangle.h>
#include <Rectangle.cxx>

int main()
{
	Rectangle rect1;
	Rectangle rect2(5.5, 10.0);
	rect1->setdim(2.5, 3.2);
	rect2->findarea();
	std::cout << "Rectangle 1 ["<< rect1->getdim()[0] << "," << rect1->getdim()[1] << std::endl;
	std::cout << "Rectangle 2 _area" << rect2->getarea() << std::endl;
}