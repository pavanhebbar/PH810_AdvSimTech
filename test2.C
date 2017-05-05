#include <iostream>

void test2()
{
	TRandom1 r1;
	TH1F *h1 = new TH1F("h1", "histogram", 100, -10, 10);
	for (int i = 0; i < 1000000; i++)
	{
		double xx = r1.Gaus();
		h1->Fill(xx);
	}
	h1->Draw();
}