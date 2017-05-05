#include "Particles.h"

double pi = 3.14159265359;

Particles::Particles()
{
	_m0 = 0;
	_px0 = 0;
	_py0 = 0;
}

Particles::Particles(double mass, double px, double py)
{
	_m0 = mass;
	_px0 = px;
	_py0 = py;
}

void Particles::Setm(double mass)
{
	_m0 = mass;
}

void Particles::Setp(double px, double py)
{
	_px0 = px;
	_py0 = py;
}

void Particles::Setp2(double p_t, double theta)
{
	_px0 = p_t*cos(theta);
	_py0 = p_t*sin(theta);
}

void Particles::Getpvec(double p[2])
{
	p[0] = _px0;
	p[1] = _py0;
}

double Particles::Getp_t()
{
	return sqrt(_px0*_px0 + _py0*_py0);
}

double Particles::Gettheta()
{
	return atan2(_py0, _px0);
}

double Particles::Getmass()
{
	return _m0;
}

double Particles::Getenergy()
{
	return sqrt(_px0*_px0 + _py0*_py0 + _m0*_m0);
}

void Particles::decay_2(Particles *pa1, Particles *pa2)
{
	double m1 = pa1->Getmass();
	double m2 = pa2->Getmass();
	TRandom r1;
	double theta_cm = atan2(_py0, _px0);
	double energy0 = sqrt(_px0*_px0 + _py0*_py0 + _m0*_m0);
	double beta_cm = sqrt((_px0*_px0 + _py0*_py0))/energy0;
	double gamma_cm = 1.0/sqrt(1 - beta_cm*beta_cm);
	double ptotal = sqrt(pow(_m0, 4) + pow(m1, 4) + pow(m2, 4) - 2*_m0*_m0*m1*m1 - 2*_m0*_m0*m2*m2 - 2*m1*m1*m2*m2)/(2*_m0); //In COM frame
	double energy1_cm = sqrt(ptotal*ptotal + m1*m1);
	double energy2_cm = sqrt(ptotal*ptotal + m2*m2);
	r1.SetSeed(0);
	double theta = r1.Uniform(-1*pi, pi);
	double px_cm = ptotal*cos(theta);
	double py_cm = ptotal*sin(theta);
	double py1_inert = py_cm;
	double py2_inert = -1*py_cm;
	double px1_inert = gamma_cm*(px_cm + beta_cm*energy1_cm);
	double px2_inert = gamma_cm*(-1*px_cm + beta_cm*energy2_cm);
	double p1_x = px1_inert*cos(theta_cm) - py1_inert*sin(theta_cm);
	double p2_x = px2_inert*cos(theta_cm) - py2_inert*sin(theta_cm);
	double p1_y = px1_inert*sin(theta_cm) + py1_inert*cos(theta_cm);
	double p2_y = px2_inert*sin(theta_cm) + py2_inert*cos(theta_cm);
	pa1->Setp(p1_x, p1_y);
	pa2->Setp(p2_x, p2_y);

}

Lambda::Lambda()
{
	_m0 = 1115.683;
	_px0 = 0;
	_py0 = 0;
}

Lambda::Lambda(double px, double py)
{
	_m0 = 1115.683;
	_px0 = px;
	_py0 = py;
}

Neutron::Neutron()
{
	_m0 = 939.56563;
	_px0 = 0;
	_py0 = 0;
}

Neutron::Neutron(double px, double py)
{
	_m0 = 939.56563;
	_px0 = px;
	_py0 = py;
}

Pion::Pion()
{
	_m0 = 134.9766;
	_px0 = 0;
	_py0 = 0;
}

Pion::Pion(double px, double py)
{
	_m0 = 134.9766;
	_px0 = px;
	_py0 = py;
}

Gamma::Gamma()
{
	_m0 = 0;
	_px0 = 0;
	_py0 = 0;
}

Gamma::Gamma(double px, double py)
{
	_m0 = 0;
	_px0 = px;
	_py0 = py;
}

void Gamma::Rndm_en(double rel_err)
{
	double e0 = sqrt(_px0*_px0 + _py0*_py0);
	TRandom3 r1;
	r1.SetSeed();
	double dele = r1.Gaus(0, rel_err*e0);
	double delp = dele;
	double deltheta = r1.Uniform(-1*pi, pi);
	_px0 += delp*cos(deltheta);
	_py0 += delp*sin(deltheta);
}