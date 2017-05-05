#include <iostream>

int histogram()
{
	TFile file("histos.root", "new");
	TH1F *h1 = new TH1F("h1", "Example", 10, 0., 10.);
	for(int i = 0; i < 100; i++)
	{
		float x = (float)i;
		int w = i;
		if (i > 5)
		{
			w = 10 - i;
		}
		h1->Fill(x, w);
	}
	h1->Fit("gaus");
	//h1->Draw();
	h1->Write();
	file.Write();
	return 0;
}