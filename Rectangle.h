#include <iostream>

class Rectangle
{
	public:
		Rectangle();
		Rectangle(float length, float breadth);
		~Rectangle();
		void setdim(float length, float breadth);
		float *getdim();
		void findarea();
		float getarea();

	private:
		float _length;
		float _breadth;
		float _area;

};