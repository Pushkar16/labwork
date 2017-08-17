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
#include "ctffind.h"
#include "CTFEstimate.h"
extern"C" {
void guessf_(char *FILEIN, char  *CFORM,bool *EX);
void iopen_(char *FILEIN,int *IFILE,char  *CFORM,int *mode,int *NX,int *NY,int *NZ,char *CSTIN,float *STEPR,char TITLE[80]);
void demo_(int NXYZ[]);
void iread_(int *,float *,int *);
void iwrite_(int *,float *,int *);
void iclose_(int *IFILE);
void getparam_(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,float *RMSA,int *NY,int *CNT,int *NX);
void calculatepower_(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,float *RMSA,int *NY,int *CNT,int *NX,float *RMSMAX,float *RMSMIN,int KXYZ[],float *SCAL,float *POWER);
void boximg_(float *AIN,int NXYZ[] ,float *ABOX,int JXYZ[] ,int *IX,int *boximg_num,float *MEAN,float *RMS);
void histo_(int *CNT,int *NBIN,float *RMSA,float *BINS,float *MIN,float *MAX);
void rlft3_(float *ABOX,float* CBOXS,int *nn1,int *nn2,int *nn3,int *isign);
void filter_(int JXYZ[],int KXYZ[],float *POWER,float *BUF1,float *DMEAN,float *DRMS1,float *DMAX,float *RESMIN);
float ctf_(float *CS,float *WL,float *WGH1,float *WGH2,float *DFMID1,float *DFMID2,float *ANGAST,float *THETATR,int *LL,int *MM);
void search_ctf_(float *CS,float *WL,float *WGH1,float *WGH2,float *THETATR,float *RESMIN,float *RESMAX,float *POWER,int JXYZ[],float *DFMID1,float *DFMID2,float *ANGAST,float *FSTEP,float *DAST);
void forwrite_(float *OUT,char *FILEOUT,char *CFORM,float *STEPR,char TITLE[80],int JXYZ[]);
void refine_ctf_(float *DFMID1,float *DFMID2,float *ANGAST,float *POWER,float *CS,float *WL,float *WGH1,float *WGH2,float *THETATR,float *RMIN2,float *RMAX2,int JXYZ[],float *HW,float *DAST);
}

