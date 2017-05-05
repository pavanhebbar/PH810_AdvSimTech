#include <iostream>
#include <cmath>

class Particles
{
	public:
		Particles();
		Particles(double mass, double px, double py);
		void Setm(double mass);
		void Setp(double px, double py);
		void Setp2(double p_t, double theta);
		void Getpvec(double p[2]);
		double Getp_t();
		double Gettheta();
		double Getmass();
		double Getenergy();
		void decay_2(Particles *pa1, Particles *pa2);

	protected:
		double _m0;
		double _px0;
		double _py0;
};

class Lambda: public Particles
{
	public:
		Lambda();
		Lambda(double px, double py);
};

class Neutron: public Particles
{
	public:
		Neutron();
		Neutron(double px, double py);	
};

class Pion: public Particles
{
	public:
		Pion();
		Pion(double px, double py);	
};

class Gamma: public Particles
{
public:
	Gamma();
	Gamma(double px, double py);
	void Rndm_en(double rel_err);	
};