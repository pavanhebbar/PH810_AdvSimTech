#include <iostream>

class Integration
{
	public:
		Integration();
		Integration(float xmin, float xmax, int nx);
		Integration(float xmin, float xmax, float ymin, float ymax, int nx, int ny);
		void Setxrange(float xmin, float xmax);
		float Getxmin();
		float Getxmax();
		void Setyrange(float ymin, float ymax);
		float Getymin();
		float Getymax();
		void Setnx(int nx);
		void Setny(int ny);
		int Getnx();
		int Getny();
		float TrapInt1D(std::function< float(float) > myfunc1);
		float TrapInt2D(std::function< float(float, float) > myfunc2);
		float SimpInt1D(std::function< float(float) > myfunc1);
		float SimpInt2D(std::function< float(float, float) > myfunc2);
		float RombInt1D(std::function< float(float) > myfunc1, int order, int num = 1);
		float GaussQInt1D(std::function< float(float) > myfunc1);

	private:
		float _xmin, _xmax;
		float _ymin, _ymax;
		int _nx, _ny;
};