CTFFind::CTFFind(float CS,float KV,float WGH,float XMAG,float DSTEP,float RESMIN,float RESMAX,float DFMIN,float DFMAX,float FSTEP,float DAST,int Box,std::string inputfile,std::string outputfile)
{
  char FILEIN[inputfile.length()+1];
  strcpy(FILEIN, inputfile.c_str());
  std::cout<< CS<<"\t"<<KV<<"\t"<< WGH<<"\t"<<XMAG<<"\n";
  std::cout<<  DSTEP<<"\t"<< RESMIN<<"\t"<< RESMAX<<"\t"<< DFMIN<<"\t"<< DFMAX<<"\t"<< FSTEP<<"\t"<< DAST<<"\t"<< Box<<"\n";
  std::cout<<FILEIN;
  int NXYZ[3], MODE, JXYZ[3], I, J, NX, NY,NZ, IX, IS, KXYZ[3];
  int K, CNT, ID, L, M, LL, MM, ITEST, IP, IMP, IERR;
  int OMP_GET_NUM_PROCS;
  int NBIN = 100;
  const int  LENGTH = 10;
  float DMAX, DMEAN, DRMS, RMS, WGH1, WGH2, RMSMIN;
  float SCAL, MEAN, WL, MIN, MAX, ANGAST;
  float DFMID1, DFMID2;
  float THETATR, STEPR, RMIN2, RMAX2, HW, RMSMAX;
  float RES2, CTF, CTFV, TMP, DRMS1, CMAX;
  float *AIN, *ABOX, *POWER, *OUT, *BUF1,*CBOXS;
  float *RMSA, *BINS;
  int boximg_num=1;
  const float FLT = -0.1;
  const float PI = 3.1415926535898;
  char  TITLE[1600], CFORM, NCPUS[10];
  char *input;
  bool EX=false;
  JXYZ[0]= Box;

  checkParameters(&DAST,JXYZ,&RESMIN,&RESMAX,&DFMIN,&DFMAX);
  std::cout<<"input file is "<<FILEIN<<"\n";
  std::cout<<FILEIN<<"\t"<<CFORM<<"\t"<<EX<<"\n";
  guessf_(FILEIN,&CFORM,&EX);
    std::cout<<FILEIN<<"\t"<<CFORM<<"\t"<<EX<<"\n";

  if(!EX)
  {
   std::cout << "Unable to open file"; 
 		exit(1);
  }
  std::string tmp = "OLD";
  char tab2[1024];
  strcpy(tab2, tmp.c_str());
  int IFILE=10;
  iopen_(FILEIN,&IFILE,&CFORM,&MODE,&NXYZ[0],&NXYZ[1],&NXYZ[2],tab2,&STEPR,TITLE);
  NX=NXYZ[0]/JXYZ[0];
  NY=NXYZ[1]/JXYZ[1];
  AIN=(float*) calloc(NXYZ[0]*JXYZ[1],sizeof (float));
  ABOX=(float*) calloc(JXYZ[0]*JXYZ[1],sizeof (float));
  CBOXS=(float*) calloc(JXYZ[0]*JXYZ[1],sizeof (float));
  OUT=(float*) calloc(JXYZ[0]*JXYZ[1],sizeof (float));
  BUF1=(float*) calloc(JXYZ[0]*JXYZ[1],sizeof (float));
  RMSA=(float*) calloc(NX*NY,sizeof (float));
  BINS=(float*) calloc(NBIN,sizeof (float));
  if((AIN==NULL)||(ABOX==NULL)||(OUT==NULL)||(BUF1==NULL)||(RMSA==NULL)||(BINS==NULL))
  {
 		std::cout <<"NOT ENOUGH MEMORY";
 		exit(1);
  }
  DRMS=0;
  CNT=0;
  fillABOX(AIN,NXYZ,ABOX,JXYZ,&IX,&DRMS,&MEAN,&RMS,RMSA,&NY,&CNT,&NX);
  DRMS=pow(DRMS/CNT,0.5);
  std::cout<<"\n DRMS is::"<<DRMS;
  histo_(&CNT,&NBIN,RMSA,BINS,&MIN,&MAX);
  RMSMIN=MIN;
  RMSMAX=MAX;
  getRMSMax_RMSMin(NBIN,BINS,MIN,MAX,&RMSMIN,&RMSMAX);
  KXYZ[0]=JXYZ[0]/2;
  KXYZ[1]=JXYZ[1];
  KXYZ[2]=JXYZ[2];
  if(2*(KXYZ[0]/2)!=KXYZ[0])
  {
		KXYZ[0]=KXYZ[0]+1;
  }
  POWER=(float*) calloc(KXYZ[0]*KXYZ[1],sizeof (float));
  if(POWER==NULL)
  {
 		std::cout <<"NOT ENOUGH MEMORY";
 		exit(1);
  }
  for(K=0;K<KXYZ[0]*KXYZ[1];K++)
  {
 		POWER[K]=0.0;
  }
  SCAL=1/pow((float)(JXYZ[0]*JXYZ[1]),0.5);
  std::cout<<"\n SCAL::"<<SCAL<<" RMSMIN::"<<RMSMIN<<" RMSMAX::"<<RMSMAX;
  CNT=0;
  calcPower(AIN,NXYZ,ABOX,JXYZ,&IX,&DRMS,&MEAN,&RMS,
		           RMSA,&NY,&CNT,&NX,&RMSMAX,&RMSMIN,KXYZ,&SCAL,POWER,CBOXS);
  SCAL=1/(float)CNT;
  for(K=0;K<KXYZ[0]*KXYZ[1];K++)
  {
		POWER[K]=pow(POWER[K]*SCAL,0.5);
    
  }

  
  STEPR=DSTEP*pow(10,4)/XMAG;
  RESMIN=STEPR/RESMIN;
  RESMAX=STEPR/RESMAX;
  if (RESMIN<STEPR/50)
  {
    	RESMIN=STEPR/50;
    	std::cout<<"lower resolution reset";

  }
  if (RESMIN>RESMAX)
  {
    	std::cout<<"increase RESMAX";
    	exit(1);
  }
 filter_(JXYZ,KXYZ,POWER,BUF1,&DMEAN,&DRMS1,&DMAX,&RESMIN);
 CS=CS*pow(10.0,7.0);                     
 KV=KV*1000.0;                             
 WL=12.26/pow(KV+0.9785*pow(KV,2)/pow(10.0,6.0),0.5);
 WGH1=pow(1.0-pow(WGH,2),0.5);
 WGH2=WGH;
 THETATR=WL/(STEPR*JXYZ[0]);
 DFMID1=DFMIN;
 DFMID2=DFMAX;
 search_ctf_(&CS,&WL,&WGH1,&WGH2,&THETATR,&RESMIN,&RESMAX,POWER,JXYZ,&DFMID1,&DFMID2,&ANGAST,&FSTEP,&DAST);
 RMIN2=pow(RESMIN,2);
 RMAX2=pow(RESMAX,2);
 HW=-1.0/(float)RMAX2;
 float hw=0.0;
 refine_ctf_(&DFMID1,&DFMID2,&ANGAST,POWER,&CS,&WL, &WGH1,&WGH2,&THETATR,&RMIN2,&RMAX2,JXYZ,&HW,&DAST);
 calculateOutput(&MM,&LL,POWER,OUT,JXYZ,&RMAX2,&RMIN2,
						&CS,&WL,&WGH1,&WGH2,&DFMID1,&DFMID2,&ANGAST,&THETATR,&DRMS1);

 iclose_(&IFILE);
 MODE=2;
 if (STEPR!=0.0)
 {
   STEPR=1.0/STEPR;
 }

 tmp = "NEW";
 strcpy(tab2, tmp.c_str());
 char *FILEOUT=new char[outputfile.length()+1];
 strcpy(FILEOUT, outputfile.c_str());
 writeOutput(&J,OUT,FILEIN,FILEOUT,&IFILE,&CFORM,&MODE,&NX,&NY,&NZ,tab2,
				&STEPR,TITLE,JXYZ);
 //forwrite_(OUT,FILEOUT,&CFORM,&STEPR,TITLE,JXYZ);

}
void CTFFind::checkParameters(float *DAST,int JXYZ[],float *RESMIN,float *RESMAX,float *DFMIN,float *DFMAX)
{
  int ITEST=JXYZ[0]/2;
  int TMP;
  if(ITEST%2!=0)
  {
    std::cout << "box size must be even number"<< '\n';
    exit(1);
  }
  if(*DAST<0)
  {
   *DAST=500; 
    std::cout << "DAST set to 500";   
  }
  JXYZ[2]=1;
  JXYZ[1]=JXYZ[0];
  if(*RESMIN<*RESMAX)
  {
    TMP=*RESMIN;
    *RESMIN=*RESMAX;
    *RESMAX=TMP;
  }
  if(*DFMAX<*DFMIN)
  {
   TMP=*DFMAX;
   *DFMAX=*DFMIN;
   *DFMIN=TMP;
  }
}
void CTFFind::fillABOX(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,float *RMSA,int *NY,int *CNT,int *NX)
{
  /*int I,J,boximg_num=1;
  for(I=1;I<=*NY;I++)
  {
    int IP=(I-1)*JXYZ[1];
    for (J= 1; J <=JXYZ[1];J++)
    {
      int ID=1+NXYZ[0]*(J-1);
      int line=10;
      int irec=J+IP;
      //std::cout<<"\nAIN[ID] B4  :"<<AIN[ID]<<"and ID is "<<ID;
      iread_(&line,&AIN[ID],&irec);
      //std::cout<<"\nAIN[ID] AFTWE  :"<<AIN[ID]<<"and ID is"<<ID;
    }
    for (J= 1; J <=*NX; ++J)
    {
      *IX=1+JXYZ[0]*(J-1);
      //std::cout<<"___________________________________________";
      //std::cout<<AIN<<"\t"<<NXYZ<<"\t"<<ABOX<<"\t"<<IX<<"\t"<<boximg_num<<"\t"<<MEAN<<"\t"<<RMS;
      boximg_(AIN,NXYZ,ABOX,JXYZ,IX,&boximg_num,MEAN,RMS);
      //std::cout<<"\nDRMS is "<<DRMS;
      //std::cout<<"\nRMS is "<<RMS;
      *DRMS=*DRMS+pow(*RMS,2);
      //std::cout<<"\nDRMS AFTER CALCULATION IS"<<DRMS;     
      if (*CNT<50000) RMSA[*CNT]=*RMS;
        *CNT=*CNT+1;

    }
    //std::cout<<"IP is"<<I P<<"\n";

  }*/

    getparam_(AIN,NXYZ,ABOX,JXYZ,IX,DRMS,MEAN,RMS,RMSA,NY,CNT,NX);
}
void CTFFind::getRMSMax_RMSMin(int NBIN,float *BINS,float MIN,float MAX,float *RMSMIN,float *RMSMAX)
{
  int CMAX=0,I,J;
  for(int I=0;I<NBIN;I++)
  {
    if(BINS[I]>CMAX)
    {
     CMAX=BINS[I];
      J=I;
    }
         
  }
  //std::cout<<"CMAX is"<<CMAX<<"\n";

  if (J >1) 
  {
    //std::cout<<"VALUE OF J  is"<<J<<"\n";
    for(I=0;I<J-1;I++)
    {
      //std::cout<<"\nVALUE OF I  is"<<I<<"\n";
      if (BINS[I] >= CMAX/20.0) 
      {
        *RMSMIN = (I+1)*(MAX - MIN)/(NBIN - 1) + MIN;
        break;
      }
              
    }
  }
  if (J <= NBIN) 
  {
    //std::cout<<"VALUE OF J  is"<<J<<"\n";
    for(I = NBIN-1; I>=J + 1;I--)
    {
      //std::cout<<"VALUE OF I  is"<<I<<"\n";
      if (BINS[I] >= CMAX/20.0) 
      {
        *RMSMAX = (I+1)*(MAX - MIN)/(NBIN - 1) + MIN;
        break;
      }
          
    }
  }
}
void CTFFind::calcPower(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,
               float *RMSA,int *NY,int *CNT,int *NX,float *RMSMAX,float *RMSMIN,int KXYZ[],float *SCAL,float *POWER,float *CBOXS)
{
/*  int I,J,IS,boximg_num=1;

  for(I=1;I<=*NY;I++)
  {
    int IP=(I-1)*JXYZ[1];
    for(J=1;J<=JXYZ[1];J++)
    {
      int ID=1+NXYZ[0]*(J-1);
      int line=10;
      int irec=J+IP;  
      //iread_(&line,&AIN[ID],&irec);
        //std::cout<<"out of read";

    }
    for(J=1;J<=*NX;J++)
    {

      *IX=(J-1)*JXYZ[0]+1;
      //il=il+1;
      boximg_(AIN,NXYZ,ABOX,JXYZ,IX,&boximg_num,MEAN,RMS);     
       //std::cout<<"\n RMS IS ::"<<RMS<<"\t RMSMAX is ::"<<RMSMAX<<"\t RMSMIN IS"<<RMSMIN;
      if((RMS<RMSMAX)&&(RMS>RMSMIN))
      {

        int nn3=1;
        int isign=1;
        rlft3_(ABOX,CBOXS,&JXYZ[0],&JXYZ[1],&nn3,&isign);
        for(int L=1;L<=JXYZ[1];L++)
        {
          for(int K=1;K<=JXYZ[0]/2;K++)
          {
            int ID=(K+JXYZ[0]/2*(L-1))*2;
             IS=K+KXYZ[0]*(L-1);
            //std::cout<<"\nIS is"<<IS<<" power "<<POWER[IS];
            POWER[IS-1]=POWER[IS]+(pow(ABOX[ID-2],2)+pow(ABOX[ID-1],2))*pow(*SCAL,2);
                    
          }
          if (KXYZ[0]>JXYZ[0]/2)
          {
            //std::cout<<"in if"<<KXYZ[0]<<JXYZ[0];
            POWER[IS]=POWER[IS]+pow(abs(CBOXS[L]*(*SCAL)),2);
          }
        }
        *CNT=*CNT+1;
      }
              

    }

  }*/
    calculatepower_(AIN, NXYZ,ABOX, JXYZ,IX,DRMS,MEAN,RMS,RMSA,NY,CNT,NX,RMSMAX,RMSMIN,KXYZ,SCAL,POWER);
}
void CTFFind::calculateOutput(int *MM,int *LL,float *POWER,float *OUT,int JXYZ[],float *RMAX2,float *RMIN2,
            float *CS,float *WL,float *WGH1,float *WGH2,float *DFMID1,float *DFMID2,float *ANGAST,float *THETATR,float *DRMS1)
{
  int I,L,M,ID,J,IS;
  float CTFV;

  for(I=0;I<JXYZ[0]*JXYZ[1];I++)
  {
    OUT[I]=0;
  }
  for ( L = 1; L <=JXYZ[0]/2; L++)
  {
    *LL=L-1;
    for (M = 1; M <= JXYZ[1]; M++)
    {
      *MM=M-1;
      if(*MM>JXYZ[1]/2)
      {
        *MM=*MM-JXYZ[1];
      }
      ID=L+JXYZ[0]/2*(M-1);
      I=L+JXYZ[0]/2;
      J=M+JXYZ[1]/2;
      if(J>JXYZ[1])
      {
              J=J-JXYZ[1];
      }
      IS=I+JXYZ[1]*(J-1);
      OUT[IS]=POWER[ID]/(*DRMS1)/2.0+0.5;
      if (OUT[IS]>1.0) 
      {
        OUT[IS]=1.0;
      }
      if (OUT[IS]<-1.0) 
      {
          OUT[IS]=-1.0;
      }
      float RES2=pow((float)*LL/JXYZ[0],2)+pow((float)*MM/JXYZ[1],2);
      //std::cout<<"\n "<<RES2<<"\t"<<*RMAX2<<"\t"<<*RMIN2;
     if ((RES2<=*RMAX2)&&(RES2>=*RMIN2)) 
     {
        CTFEstimate ct;
        CTFV=ct.calculateCTF(*CS,*WL,*WGH1,*WGH2,*DFMID1,*DFMID2,*ANGAST,*THETATR,*LL,*MM);
        //CTFV=ctf_(CS,WL,WGH1,WGH2,DFMID1,DFMID2,ANGAST,THETATR,LL,MM);
        //std::cout<<"\nvalue of ctfv is "<<ctf_(CS,WL,WGH1,WGH2,DFMID1,DFMID2,ANGAST,THETATR,LL,MM)<<" and my value "<<CTFV;
        I=JXYZ[0]/2-L+1;
        J=JXYZ[1]-J+2;
        if(J<=JXYZ[1])
        {
         IS=I+JXYZ[0]*(J-1);
         //std::cout<<"\nIS is "<<IS;
         //std::cout<<"\nvalue of ctfv is "<<CTFV;
         OUT[IS]=pow(CTFV,2);
         //std::cout<<"\nIS is "<<IS<<"out[is] is "<<OUT[IS];
        }
            
    }
  }
 }     
}
void CTFFind::writeOutput(int *J,float *OUT,char *FILEIN,char *FILEOUT,int *IFILE,char  *CFORM,int *MODE,int *NX,int *NY,int *NZ,char *CSTIN,
          float *STEPR,char TITLE[80],int JXYZ[])
{
   std::string  tmp="NEW";
   char tab2[1024];
   strcpy(tab2, tmp.c_str());
   iopen_(FILEOUT,IFILE,CFORM,MODE,&JXYZ[0],&JXYZ[1],&JXYZ[2],tab2,STEPR,TITLE);
   //std::cout<<"______________________________b4 for";
   for(*J=1;*J<=JXYZ[1];(*J)++)
   {
      //std::cout<<"in for";
      int ID=1+JXYZ[0]*(*J-1);
      std::cout<<"\nJ is"<<*J<<" ID is "<<ID<<"out[id] is"<<OUT[ID];
      
      iwrite_(IFILE,&OUT[ID],J);
    }
   iclose_(IFILE);
}

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(ctffind)
{
    class_<CTFFind>("CTFFind",init<float,float,float ,float ,float ,float ,float ,float ,float ,float ,float ,int,std::string,std::string >())
    ;

}