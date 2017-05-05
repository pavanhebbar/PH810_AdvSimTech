# include <iostream>

double pi = 3.1415926;

double func1(double x, double y1, double y2)
{
	return y2;
}

double func2(double x, double y1, double y2)
{
	return -1.0*4.0*pi*pi*y1;
}

double s_func(double x)
{
	return 0.;
}

double k_func(double x)
{
	return 4*pi*pi;
}

void rk4_int(double xmin, double xmax, double y10, double y20, const int n, double y1[n])
{
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	//cout << h << endl;
	double x = xmin;
	y1[0] = y10;
	double y2 = y20;
	for (int i = 1; i < n; i++)
	{
		/*double k1 = func1(x, y[i-1])*h;
		double k2 = func(x[i-1] + h/2, y[i-1] + k1/2)*h;
		double k3 = func(x[i-1] + h/2, y[i-1] + k2/2)*h;
		double k4 = func(x[i-1] + h, y[i-1] + k3)*h;
		y[i] = y[i-1] + (k1 + 2*k2 + 2*k3 + k4)/6;
		x[i] = x[i-1] + h;
		*/
		double k11 = func1(x, y1[i-1], y2)*h;
		double k21 = func2(x, y1[i-1], y2)*h;
		double k12 = func1(x + h/2, y1[i-1] + k11/2, y2 + k21/2)*h;
		double k22 = func2(x + h/2, y1[i-1] + k11/2, y2 + k21/2)*h;
		double k13 = func1(x + h/2., y1[i-1] + k12/2, y2 + k22/2)*h;
		double k23 = func2(x + h/2., y1[i-1] + k12/2, y2 + k22/2)*h;
		double k14 = func1(x + h, y1[i-1] + k13, y2 + k23)*h;
		double k24 = func2(x + h, y1[i-1] + k13, y2 + k23)*h;
		y2 += (k21 + 2*k22 + 2*k23 + k24)/6;
		y1[i] = y1[i-1] + (k11 + 2*k12 + 2*k13 + k14)/6;
		x += h;
	}
}

void numerov(double xmin, double xmax, double y10, double y20, const int n, double y1[])
{
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	//cout << h << endl;
	double x = xmin + h;
	y1[0] = y10;
	y1[1] = y10 + y20*h;
	for (int i = 1; i < n - 1; i++)
	{
		rhs = (s_func(x - h) + s_func(x) + s_func(x+h))*h*h/12.;
		y1[i + 1] = (rhs - (1 + h*h*k_func(x)/12.)*y1[i-1] - (5./6.*h*h*k_func(x) - 2)*y1[i]);
		x += h;
	}
}


int num2diff_eq()
{
	double xmin = 0.0;
	double xmax = 1.0;
	const int n = 100;
	double h = (double)((xmax - xmin)*1.0/(1.0*n));
	double y_rk4[n], y_num[n];
	double x[n];
	x[0] = xmin;
	for (int i = 1; i < n; i++)
	{
		x[i] = x[i-1] + h;
	}
	//euler_int(xmin, xmax, 1, n, y_euler);
	//rk2_int(xmin, xmax, 1, n, y_rk2);
	numerov(xmin, xmax, 0, 1, n, y_num);
	rk4_int(xmin, xmax, 0, 1, n, y_rk4);
	cout << func2(0, 1, 2) << endl;
	//TGraph *g1 = new TGraph(n, x, y_euler);
	TGraph *g2 = new TGraph(n, x, y_num);
	TGraph *g3 = new TGraph(n, x, y_rk4);
	TF1 *f1 = new TF1("f1", "1.0/(2.0*pi)*sin(x)", xmin, xmax);
	TCanvas *c1 = new TCanvas("c1", "Int1", 0, 0, 750, 750);
	//g1->Draw();
	//g2->Draw();
	g3 -> Draw();
	//f1->Draw("SAME");
	return 1;
}