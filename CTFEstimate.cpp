#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "CTFEstimate.h"

#define PI 3.14159265

/*CTFEstimate::CTFEstimate(float A,float lambda,float g,float cs,float defocus,float alpha_g,float alpha_ast)
{
	float w2=A;
	float w1=pow(1-pow(A,2),0.5);

	float gamma=calculateGamma(lambda,g,defocus,cs);
  std::cout <<std::fixed;
  std::cout<<"\ngamma is "<<gamma;
	calculateCTF(w1,w2,gamma);

}



/*float CTFEstimate::calculateGamma(float lambda,float g,float defocus, float cs)
{
   float a=2*pow(lambda,2)*pow(g,2)*cs;
   float fract=1/a;
   return PI*lambda*pow(g,2)*(defocus-fract);
}
void CTFEstimate::calculateCTF(float w1,float w2,float gamma)
{
  float sin_func=-w1*sin(gamma *PI/180.0);
  float cos_func=-w2*cos(gamma*PI/180.0);
  demo();
  std::cout<<"\n"<<sin_func<<"i+"<<cos_func<<"\n";
  std::cout<<"Intensity is "<<pow(sin_func,2)+pow(cos_func,2)<<"\n";
}*/

float CTFEstimate::calculateCTF(float CS,float WL,float WGH1,float WGH2,float DFMID1,float DFMID2,float ANGAST,float THETATR,int IX,int IY)
{
    float RAD,ANGLE,ANGSPT,C1,C2,ANGDIF,CCOS,DF,CHI,CTF;
    RAD=pow(IX,2)+pow(IY,2);
    if(RAD!=0)
    {
        RAD=sqrt(RAD);
        //std::cout <<"\nrad is "<<RAD;
        ANGLE=RAD*THETATR;
        ANGSPT=atan2((float)IY,(float)IX);
        C1=2*PI*ANGLE*ANGLE/(2*WL);
        C2=-C1*CS*ANGLE*ANGLE/2;
        //std::cout<<"\n"<<C1<<C2;
        //std::cout<<"\n ANGDIF calc"<<ANGSPT<<ANGAST;
        ANGDIF=ANGSPT-ANGAST;
        CCOS=cos(2.0*ANGDIF);
        //std::cout<<"\n CCOS ::"<<CCOS<<"  ANGDIF IS  "<<ANGDIF;
        DF=0.5*(DFMID1+DFMID2+CCOS*(DFMID1-DFMID2));
        CHI=C1*DF+C2;
        //std::cout<<"\n DF AND CHI "<<DF<<" ____"<<CHI;
        //std::cout<<"\n"<<sin(CHI)<<"______"<<cos(CHI);
        CTF=-WGH1*sin(CHI)-WGH2*cos(CHI);
  }
  else
  {
    CTF=-WGH2;
  }
  return CTF;
}