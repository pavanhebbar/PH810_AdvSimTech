#include "Integration.cxx"

float c_func(float w)
{
	return (float)(cos(3.141 * w*w/2));
}

float s_func(float w)
{
	return (float)(sin(3.141*w*w/2));
}

float test_func(float x)
{
	return sin(x);
}

Double_t intensity_func_v(Double_t *v, Double_t *par)
{
	float v_1 = (float)(v[0]);
	Integration c_int(0, v_1, 100);
	Integration s_int(0, v_1, 100);
	float c_v = c_int.SimpInt1D(c_func);
	float s_v = s_int.SimpInt1D(s_func);
	Double_t intensity;
	intensity = 0.5*((c_v + 0.5)*(c_v + 0.5) + (s_v + 0.5)*(s_v + 0.5));
	return intensity;	
}

Double_t intensity_func_d2(Double_t *x, Double_t *par)
{
	Double_t h = par[0];
	Double_t d1 = par[1];
	Double_t lambda = par[2];
	Double_t d2 = x[0];
	Double_t v = (float)(h*sqrt(2*(d1 + d2)/(lambda*d1*d2)));
	Double_t par1[0];
	Double_t intensity = intensity_func_v(&v, par1);
	return intensity;
}

int pavan_130010046()
{
	Integration test1(0, 3.141, 100);
	float testres = test1.SimpInt1D(test_func);
	if (abs(testres - 2) > 0.01)
	{
		cout << "Error in intgration function";
		return 0;
	}
	TCanvas *c1 = new TCanvas("c1", "c1", 750, 750);
	TF1 *f1 = new TF1("I/I0 v/s v", intensity_func_v, 0, 5, 0);
	f1->SetTitle("I/I0 v/s v; v; I/I0");
	f1->Draw();
	TCanvas *c2 = new TCanvas("c2", "c2", 750, 750);
	TF1 *f2 = new TF1("I/I0 v/s d2", intensity_func_d2, 20, 200, 3);
	f2->SetParameters(0.01, 10, 4e-7);
	f2->SetParNames("h", "d1", "lambda");
	f2->SetTitle("I/I0 v/s d2; d2; I/I0");
	f2->Draw();
	return 1;
}

