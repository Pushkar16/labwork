class CTFEstimate
{
public:
	float A;
	float lambda,g,cs;
	float freq,DF1,DF2;
    float alpha_g,alpha_ast;
    float gamma;
 public:
 	CTFEstimate(float A,float lambda,float g,float cs,float DF1,float DF2,float alpha_g,float alpha_ast);
 	float calculateFreq(float DF1,float DF2,float alpha_g, float alpha_ast);
 	float calculateGamma(float lambda,float g,float freq, float cs);
 	float calculateCTF(float w1,float w2,float gamma);

};