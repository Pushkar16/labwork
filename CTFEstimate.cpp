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

CTFEstimate::CTFEstimate(float A,float lambda,float g,float cs,float DF1,float DF2,float alpha_g,float alpha_ast);
{
	float w2=A;
	float w1=pow(1-pow(A,2),0.5);
	float freq=calculateFreq(DF1,DF2,alpha_g,alpha_ast);
	float gamma=calculateGamma(lambda,g,freq,cs);
	float ctf_value=calculateCTF(w1,w2,gamma);
	std::cout<<"\nctf_value is "<<ctf_value<<"\n";

}

float CTFEstimate::calculateFreq(float DF1,float DF2,float alpha_g, float alpha_ast)
{
  float cos_value=cos((alpha_g-alpha_ast)*PI/180.0);
  return 0.5*(DF1+DF2+(DF1-DF2)*cos_value);
}

float CTFEstimate::calculateGamma(float lambda,float g,float freq, float cs)
{
   float a=2*pow(lambda,2)*pow(g,2)*cs;
   float fract=1/a;
   return PI*lambda*pow(g,2)*(freq-fract);
}
float CTFEstimate::calculateCTF(float w1,float w2,float gamma)
{
  float sin_func=sin(gamma *PI/180.0);
  float cos_func=cos(gamma*PI/180.0);
  return -(w1*sin_func)-(w2*cos_func);
}