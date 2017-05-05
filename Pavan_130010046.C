#include "Particles.cxx"

void gen_lambda(const int nx, Particles pa[nx])
{
	TRandom r1;
	for (int i = 0; i < nx; i++)
	{
		double p_t = r1.Exp(1000);             //tau = 1 GeV/c
		double eta = r1.Gaus();           //mu = 0, sigma = 1
		double theta = 2*atan(exp(-1*eta));
		pa[i].Setp2(p_t, theta);
	}
}

void get_mu2(const int nx, Particles pa1[nx], Particles pa2[nx], double mu[nx])  //Rest mass of all pa1's are same and so on
{
	double m1 = pa1[0].Getmass();
	double m2 = pa2[0].Getmass();
	double p1[2], p2[2];
	for(int i = 0; i < nx; i++)
	{
		double e1 = pa1[i].Getenergy();
		double e2 = pa2[i].Getenergy();
		pa1[i].Getpvec(p1);
		pa2[i].Getpvec(p2);
		mu[i] = (m1*m1 + m2*m2 + 2*(e1*e2 - p1[0]*p2[0] - p1[1]*p2[1]));
	}
}

double get_lmass(const int nx, Particles pa1[nx], Particles pa2[nx], Particles pa3[nx])
{
	double mass[nx];
	double sum = 0.;
	double p_1[2], p_2[2], p_3[3], p_l[2];
	double p4[4];
	for (int i = 0; i < nx; i++)
	{
		pa1[i].Getpvec(p_1);
		pa2[i].Getpvec(p_2);
		pa3[i].Getpvec(p_3);
		p_l[0] = p_1[0] + p_2[0] + p_3[0];
		p_l[1] = p_1[1] + p_2[1] + p_3[1];
		double pl_t = sqrt(p_l[0]*p_l[0] + p_l[1]*p_l[1]);
		double en_t = pa1[i].Getenergy() + pa2[i].Getenergy() + pa3[i].Getenergy();
		mass[i] = sqrt(en_t*en_t - pl_t*pl_t);
		sum += mass[i];
	}
	return sum/nx;	
}

void get_mu_ngg(const int nx, double p_n[nx][2], double p_g[2*nx][2], double mu_ng[2*nx*nx])
{
	double m_n = 939.56563;
	for(int i = 0; i < nx; i++)
	{
		double e_n = sqrt(m_n*m_n + p_n[i][0]*p_n[i][0] + p_n[i][1]*p_n[i][1]);
		for(int j = 0; j < 2*nx; j++)
		{
			double e_p = sqrt(p_g[j][0]*p_g[j][0] + p_g[j][1]*p_g[j][1]);
			mu_ng[i*2*nx +j] = sqrt(m_n*m_n + 2*(e_p*e_n - p_n[i][0]*p_g[j][0] - p_n[i][1]*p_g[j][1]));
		}
	}
}

void Dalitz_plot(const int nx, double mu_ng[2*nx*nx])   //not getting right result
{
	TCanvas *c3 = new TCanvas("ng1_ng2", "Dalitz plot1", 0, 0, 750, 750);
	TGraph *g3 = new TGraph();
	g3->SetTitle("Graph of m_{n#gamma_{1}} v/s m_{n#gamma_{2}}; m_{n#gamma_{1}} [MeV/c^2]; m_{n#gamma_{2}} [MeV/c^2]"); 
	int count = 0;
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < 2*nx; j++)
		{
			for (int k = 0; k < 2*nx; k++)
			{
				if (j != k)
				{
					g3->SetPoint(count, mu_ng[i*2*nx + j]*mu_ng[i*2*nx + j], mu_ng[i*2*nx + k]*mu_ng[i*2*nx + k]);
					count++;
				}
			}
		}
	}
	g3->Draw("ap*");
}


void Pavan_130010046()
{
	const int nx = 10000;
	Lambda lmd[nx];
	Neutron neut[nx];
	Pion p0[nx];
	Gamma ph1[nx], ph2[nx];
	double mu1[nx], mu2[nx];
	//double mu_ng[2*nx*nx]; 
	gen_lambda(nx, lmd);
	double p_n[nx][2], p_g[2*nx][2];
	for(int i = 0; i < nx; i++)
	{
		lmd[i].decay_2(&neut[i], &p0[i]);
		p0[i].decay_2(&ph1[i], &ph2[i]);
		ph1[i].Rndm_en(0.05);
		ph2[i].Rndm_en(0.05);
		neut[i].Getpvec(p_n[i]);
		ph1[i].Getpvec(p_g[2*i]);
		ph2[i].Getpvec(p_g[2*i + 1]);
	}
	double lambda_mass = get_lmass(nx, neut, ph1, ph2);
	cout << "Reconstructed mass = " << lambda_mass << endl;
	//get_mu_ngg(nx, p_n, p_g, mu_ng);
	//Dalitz_plot(nx, mu_ng);
	get_mu2(nx, neut, ph1, mu1);
	get_mu2(nx, neut, ph2, mu2);
	TCanvas *c1 = new TCanvas("ng1_ng2", "Dalitz plot1", 0, 0, 750, 750);
	TGraph *g1 = new TGraph(nx, mu1, mu2);
	g1->SetTitle("Graph of m_{n#gamma_{2}}^{2} v/s m_{n#gamma_{1}}^{2}; m_{n#gamma_{1}}^{2} [MeV/c^2]; m_{n#gamma_{2}}^{2} [MeV/c^2]"); 
	g1->Draw("ap*");
	get_mu2(nx, neut, ph1, mu1);
	get_mu2(nx, ph1, ph2, mu2);
	TCanvas *c2 = new TCanvas("ng1_g1g2", "Dalitz plot2", 0, 0, 750, 750);
	TGraph *g2 = new TGraph(nx, mu1, mu2);
	g2->SetTitle("Graph of m_{#gamma_{1}#gamma_{1}}^{2} v/s m_{n#gamma_{2}}^{2}; m_{n#gamma_{1}}^{2} [MeV/c^2]; m_{#gamma_{1}#gamma_{2}}^{2} [MeV/c^2]"); 
	g2->Draw("ap*");

}