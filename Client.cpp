#include <iostream>
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
using namespace std;
#include "CTFEstimate.h"

int main()
{
	float A;
	float lambda,g,cs;
	float DF1,DF2;
    float alpha_g,alpha_ast;
	std::string line;
  	std::ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
  	std::string delimiter = ":";
    while ( getline (myfile,line) )
    {
	    std::string token = line.substr(0,line.find(delimiter));
	    std::string value = line.substr(line.find(delimiter)+1);
		    if(token=="A")
		    {
				A=atof(value.c_str());
		    }
		    
		    if(token=="lambda")
		    {
		    	lambda=atof(value.c_str());

		    }
		    if(token=="g")
		    {
		    	g=atof(value.c_str());

		    }
		    if(token=="CS")
		    {
		    	cs=atof(value.c_str());

		    }
		    if(token=="DF1")
		    {
		    	DF1=atof(value.c_str());

		    }
		    if(token=="DF2")
		    {
		    	DF2=atof(value.c_str());

		    }
		    if(token=="alpha_g")
		    {
		    	alpha_g=atof(value.c_str());

		    }
		    if(token=="alpha_ast")
		    {
		    	alpha_ast=atof(value.c_str());

		    }
		 
		   
      //std::cout << token << '\n';
    }
  }
  	//std::cout<<w1<<"\n"<<w2<<"\n"<<lambda<<"\n"<<g<<"\n"<<cs<<"\n"<<alpha_g<<"\n"<<alpha_ast;
	CTFEstimate ctf=CTFEstimate(A,lambda,g,cs,DF1,DF2,alpha_g,alpha_ast);
	std::cout<<"in client\n";
}