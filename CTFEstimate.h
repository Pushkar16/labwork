class CTFEstimate
{
public:
	float A;
	float lambda,g,cs;
	float freq,DF1,DF2;
    float alpha_g,alpha_ast;
    float gamma;
 public:
 	CTFEstimate(float A,float lambda,float g,float cs,float defocus,float alpha_g,float alpha_ast);
 	float calculateGamma(float lambda,float g,float defocus, float cs);
 	void calculateCTF(float w1,float w2,float gamma);

};