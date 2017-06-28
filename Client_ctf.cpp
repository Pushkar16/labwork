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
#include "CTFFind.h"
int main()
{
	float CS, KV, WGH, XMAG, DSTEP, RESMIN, RESMAX;
    float DFMIN, DFMAX, FSTEP, DAST;
    int Box;
    char input[200], output[200];
    std::string line;
    std::ifstream myfile ("ctffind3_input.txt");
    if (myfile.is_open())
	{
  	std::string delimiter = ":";
    while ( getline (myfile,line) )
    {
	    std::string token = line.substr(0,line.find(delimiter));
	    std::string value = line.substr(line.find(delimiter)+1);
		  
		    if(token=="CS[mm]")
		    {
		    	CS=atof(value.c_str());
		    	std::cout<<"values of cs"<<CS;

		    }
		    if(token=="HT[kV]")
		    {
		    	KV=atof(value.c_str());

		    }
		    if(token=="AmpCnst")
		    {
		    	WGH=atof(value.c_str());

		    }
		    if(token=="DStep[um]")
		    {
		    	DSTEP=atof(value.c_str());

		    }
		    if(token=="Box")
		    {
		    	Box=atoi(value.c_str());

		    }
		    if(token=="ResMin[A]")
		    {
		    	RESMIN=atof(value.c_str());

		    }
		    if(token=="ResMax[A]")
		    {
		    	RESMAX=atof(value.c_str());

		    }
		    if(token=="dFMin[A]")
		    {
		    	DFMIN=atof(value.c_str());

		    }
        if(token=="XMAG")
        {
          XMAG=atof(value.c_str());

        }
		    if(token=="dFMax[A]")
		    {
				DFMAX=atof(value.c_str());
		    }
		    if(token=="FStep[A]")
		    {
				FSTEP=atof(value.c_str());

		    }
		    if(token=="dAst[A]")
		    {
				DAST=atof(value.c_str());

		    }
		      if(token=="input")
		    {
		    	std::strcpy(input, value.c_str());
		    	//input=&value[0];
		    	std::cout << "input file lenght is"<<strlen(value.c_str())<<"\n";
		    	//std::cout << "input file lenght is"<<strlen(input)<<"\n";
		    	std::cout << "input file lenght is"<<strlen(input)<<"\n";
		    }
		    if(token=="output")
		    {
		    	std::strcpy(output, value.c_str());

		    }
		   
    }
    int input_len=strlen(input);
    int output_len=strlen(output);
    char FILEIN[input_len],FILEOUT[output_len];
    for(int i=0;i<input_len;i++)
    	FILEIN[i]=input[i];
    for(int i=0;i<output_len;i++)
    	FILEOUT[i]=output[i];
    std::cout << "input file is "<<FILEIN<< '\n';
    std::cout << "output file is "<<FILEOUT<< '\n';
    std::cout << "CS[mm]is "<<CS<< '\n';
    std::cout << "HT[kV] is "<<KV<< '\n';
    std::cout << "AmpCnst is "<<WGH<< '\n';
    std::cout << "DStep[um] is "<<DSTEP<< '\n';
    std::cout << "Box is "<<Box<< '\n';
    std::cout << "ResMin[A] file is "<<RESMIN<< '\n';
    std::cout << "ResMax[A] is "<<RESMAX<< '\n';
    std::cout << "dFMin[A] is "<<DFMIN<< '\n';
    std::cout << "dFMax[A] is "<<DFMAX<< '\n';
    std::cout << "FStep[A] is "<<FSTEP<< '\n';
    std::cout << "dAst[A] is "<<DAST<< '\n';

  
	CTFFind ctf=CTFFind(FILEIN,FILEOUT,CS,KV,WGH,XMAG,DSTEP,RESMIN,RESMAX,DFMIN,DFMAX,FSTEP,DAST,Box);
  }
}