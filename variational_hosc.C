//
// Variational monte carlo for Harmonic Oscillator
//
void Initialize(Float_t psi[],Float_t &dx, Float_t &dpsi,
		Float_t &xLeft,Float_t &xRight,
		Float_t &energy);
void Normalize(Float_t psi[],Float_t dx,Float_t xLeft,Float_t xRight);
void Calculate(Float_t psi[],Float_t dx,Float_t dpsi,
	       Float_t xLeft,Float_t xRight,
	       Float_t &energy, Int_t nattempts);
void CalEnergy(Float_t psi[],Float_t dx,Float_t xLeft,Float_t xRight,
	       Float_t &energy);
Float_t Potential(Float_t x);



void Initialize(Float_t psi[],Float_t &dx, Float_t &dpsi,
		Float_t &xLeft,Float_t &xRight,
		Float_t &energy)
{
  /*
    dx      = 0.2;
    xLeft   = -5.0
    xRight  = 5.0;
  */

  Float_t delta = 4.0/dx;

  for(Int_t i = 0; i< 96; i++)
    {
      psi[i] = 1./sqrt(delta);
    }

  dpsi = 0.1/sqrt(delta);
  
  Normalize(psi,dx,xLeft,xRight);
  CalEnergy(psi,dx,xLeft,xRight,energy);

}
//
// Normalization
//
void Normalize(Float_t psi[],Float_t dx,Float_t xLeft,Float_t xRight)
{
  Float_t sum = 0.;
  
  for(int i=0; i < 100; i++)
    {
      sum += dx*psi[i]*psi[i];
    }
  for(int i=0; i < 100; i++)
    {
      psi[i] = psi[i]/sqrt(sum);
    }

}
//
//

void Calculate(Float_t psi[],Float_t dx,Float_t dpsi,
	       Float_t xLeft,Float_t xRight,
	       Float_t &energy, Int_t nattempts)
{
  TRandom rr;
  Int_t ntotal      = 0;
  Int_t nmoves      = 0;
  Int_t na          = 0;
  Float_t newenergy = 0.;

  for(int i = 0; i < nattempts; i++)
    {
      Int_t n =  2 + rr.Integer(97);
      Float_t psiOld = psi[n];
      psi[n] += 2.*(rr.Rndm()-0.5)*dpsi;

      CalEnergy(psi,dx,xLeft,xRight,newenergy);

      if (newenergy > energy)
	{
	  psi[n] = psiOld;
	}
      else
	{
	  energy = newenergy;
	  Normalize(psi,dx,xLeft,xRight);
	  na++;
	}
    }

  ntotal += nattempts;
  nmoves += na;

  //cout << "total = " << ntotal << " nmoves = " << nmoves << endl;
}

//
// --------------------------
//

void CalEnergy(Float_t psi[],Float_t dx,Float_t xLeft,Float_t xRight,
	       Float_t &energy)
{
  energy = 0.;
  Float_t sum = 0.;
  Float_t xLow = 0.2;

  for (int i = 1; i < 99; i++)
    {

      Float_t xx = xLow + (Int_t)i*dx;

      energy += dx*Potential(xx)*psi[i]*psi[i]-
	dx*psi[i]*((0.5/(dx*dx))*(psi[i+1]+psi[i-1]-2*psi[i]));

      sum += psi[i]*psi[i]*dx;

    }

  energy = energy/sum;

}

Float_t Potential(Float_t x)
{
  // Here m = 1, w = 1
  //
  Float_t potential = 1.0/pow(x, 12) - 1.0/pow(x, 6);

  return potential;
}




//
// main program starts
//
void variational_hosc(Int_t nattempts = 1000)
{

  TH2F *h21 = new TH2F("h21","",100,0.2,20.0,100,0.,1.);
  TH2F *h22 = new TH2F("h22","",100,0.2,20.0,100,0.,1.);


  Float_t dx      = 0.2;
  Float_t dpsi    = 0.;
  Float_t energy  = 0.;
  Float_t xLeft   = 0.2;
  Float_t xRight  = 10.0;

  Float_t psi[100];

  for (Int_t i = 0; i < 100; i++)
    {
      psi[i] = 0.;
    }
  
  Initialize(psi,dx,dpsi,xLeft,xRight,energy);

  cout << " old energy = " << energy << endl;

  for(int i=0; i<100; i++)
    {
      Float_t xx = 0.2 + (int)i*dx;
      h21->Fill(xx,psi[i]);
    }


  Calculate(psi,dx,dpsi,xLeft,xRight,energy,nattempts);

  cout << "energy = " << energy << " nattempts = " << nattempts << endl; 
	    
  CalEnergy(psi,dx,xLeft,xRight,energy); 
  float sum; 

  for(int i=0; i<100; i++)
    {
      //cout << psi[i] << endl;
      Float_t xx = 0.2 + (int)i*dx;
      h22->Fill(xx,psi[i]);
      cout << xx << " " << psi[i] << endl;
      sum += psi[i]*psi[i]*dx;
    }
    cout << "sum = " << sum << endl;

  cout << " new energy = " << energy << endl;

  gStyle->SetOptStat(0);

  TCanvas *c1 = new TCanvas("c1","Wavefunction for HO Potential",0,0,500,500);
  c1->cd();
  h22->SetMarkerStyle(20);
  h22->SetMarkerColor(4);
  h22->Draw();

  h21->SetMarkerStyle(25);
  h21->SetMarkerColor(2);
  h21->SetMarkerSize(1);
  h21->Draw("same");
  TText *t1 = new TText(0.5,1.6,"Wavefunction for H.O. Potential");
  t1->Draw();


  TCanvas *c2 = new TCanvas("c2","Harmon Potential",0,0,500,500);

  TF1 *f1 = new TF1("f1","0.5*x*x",-10.,10.);
  c2->cd();
  
  f1->Draw();

  TText *t2 = new TText(2,8,"Harmonic Oscillator Potential");
  t2->Draw();

}
