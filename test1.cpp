#include <iostream>

float func1(float xmin, float xmax)
{
	return xmax - xmin;
}

int func2(std::function< float(float, float) > myfunc, float val, float xmin, float xmax)
{
	return val*myfunc(xmin, xmax);
}



int test1()
{
	&func3 = &func2;
	float ans = func3(func1, 2, 4.0, 1.0);
	std::cout << ans << std::endl;
	return 1;
}