#include <iostream>

double lj_pot(double x)
{
	return (double)(1.0/pow(x, 12) - 10.0/pow(x, 6));
}

double har_pot(double x)
{
	return (double)(x*x*0.5);
}

void normalize(double dx, const int nx, double phi[nx])
{
	double sum = 0;
	for (int i = 0; i < nx; i++)
	{
		sum += phi[i]*phi[i]*dx;
	}
	for (int i = 0; i < nx; i++)
	{
		phi[i] = phi[i]/sqrt(sum);
	}
}

double cal_energy(double dx, const int nx, double phi[nx]) //xmin = 0, xmax can be calculated from nx and dx
{
	double energy = dx*phi[0]*har_pot(0.5*dx)*phi[0] - dx*phi[0]*0.5*(phi[2] - 2*phi[1] + phi[0])/(dx*dx);
	double sum = dx*phi[0]*phi[0];
	double x;
	for (int i = 1; i < nx-1; i++)
	{
		x = (i*1.0 + 0.5)*dx;                                               //phi shd be normalized
		energy += dx*phi[i]*lj_pot(x)*phi[i] - dx*phi[i]*0.5*(phi[i+1] - 2*phi[i] + phi[i-1])/(dx*dx);
		sum += phi[i]*phi[i]*dx;
	}
	energy += dx*phi[nx-1]*har_pot((nx-0.5)*dx)*phi[nx-1] - dx*phi[nx-1]*0.5*(phi[nx-1] - 2*phi[nx-2] + phi[nx-3])/(dx*dx);
	sum += phi[nx-1]*phi[nx-1]*dx;
	return energy/sum;
}

double en_change(double dx, double phi[], int n, double phin_old) //phi_old must be normalized
{
	double x = (n*1.0 + 0.5)*dx;
	energy_ch = dx*lj_pot(x)*(phi[n]*phi[n] - phin_old*phin_old) - dx*0.5/(dx*dx)*((phi[n-1] + phi[n+1] - 2*(phin_old + phi[n]))*(phi[n] - phin_old));
	new_sum = 1.0 + (phi[n]*phi[n] + phin_old*phin_old);
	return energy_ch/new_sum;
}

void init(double dx, const int nx, double phi[nx])
{
	for (int i = 2; i < nx; i++)
	{
		double xx = (i + 0.5)*dx;
		phi[i] = 10*xx - xx*xx;
	}
	//phi[0] = phi[1] = phi[2] = 0.0;
	normalize(dx, nx, phi);
}

void getphi(double dx, const int nx, double phi[nx], double dphi, int niter)
{
	TRandom rr1;
	TRandom rr2;
	for(int i = 0; i < niter; i++)
	{
		double energy_old = cal_energy(dx, nx, phi);
		int n = 1 + rr1.Integer(nx-1);
		double phin_old = phi[n];
		phi[n] += (rr1.Rndm() - 0.5)*2*dphi;
		double energy_new = cal_energy(dx, nx, phi);
		if ((energy_new) > (energy_old))
		{
			phi[n] = phin_old;
		}
		normalize(dx, nx, phi);
	}
}

int var_prog(int niter = 1000000)
{
	const int nx = 100;
	double phi[nx];
	double psi[nx-1];
	double dx = 0.2;
	init(dx, nx, phi);
	double xx[nx-1];

	getphi(dx, nx, phi, 0.001, niter);

	for(int i = 0; i < nx-1; i++)
	{
		xx[i] = (i*1.0 + 0.5)*dx;
		cout << xx[i] << " " << phi[i] << endl;
		psi[i] = phi[i];
	}
	TGraph *g1 = new TGraph(nx-1, xx, psi);
	g1->Draw();
	cout << cal_energy(dx, nx, phi) << endl;
	return 1;
}