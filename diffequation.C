// Boundary value problem
// Program to find out the solution of the differential equation
// y" = -pi^2/4(y + 1)
//
// Runge - Kutta Method
//


Float_t ffx1(Float_t x, Float_t yy2)
{
  return yy2;
}

Float_t ffx2(Float_t xx , Float_t yy1)
{
  // function is -pi^2/4 (y1 +1)

  const Float_t kPi = 3.14159;
  Float_t xa = -kPi*kPi*(yy1 + 1.)/4.;
  
  return xa;
}

void diffequation()
{


  TH2F *h1 = new TH2F("h1","Sol. of Diff. Equ.",100,0.,1.,1500,0.,1.5);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(0.5);
  h1->SetMarkerColor(4);

  Float_t y1[100];
  Float_t y2[100];
  Float_t xx;
  Float_t x2;
  Float_t delta, fval0, fval1;
  Float_t hh;
  Float_t yy1, yy2;
  Float_t ak11, ak12, ak13, ak14;
  Float_t ak21, ak22, ak23, ak24;

  // Initialisation


  for (int i =0; i < 100; i++)
    {
      y1[i] = 0.;
      y2[i] = 0.;
    }

  Float_t xLow = 0.;
  Float_t xUpp = 1.;
  Float_t delX = 0.01;
  Float_t tole = 0.000001;

  Float_t hh = (xUpp - xLow)/100.;

  // Boundary Condition y(0) = 0 , y(1) = 1

  Float_t yLow = 0.;
  Float_t yUpp = 1.;

  // First one has to take some initial guess of y2 at x = 0  
  // Float_t x0 = (yUpp - yLow)/(xUpp-xLow);

  Float_t x0 = 0.1;
  Float_t x1 = x0 + delX;

  y1[0] = yLow;

  // root searching algorithm
  //

  for (int i = 0; i < 10; i++)
    {

      // the 2nd iteration RK-4

      y2[0] = x0;

      for (int j=0; j<99; j++)
	{
	  xx = xLow + (float) j*hh;
	  yy1 = y1[j];
	  yy2 = y2[j];

	  ak11 = hh*ffx1(xx,yy2);
	  ak21 = hh*ffx2(xx,yy1);

	  ak12 = hh*ffx1((xx+hh/2.),(yy2+ak21/2.));
	  ak22 = hh*ffx2((xx+hh/2.),(yy1+ak11/2.));

	  ak13 = hh*ffx1((xx+hh/2.),(yy2+ak22/2.));
	  ak23 = hh*ffx2((xx+hh/2.),(yy1+ak12/2.));

	  ak14 = hh*ffx1((xx+hh),(yy2+ak23));
	  ak24 = hh*ffx2((xx+hh),(yy1+ak13));

	  y1[j+1] = y1[j] + (ak11 + 2.*ak12+2.*ak13+ak14)/6.;
	  y2[j+1] = y2[j] + (ak21+2.*ak22+2.*ak23+ak24)/6.;

	}
      
      //cout << " step 1 y1[99] = " << y1[99] << endl;

      fval0 = y1[99] - 1.0;


      // the 2nd iteration RK-4

      y2[0] = x1;

      for (int j=0; j<99; j++)
	{
	  xx = xLow + (float) j*hh;
	  yy1 = y1[j];
	  yy2 = y2[j];

	  ak11 = hh*ffx1(xx,yy2);
	  ak21 = hh*ffx2(xx,yy1);

	  ak12 = hh*ffx1((xx+hh/2.),(yy2+ak21/2.));
	  ak22 = hh*ffx2((xx+hh/2.),(yy1+ak11/2.));

	  ak13 = hh*ffx1((xx+hh/2.),(yy2+ak22/2.));
	  ak23 = hh*ffx2((xx+hh/2.),(yy1+ak12/2.));

	  ak14 = hh*ffx1((xx+hh),(yy2+ak23));
	  ak24 = hh*ffx2((xx+hh),(yy1+ak13));

	  y1[j+1] = y1[j] + (ak11+2.*ak12+2.*ak13+ak14)/6.;
	  y2[j+1] = y2[j] + (ak21+2.*ak22+2.*ak23+ak24)/6.;

	}

      //cout << " step 2 y1[99] = " << y1[99] << endl;

      
      fval1 = y1[99] - 1.0;

      delta = fval1 - fval0;

      if (fabs(delta) <= tole)
	{
	  for (int j=0; j < 100; j++)
	    {
	      Float_t ij = (Float_t) j/100.;
	      cout << j << " " << y1[j] << endl;
	      h1->Fill(ij,y1[j]);
	    }

	  break;

	}
      else
	{
	  // Secant method
	  // root finding algorithm
	  //
	  x2 = x1 - fval1*(x1-x0)/delta;
	  x0 = x1;
	  x1 = x2;
	}



    }

  gStyle->SetOptStat(0);
  
  TCanvas *c1 = new TCanvas("c1","Sol of Dif. Eq.",0,0,500,500);
  TF1 *f1 = new TF1("f1","cos(1.57*x)+2.*sin(1.57*x)-1",0.,1.);

  h1->Draw();

  f1->Draw("same");

}

