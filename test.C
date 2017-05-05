#include <iostream>

void test2(double arr[10])
{
	for(int i = 0; i < 10; i++)
	{
		arr[i] = i;
	}
}

void test()
{
	double abc_arr[10][10];
	test2(abc_arr[9]);
	cout << abc_arr[9][6] << endl;
}

double get_lmass(const int nx, p_n[nx], p_g1[nx], p_g2[nx])
{

}

void Dalitz_plot(const int nx, p_n[nx], p_g[2*nx])
{
	double m_n = 939.56563;
	double mu_ng[2*nx*nx];
	for(int i = 0; i < nx; i++)
	{
		for(int j = 0; j < 2*nx; j++)
		{

		}
	}
}

void get_mu_ngg(const int nx, p_n[nx][2], p_g[2*nx][2], mu_ng[2*nx*nx], mu_gg[2*nx*nx - nx])
{
	double m_n = 939.56563;
	for(int i = 0; i < nx; i++)
	{
		e_n = sqrt(m_n*m_n + p_n[i][0]*p_n[i][0] + p_n[i][1]*p_n[i][1]);
		for(int j = 0; j < 2*nx; j++)
		{
			e_p = sqrt(p_g[j][0]*p_g[j][0] + p_g[j][1]*p_g[j][1]);
			mu_ng[i*2*nx + j] = sqrt()
		}
	}	
}