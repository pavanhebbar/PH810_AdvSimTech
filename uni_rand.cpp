#include <iostream>

int gennxt_method(int seed)
{
	int a = 1103515245;
	int b = 	12345;
	int m = pow(2, 31) - 1;
	return (a*seed + b) % m;
}

int uni_rand()
{
	int seed = 0;
	int n = 10000000;
	float rand;
	float randex;
	TH1F *h1 = new TH1F("h1", "Histogram", 1000, 0.0, 1.0);
	TH1F *h2 = new TH1F("h2", "Histogram2", 1000, 0.0, 1.0);
	for(int i = 0; i < n; i++)
	{
		rand = (float)(seed * 1.0/(pow(2, 31) - 1));
		randex = -log(1 - rand);
		seed = gennxt_method(seed);
		h1->Fill(rand);
		h2->Fill(randex);
	}
	h2->Draw();
	
	return 1;
}