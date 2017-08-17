class CTFFind
{
public:
	float CS,KV,WGH,XMAG,DSTEP,RESMIN,RESMAX;
	float DFMIN,DFMAX,FSTEP,DAST;
	int JXYZ[3];
public:
	CTFFind(float CS,float KV,float WGH,float XMAG,float DSTEP,float RESMIN,float RESMAX,
            float DFMIN,float DFMAX,float FSTEP,float DAST,int Box,std::string inputfile,std::string outputfile);
	void checkParameters(float *DAST,int JXYZ[],float *RESMIN,float *RESMAX,float *DFMIN,float *DFMAX);
	void fillABOX(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,float *RMSA,int *NY,int *CNT,int *NX);
	void getRMSMax_RMSMin(int NBIN,float *BINS,float MIN,float MAX,float *RMSMIN,float *RMSAX);
	void calcPower(float *AIN,int NXYZ[],float *ABOX,int JXYZ[],int *IX,float *DRMS,float *MEAN,float *RMS,
		           float *RMSA,int *NY,int *CNT,int *NX,float *RMSMAX,float *RMSMIN,int KXYZ[],float *SCAL,float *POWER,float *CBOXS);
	void calculateOutput(int *MM,int *LL,float *POWER,float *OUT,int JXYZ[],float *RMAX2,float *RMIN2,
						float *CS,float *WL,float *WGH1,float *WGH2,float *DFMID1,float *DFMID2,float *ANGAST,float *THETATR,float *DRMS1);
	void writeOutput(int *J,float *OUT,char *FILEIN,char *FILEOUT,int *IFILE,char  *CFORM,int *MODE,int *NX,int *NY,int *NZ,char *CSTIN,
					float *STEPR,char TITLE[80],int NXYZ[]);


};