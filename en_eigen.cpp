#include <iostream>
Double_t h_cross = 1.1054 * 1e-34;
Double_t e_charge = 1.6022 * 1e-19;
Double_t e_mass = 9.1094 * 1e-31;

Double_t eigen_func(Double_t *x, Double_t *par) //V in eV, d in nm
{
	Float_t alp = x[0] * 1e9;
	Float_t V = par[0] * e_charge;
	Float_t d = par[1] * 1e-9;
	Float_t beta = sqrt(2*e_mass*V/(h_cross*h_cross) - alp*alp);
	Double_t f = (alp*sin(alp*d) - beta*cos(alp*d))*1e-9;
	return f;
}

int en_eigen() 
{
	TF1 *f1 = new TF1("Eigen_func", eigen_func, 0, 15, 2);
	f1->SetParameters(10, 0.5);
	f1->SetParNames("volt", "width");
	f1->Draw();
	Float_t x_init = 1;
	while (TMath::Abs(f1->Eval(x_init)) > 0.0001)
	{
		x_init = x_init - f1->Eval(x_init)/f1->Derivative(x_init);
	}
	cout << x_init << endl;
	x_init = 8.0;
	while (TMath::Abs(f1->Eval(x_init)) > 0.0001)
	{
		x_init = x_init - f1->Eval(x_init)/f1->Derivative(x_init);
	}
	cout << x_init << endl;
	x_init = 14.0;
	while (TMath::Abs(f1->Eval(x_init)) > 0.0001)
	{
		x_init = x_init - f1->Eval(x_init)/f1->Derivative(x_init);
	}
	cout << x_init << endl;
	return 0;
}