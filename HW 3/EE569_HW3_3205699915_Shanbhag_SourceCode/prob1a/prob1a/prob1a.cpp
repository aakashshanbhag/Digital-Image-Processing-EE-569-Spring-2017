// Inclusion of all headers
#include "stdafx.h"
#include <iostream>
#include "Header1.h"
#include<math.h>
using namespace std;
#include <fstream>

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	int BytesPerPixel1=1;
	int Size_h,Size_w ;
	

	if (argc < 1)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name "<<endl;
		return 0;
	}
	
	Size_h=128;// Width of the image used.
	Size_w=128;// Height of the image used.
	const int n=5;//Size of the Bayer index.
	
	
	//	Training 12 images(TextureImages)

	unsigned char *Imagedatac1;
	unsigned char *Imagedatac2;
	unsigned char *Imagedatac3;
	unsigned char *Imagedatac4;
	unsigned char *Imagedatac5;
	unsigned char *Imagedatac6;
	unsigned char *Imagedatac7;
	unsigned char *Imagedatac8;
	unsigned char *Imagedatac9;
	unsigned char *Imagedatac10;
	unsigned char *Imagedatac11;
	unsigned char *Imagedatac12;
	
	Imagedatac1= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac2= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac3= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac4= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac5= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac6= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac7= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac8= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac9= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac10= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac11= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatac12= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix

	unsigned char *Imagedatam;
	unsigned char *IndexMatrix;

	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Output image matrix
	IndexMatrix= new unsigned char [5*5];// Basic Index matrix needed.

	//	Reading Training data image textures.

	fileread(file,"D:/cplusplus/HW3/prob1a/Texture1.raw",Imagedatac1,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture2.raw",Imagedatac2,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture3.raw",Imagedatac3,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture4.raw",Imagedatac4,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture5.raw",Imagedatac5,Size_h,Size_w,BytesPerPixel1);	
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture6.raw",Imagedatac6,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture7.raw",Imagedatac7,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture8.raw",Imagedatac8,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture9.raw",Imagedatac9,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture10.raw",Imagedatac10,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture11.raw",Imagedatac11,Size_h,Size_w,BytesPerPixel1);	
	fileread(file,"D:/cplusplus/HW3/prob1a/Texture12.raw",Imagedatac12,Size_h,Size_w,BytesPerPixel1);
	

	//	Reading Classification data image textures.

	unsigned char *ImagedatacA;
	unsigned char *ImagedatacB;
	unsigned char *ImagedatacC;
	unsigned char *ImagedatacD;
	unsigned char *ImagedatacE;
	unsigned char *ImagedatacF;

	ImagedatacA= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE A image matrix
	ImagedatacB= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE B  image matrix
	ImagedatacC= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE C  image matrix
	ImagedatacD= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE D  image matrix
	ImagedatacE= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE E  image matrix
	ImagedatacF= new unsigned char [Size_w*Size_h*BytesPerPixel1];// TEXTURE F  image matrix

	fileread(file,"D:/cplusplus/HW3/prob1a/TextureA.raw",ImagedatacA,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/TextureB.raw",ImagedatacB,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/TextureC.raw",ImagedatacC,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/TextureD.raw",ImagedatacD,Size_h,Size_w,BytesPerPixel1);
	fileread(file,"D:/cplusplus/HW3/prob1a/TextureE.raw",ImagedatacE,Size_h,Size_w,BytesPerPixel1);	
	fileread(file,"D:/cplusplus/HW3/prob1a/TextureF.raw",ImagedatacF,Size_h,Size_w,BytesPerPixel1);

	// Allocation of multi-dimensional array for easier handling of pixels.
	double **Imgdatac1=NULL;
	Imgdatac1=alloc_mem2double(Imgdatac1,Size_h,Size_w);
	
	double **Imgdatac2=NULL;
	Imgdatac2=alloc_mem2double(Imgdatac2,Size_h,Size_w);
	
	double **Imgdatac3=NULL;
	Imgdatac3=alloc_mem2double(Imgdatac3,Size_h,Size_w);
	
	double **Imgdatac4=NULL;
	Imgdatac4=alloc_mem2double(Imgdatac4,Size_h,Size_w);
	double **Imgdatac5=NULL;
	Imgdatac5=alloc_mem2double(Imgdatac5,Size_h,Size_w);
	
	double **Imgdatac6=NULL;
	Imgdatac6=alloc_mem2double(Imgdatac6,Size_h,Size_w);

	double **Imgdatac7=NULL;
	Imgdatac7=alloc_mem2double(Imgdatac7,Size_h,Size_w);

	double **Imgdatac8=NULL;
	Imgdatac8=alloc_mem2double(Imgdatac8,Size_h,Size_w);
	
	double **Imgdatac9=NULL;
	Imgdatac9=alloc_mem2double(Imgdatac9,Size_h,Size_w);

	double **Imgdatac10=NULL;
	Imgdatac10=alloc_mem2double(Imgdatac10,Size_h,Size_w);
	
	double **Imgdatac11=NULL;
	Imgdatac11=alloc_mem2double(Imgdatac11,Size_h,Size_w);

	double **Imgdatac12=NULL;
	Imgdatac12=alloc_mem2double(Imgdatac12,Size_h,Size_w);

	double **ImgdatacA=NULL;
	ImgdatacA=alloc_mem2double(ImgdatacA,Size_h,Size_w);
	
	double **ImgdatacB=NULL;
	ImgdatacB=alloc_mem2double(ImgdatacB,Size_h,Size_w);
	
	double **ImgdatacC=NULL;
	ImgdatacC=alloc_mem2double(ImgdatacC,Size_h,Size_w);

	double **ImgdatacD=NULL;
	ImgdatacD=alloc_mem2double(ImgdatacD,Size_h,Size_w);

	double **ImgdatacE=NULL;
	ImgdatacE=alloc_mem2double(ImgdatacE,Size_h,Size_w);

	double **ImgdatacF=NULL;
	ImgdatacF=alloc_mem2double(ImgdatacF,Size_h,Size_w);


	unsigned char **Imgdatac1c=NULL;
	Imgdatac1c=alloc_mem2(Imgdatac1c,Size_h,Size_w);
	
	unsigned char **Imgdatac2c=NULL;
	Imgdatac2c=alloc_mem2(Imgdatac2c,Size_h,Size_w);
	
	unsigned char **Imgdatac3c=NULL;
	Imgdatac3c=alloc_mem2(Imgdatac3c,Size_h,Size_w);
	
	unsigned char **Imgdatac4c=NULL;
	Imgdatac4c=alloc_mem2(Imgdatac4c,Size_h,Size_w);
	
	unsigned char **Imgdatac5c=NULL;
	Imgdatac5c=alloc_mem2(Imgdatac5c,Size_h,Size_w);
	
	unsigned char **Imgdatac6c=NULL;
	Imgdatac6c=alloc_mem2(Imgdatac6c,Size_h,Size_w);

	unsigned char **Imgdatac7c=NULL;
	Imgdatac7c=alloc_mem2(Imgdatac7c,Size_h,Size_w);

	unsigned char **Imgdatac8c=NULL;
	Imgdatac8c=alloc_mem2(Imgdatac8c,Size_h,Size_w);
	
	unsigned char **Imgdatac9c=NULL;
	Imgdatac9c=alloc_mem2(Imgdatac9c,Size_h,Size_w);

	unsigned char **Imgdatac10c=NULL;
	Imgdatac10c=alloc_mem2(Imgdatac10c,Size_h,Size_w);
	
	unsigned char **Imgdatac11c=NULL;
	Imgdatac11c=alloc_mem2(Imgdatac11c,Size_h,Size_w);

	unsigned char **Imgdatac12c=NULL;
	Imgdatac12c=alloc_mem2(Imgdatac12c,Size_h,Size_w);

	unsigned char **ImgdatacAc=NULL;
	ImgdatacAc=alloc_mem2(ImgdatacAc,Size_h,Size_w);
	
	unsigned char **ImgdatacBc=NULL;
	ImgdatacBc=alloc_mem2(ImgdatacBc,Size_h,Size_w);
	
	unsigned char **ImgdatacCc=NULL;
	ImgdatacCc=alloc_mem2(ImgdatacCc,Size_h,Size_w);

	unsigned char **ImgdatacDc=NULL;
	ImgdatacDc=alloc_mem2(ImgdatacDc,Size_h,Size_w);

	unsigned char **ImgdatacEc=NULL;
	ImgdatacEc=alloc_mem2(ImgdatacEc,Size_h,Size_w);

	unsigned char **ImgdatacFc=NULL;
	ImgdatacFc=alloc_mem2(ImgdatacFc,Size_h,Size_w);


	//	Conversion from 1 dimensional array to Multi dimensional array for easier manipulation in unsigned char format

	Imgdatac1c=oned22d(Imgdatac1c,Imagedatac1,Size_h,Size_w);
	Imgdatac2c=oned22d(Imgdatac2c,Imagedatac2,Size_h,Size_w);
	Imgdatac3c=oned22d(Imgdatac3c,Imagedatac3,Size_h,Size_w);
	Imgdatac4c=oned22d(Imgdatac4c,Imagedatac4,Size_h,Size_w);
	Imgdatac5c=oned22d(Imgdatac5c,Imagedatac5,Size_h,Size_w);
	Imgdatac6c=oned22d(Imgdatac6c,Imagedatac6,Size_h,Size_w);
	Imgdatac7c=oned22d(Imgdatac7c,Imagedatac7,Size_h,Size_w);
	Imgdatac8c=oned22d(Imgdatac8c,Imagedatac8,Size_h,Size_w);
	Imgdatac9c=oned22d(Imgdatac9c,Imagedatac9,Size_h,Size_w);
	Imgdatac10c=oned22d(Imgdatac10c,Imagedatac10,Size_h,Size_w);
	Imgdatac11c=oned22d(Imgdatac11c,Imagedatac11,Size_h,Size_w);
	Imgdatac12c=oned22d(Imgdatac12c,Imagedatac12,Size_h,Size_w);

	ImgdatacAc=oned22d(ImgdatacAc,ImagedatacA,Size_h,Size_w);
	ImgdatacBc=oned22d(ImgdatacBc,ImagedatacB,Size_h,Size_w);
	ImgdatacCc=oned22d(ImgdatacCc,ImagedatacC,Size_h,Size_w);
	ImgdatacDc=oned22d(ImgdatacDc,ImagedatacD,Size_h,Size_w);
	ImgdatacEc=oned22d(ImgdatacEc,ImagedatacE,Size_h,Size_w);
	ImgdatacFc=oned22d(ImgdatacFc,ImagedatacF,Size_h,Size_w);
	
	
	// Convert to double for unsigned char 
	
	Imgdatac1=convert2double(Imgdatac1c,Imgdatac1,Size_h,Size_w);
	Imgdatac2=convert2double(Imgdatac2c,Imgdatac2,Size_h,Size_w);
	Imgdatac3=convert2double(Imgdatac3c,Imgdatac3,Size_h,Size_w);
	Imgdatac4=convert2double(Imgdatac4c,Imgdatac4,Size_h,Size_w);
	Imgdatac5=convert2double(Imgdatac5c,Imgdatac5,Size_h,Size_w);
	Imgdatac6=convert2double(Imgdatac6c,Imgdatac6,Size_h,Size_w);
	Imgdatac7=convert2double(Imgdatac7c,Imgdatac7,Size_h,Size_w);
	Imgdatac8=convert2double(Imgdatac8c,Imgdatac8,Size_h,Size_w);
	Imgdatac9=convert2double(Imgdatac9c,Imgdatac9,Size_h,Size_w);
	Imgdatac10=convert2double(Imgdatac10c,Imgdatac10,Size_h,Size_w);
	Imgdatac11=convert2double(Imgdatac11c,Imgdatac11,Size_h,Size_w);
	Imgdatac12=convert2double(Imgdatac12c,Imgdatac12,Size_h,Size_w);

	ImgdatacA=convert2double(ImgdatacAc,ImgdatacA,Size_h,Size_w);
	ImgdatacB=convert2double(ImgdatacBc,ImgdatacB,Size_h,Size_w);
	ImgdatacC=convert2double(ImgdatacCc,ImgdatacC,Size_h,Size_w);
	ImgdatacD=convert2double(ImgdatacDc,ImgdatacD,Size_h,Size_w);
	ImgdatacE=convert2double(ImgdatacEc,ImgdatacE,Size_h,Size_w);
	ImgdatacF=convert2double(ImgdatacFc,ImgdatacF,Size_h,Size_w);

	//Initially taking the mean of the image to subtract the dc component
	double mean1,mean2,mean3,mean4,mean5,mean6,mean7,mean8,mean9,mean10,mean11,mean12, meanA, meanB,meanC,meanD,meanE,meanF;
	
	mean1=meanimage(Imgdatac1,Size_h,Size_w);
	mean2=meanimage(Imgdatac2,Size_h,Size_w);
	mean3=meanimage(Imgdatac3,Size_h,Size_w);
	mean4=meanimage(Imgdatac4,Size_h,Size_w);
	mean5=meanimage(Imgdatac5,Size_h,Size_w);
	mean6=meanimage(Imgdatac6,Size_h,Size_w);
	mean7=meanimage(Imgdatac7,Size_h,Size_w);
	mean8=meanimage(Imgdatac8,Size_h,Size_w);
	mean9=meanimage(Imgdatac9,Size_h,Size_w);
	mean10=meanimage(Imgdatac10,Size_h,Size_w);
	mean11=meanimage(Imgdatac11,Size_h,Size_w);
	mean12=meanimage(Imgdatac12,Size_h,Size_w);
	
	meanA=meanimage(ImgdatacA,Size_h,Size_w);
	meanB=meanimage(ImgdatacB,Size_h,Size_w);
	meanC=meanimage(ImgdatacC,Size_h,Size_w);
	meanD=meanimage(ImgdatacD,Size_h,Size_w);
	meanE=meanimage(ImgdatacE,Size_h,Size_w);
	meanF=meanimage(ImgdatacF,Size_h,Size_w);
	



	// Subtraction of dc component

	Imgdatac1=subtractdc(Imgdatac1,Size_h,Size_w,mean1);
	Imgdatac2=subtractdc(Imgdatac2,Size_h,Size_w,mean2);
	Imgdatac3=subtractdc(Imgdatac3,Size_h,Size_w,mean3);
	Imgdatac4=subtractdc(Imgdatac4,Size_h,Size_w,mean4);
	Imgdatac5=subtractdc(Imgdatac5,Size_h,Size_w,mean5);
	Imgdatac6=subtractdc(Imgdatac6,Size_h,Size_w,mean6);
	Imgdatac7=subtractdc(Imgdatac7,Size_h,Size_w,mean7);
	Imgdatac8=subtractdc(Imgdatac8,Size_h,Size_w,mean8);
	Imgdatac9=subtractdc(Imgdatac9,Size_h,Size_w,mean9);
	Imgdatac10=subtractdc(Imgdatac10,Size_h,Size_w,mean10);
	Imgdatac11=subtractdc(Imgdatac11,Size_h,Size_w,mean11);
	Imgdatac12=subtractdc(Imgdatac12,Size_h,Size_w,mean12);

	ImgdatacA=subtractdc(ImgdatacA,Size_h,Size_w,meanA);
	ImgdatacB=subtractdc(ImgdatacB,Size_h,Size_w,meanB);
	ImgdatacC=subtractdc(ImgdatacC,Size_h,Size_w,meanC);
	ImgdatacD=subtractdc(ImgdatacD,Size_h,Size_w,meanD);
	ImgdatacE=subtractdc(ImgdatacE,Size_h,Size_w,meanE);
	ImgdatacF=subtractdc(ImgdatacF,Size_h,Size_w,meanF);

	// Generating Laws filter.
	double* l5=new double[n];
	double* s5=new double[n];
	double* w5=new double[n];
	double* r5=new double[n];
	double* e5=new double[n];
	
	l5[0]=1; l5[1]=4; l5[2]=6; l5[3]=4; l5[4]=1;
	e5[0]=-1; e5[1]=-2; e5[2]=0; e5[3]=2; e5[4]=1;
	s5[0]=-1; s5[1]=0; s5[2]=2; s5[3]=0; s5[4]=-1;
	w5[0]=-1; w5[1]=2; w5[2]=0; w5[3]=-2; w5[4]=1;
	r5[0]=1; r5[1]=-4; r5[2]=6; r5[3]=-4; r5[4]=1;

	double **l5l5=NULL;
	l5l5=alloc_mem2double(l5l5,5,5);
	
	double **l5e5=NULL;
	l5e5=alloc_mem2double(l5e5,5,5);
		
	double **l5s5=NULL;
	l5s5=alloc_mem2double(l5s5,5,5);
	
	double **l5w5=NULL;
	l5w5=alloc_mem2double(l5w5,5,5);

	double **l5r5=NULL;
	l5r5=alloc_mem2double(l5r5,5,5);

//	
	double **e5l5=NULL;
	e5l5=alloc_mem2double(e5l5,5,5);
	
	double **e5e5=NULL;
	e5e5=alloc_mem2double(e5e5,5,5);
		
	double **e5s5=NULL;
	e5s5=alloc_mem2double(e5s5,5,5);
	
	double **e5w5=NULL;
	e5w5=alloc_mem2double(e5w5,5,5);
	
	double **e5r5=NULL;
	e5r5=alloc_mem2double(e5r5,5,5);

//
	
	double **s5l5=NULL;
	s5l5=alloc_mem2double(s5l5,5,5);
	
	double **s5e5=NULL;
	s5e5=alloc_mem2double(s5e5,5,5);
		
	double **s5s5=NULL;
	s5s5=alloc_mem2double(s5s5,5,5);
	
	double **s5w5=NULL;
	s5w5=alloc_mem2double(s5w5,5,5);
	
	double **s5r5=NULL;
	s5r5=alloc_mem2double(s5r5,5,5);
//

	double **w5l5=NULL;
	w5l5=alloc_mem2double(w5l5,5,5);
	
	double **w5e5=NULL;
	w5e5=alloc_mem2double(w5e5,5,5);
		
	double **w5s5=NULL;
	w5s5=alloc_mem2double(w5s5,5,5);
	
	double **w5w5=NULL;
	w5w5=alloc_mem2double(w5w5,5,5);
	
	double **w5r5=NULL;
	w5r5=alloc_mem2double(w5r5,5,5);
//

	double **r5l5=NULL;
	r5l5=alloc_mem2double(r5l5,5,5);
	
	double **r5e5=NULL;
	r5e5=alloc_mem2double(r5e5,5,5);
		
	double **r5s5=NULL;
	r5s5=alloc_mem2double(r5s5,5,5);
	
	double **r5w5=NULL;
	r5w5=alloc_mem2double(r5w5,5,5);
	
	double **r5r5=NULL;
	r5r5=alloc_mem2double(r5r5,5,5);
	
// Output of the Laws filters.
	cout<<endl;
	cout<<"\t\t L5L5"<<endl;
	l5l5=lawsfilter(l5,l5,l5l5);

	cout<<endl;
	cout<<"\t\t L5E5"<<endl;
	l5e5=lawsfilter(l5,e5,l5e5);
	
	cout<<endl;
	cout<<"\t\t L5W5"<<endl;
	l5w5=lawsfilter(l5,w5,l5w5);
	
	cout<<endl;
	cout<<"\t\t L5R5"<<endl;
	l5r5=lawsfilter(l5,r5,l5r5);
	
	cout<<endl;
	cout<<"\t\t L5S5"<<endl;
	l5s5=lawsfilter(l5,s5,l5s5);
//
	cout<<endl;
	cout<<"\t\t E5L5"<<endl;
	e5l5=lawsfilter(e5,l5,e5l5);

	cout<<endl;
	cout<<"\t\t E5E5"<<endl;
	e5e5=lawsfilter(e5,e5,e5e5);
	
	cout<<endl;
	cout<<"\t\t E5W5"<<endl;
	e5w5=lawsfilter(e5,w5,e5w5);
	
	cout<<endl;
	cout<<"\t\t E5R5"<<endl;
	e5r5=lawsfilter(e5,r5,e5r5);
	
	cout<<endl;
	cout<<"\t\t E5S5"<<endl;
	e5s5=lawsfilter(e5,s5,e5s5);

	//
	cout<<endl;
	cout<<"w5l5"<<endl;
	w5l5=lawsfilter(w5,l5,w5l5);

	cout<<endl;
	cout<<"w5e5"<<endl;
	w5e5=lawsfilter(w5,e5,w5e5);
	
	cout<<endl;
	cout<<"w5w5"<<endl;
	w5w5=lawsfilter(w5,w5,w5w5);
	
	cout<<endl;
	cout<<"w5r5"<<endl;
	w5r5=lawsfilter(w5,r5,w5r5);
	
	cout<<endl;
	cout<<"w5s5"<<endl;
	w5s5=lawsfilter(w5,s5,w5s5);

	//
	cout<<endl;
	cout<<"s5l5"<<endl;
	s5l5=lawsfilter(s5,l5,s5l5);

	cout<<endl;
	cout<<"s5e5"<<endl;
	s5e5=lawsfilter(s5,e5,s5e5);
	
	cout<<endl;
	cout<<"s5w5"<<endl;
	s5w5=lawsfilter(s5,w5,s5w5);
	
	cout<<endl;
	cout<<"s5r5"<<endl;
	s5r5=lawsfilter(l5,r5,s5r5);
	
	cout<<endl;
	cout<<"s5s5"<<endl;
	s5s5=lawsfilter(s5,s5,s5s5);

	cout<<endl;
	cout<<"r5l5"<<endl;
	r5l5=lawsfilter(r5,l5,r5l5);

	cout<<endl;
	cout<<"r5e5"<<endl;
	r5e5=lawsfilter(r5,e5,r5e5);
	
	cout<<endl;
	cout<<"r5w5"<<endl;
	r5w5=lawsfilter(r5,w5,r5w5);
	
	cout<<endl;
	cout<<"r5r5"<<endl;
	r5r5=lawsfilter(r5,r5,r5r5);
	
	cout<<endl;
	cout<<"r5s5"<<endl;
	r5s5=lawsfilter(r5,s5,r5s5);

	// Making the image textures set a 3 dimensional array where the 3rd dimesnion denotes the number of the image.

	double ***op1=NULL;
	op1=alloc_memdouble(op1,Size_h,Size_w,25);
	double ***op2=NULL;
	op2=alloc_memdouble(op2,Size_h,Size_w,25);
	double ***op3=NULL;
	op3=alloc_memdouble(op3,Size_h,Size_w,25);
	double ***op4=NULL;
	op4=alloc_memdouble(op4,Size_h,Size_w,25);
	double ***op5=NULL;
	op5=alloc_memdouble(op5,Size_h,Size_w,25);
	double ***op6=NULL;
	op6=alloc_memdouble(op6,Size_h,Size_w,25);
	double ***op7=NULL;
	op7=alloc_memdouble(op7,Size_h,Size_w,25);
	double ***op8=NULL;
	op8=alloc_memdouble(op8,Size_h,Size_w,25);
	double ***op9=NULL;
	op9=alloc_memdouble(op9,Size_h,Size_w,25);
	double ***op10=NULL;
	op10=alloc_memdouble(op10,Size_h,Size_w,25);
	double ***op11=NULL;
	op11=alloc_memdouble(op11,Size_h,Size_w,25);
	double ***op12=NULL;
	op12=alloc_memdouble(op12,Size_h,Size_w,25);

	double ***opA=NULL;
	opA=alloc_memdouble(opA,Size_h,Size_w,25);
	double ***opB=NULL;
	opB=alloc_memdouble(opB,Size_h,Size_w,25);
	double ***opC=NULL;
	opC=alloc_memdouble(opC,Size_h,Size_w,25);
	double ***opD=NULL;
	opD=alloc_memdouble(opD,Size_h,Size_w,25);
	double ***opE=NULL;
	opE=alloc_memdouble(opE,Size_h,Size_w,25);
	double ***opF=NULL;
	opF=alloc_memdouble(opF,Size_h,Size_w,25);


	
	
	double ***filterset=NULL;
	filterset=alloc_memdouble(filterset,5,5,25);

	filterset=filterset25(l5l5,filterset,0);
	filterset=filterset25(l5e5,filterset,1);
	filterset=filterset25(l5w5,filterset,2);
	filterset=filterset25(l5r5,filterset,3);
	filterset=filterset25(l5s5,filterset,4);

	filterset=filterset25(e5l5,filterset,5);
	filterset=filterset25(e5e5,filterset,6);
	filterset=filterset25(e5w5,filterset,7);
	filterset=filterset25(e5r5,filterset,8);
	filterset=filterset25(e5s5,filterset,9);

	filterset=filterset25(w5l5,filterset,10);
	filterset=filterset25(w5e5,filterset,11);
	filterset=filterset25(w5w5,filterset,12);
	filterset=filterset25(w5r5,filterset,13);
	filterset=filterset25(w5s5,filterset,14);

	filterset=filterset25(r5l5,filterset,15);
	filterset=filterset25(r5e5,filterset,16);
	filterset=filterset25(r5w5,filterset,17);
	filterset=filterset25(r5r5,filterset,18);
	filterset=filterset25(r5s5,filterset,19);

	filterset=filterset25(s5l5,filterset,20);
	filterset=filterset25(s5e5,filterset,21);
	filterset=filterset25(s5w5,filterset,22);
	filterset=filterset25(s5r5,filterset,23);
	filterset=filterset25(s5s5,filterset,24);

	// Each texture image now has 25 filtered copies stored in op
	op1=texture_app(Imgdatac1,filterset,Size_h, Size_w,n);
	op2=texture_app(Imgdatac2,filterset,Size_h, Size_w,n);
	op3=texture_app(Imgdatac3,filterset,Size_h, Size_w,n);
	op4=texture_app(Imgdatac4,filterset,Size_h, Size_w,n);
	
	op5=texture_app(Imgdatac5,filterset,Size_h, Size_w,n);
	op6=texture_app(Imgdatac6,filterset,Size_h, Size_w,n);
	op7=texture_app(Imgdatac7,filterset,Size_h, Size_w,n);
	op8=texture_app(Imgdatac8,filterset,Size_h, Size_w,n);
	
	op9=texture_app(Imgdatac9,filterset,Size_h, Size_w,n);
	op10=texture_app(Imgdatac10,filterset,Size_h, Size_w,n);
	op11=texture_app(Imgdatac11,filterset,Size_h, Size_w,n);
	op12=texture_app(Imgdatac12,filterset,Size_h, Size_w,n);


	opA=texture_app(ImgdatacA,filterset,Size_h, Size_w,n);
	opB=texture_app(ImgdatacB,filterset,Size_h, Size_w,n);
	opC=texture_app(ImgdatacC,filterset,Size_h, Size_w,n);
	opD=texture_app(ImgdatacD,filterset,Size_h, Size_w,n);
	opE=texture_app(ImgdatacE,filterset,Size_h, Size_w,n);
	opF=texture_app(ImgdatacF,filterset,Size_h, Size_w,n);



	// Making the feature vector set as 12*25 matrix.
	
	double **f111=NULL;
	f111=alloc_mem2double(f111,12,25);
	double **f111_i=NULL;
	f111_i=alloc_mem2double(f111_i,12,25);
	double **f112=NULL;
	f112=alloc_mem2double(f112,4,25);

	double **f111_test=NULL;
	f111_test=alloc_mem2double(f111_test,6,25);
	double **f111_i_test=NULL;
	f111_i_test=alloc_mem2double(f111_i_test,6,25);
	double **f112_test=NULL;
	f112_test=alloc_mem2double(f112_test,4,25);


	double **f111_test3d=NULL;
	f111_test3d=alloc_mem2double(f111_test3d,12,3);
	double **f111_i_test3d=NULL;
	f111_i_test3d=alloc_mem2double(f111_i_test3d,12,3);
	double **f112_test3d=NULL;
	f112_test3d=alloc_mem2double(f112_test3d,4,3);

	double *f1=new double[25];
	double *f2=new double[25];
	double *f3=new double[25];
	double *f4=new double[25];
	double *f5=new double[25];
	double *f6=new double[25];
	double *f7=new double[25];
	double *f8=new double[25];
	double *f9=new double[25];
	double *f10=new double[25];
	double *f11=new double[25];
	double *f12=new double[25];

	double *fA=new double[25];
	double *fB=new double[25];
	double *fC=new double[25];
	double *fD=new double[25];
	double *fE=new double[25];
	double *fF=new double[25];



	f1=featurevalues(op1,f1,Size_w,Size_h);
	f2=featurevalues(op2,f2,Size_w,Size_h);
	f3=featurevalues(op3,f3,Size_w,Size_h);
	f4=featurevalues(op4,f4,Size_w,Size_h);

	f5=featurevalues(op5,f5,Size_w,Size_h);
	f6=featurevalues(op6,f6,Size_w,Size_h);
	f7=featurevalues(op7,f7,Size_w,Size_h);
	f8=featurevalues(op8,f8,Size_w,Size_h);
	
	f9=featurevalues(op9,f9,Size_w,Size_h);
	f10=featurevalues(op10,f10,Size_w,Size_h);
	f11=featurevalues(op11,f11,Size_w,Size_h);
	f12=featurevalues(op12,f12,Size_w,Size_h);

	fA=featurevalues(opA,fA,Size_w,Size_h);
	fB=featurevalues(opB,fB,Size_w,Size_h);
	fC=featurevalues(opC,fC,Size_w,Size_h);
	fD=featurevalues(opD,fD,Size_w,Size_h);
	fE=featurevalues(opE,fE,Size_w,Size_h);
	fF=featurevalues(opF,fF,Size_w,Size_h);

	cout<<endl;
	cout<<"feature vectors calculated successfully"<<endl;
	cout<<endl;
	
	// Making the feature vector set
	
	for(int i=0;i<25;i++)
		{
			f111[0][i]=f1[i];
			f111[1][i]=f2[i];
			f111[2][i]=f3[i];
			f111[3][i]=f4[i];
			f111[4][i]=f5[i];
			f111[5][i]=f6[i];
			f111[6][i]=f7[i];
			f111[7][i]=f8[i];
			f111[8][i]=f9[i];
			f111[9][i]=f10[i];
			f111[10][i]=f11[i];
			f111[11][i]=f12[i];
		}



	for(int i=0;i<12;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<f111[i][j]<<"\t";
		}
		cout<<endl;
		cout<<endl;
		
	}

	for(int i=0;i<25;i++)
		{
			f111_test[0][i]=fA[i];
			f111_test[1][i]=fB[i];
			f111_test[2][i]=fC[i];
			f111_test[3][i]=fD[i];
			f111_test[4][i]=fE[i];
			f111_test[5][i]=fF[i];
			
		}



	// Normalisation by mean and Standard deviation
	double mean[25],sd1[25];
	for(int i=0;i<25;i++)
	{mean[i]=0;
	sd1[i]=0;
	}

	for(int i=0;i<25;i++)
	{
	mean[i]=meanfv(f111,12, i);
	//cout<<"mean: "<<mean[i]<<endl;

	sd1[i]=sd(f111,mean[i], 12,i);
	//cout<<sd1[i]<<endl;
	//cout<<endl;
	}

	//// Normalised feature vector set.

	for(int i=0;i<12;i++)
	{
		for(int j=0;j<25;j++)
		{
			f111_i[i][j]=(f111[i][j]-mean[j])/sd1[j];
			//cout<<f111_i[i][j]<<" \t";
		}
		//cout<<endl;

	}

		
	ofstream file1;
	file1.open("high_dim.xls",ios::out);
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<25;j++)
		{
			file1<<f111_i[i][j]<<"\t";
		}
		file1<<endl;	
	}
	file1.close();

	// Getting back PCA output from Matlab
	double **f111_test3=NULL;
	f111_test3=alloc_mem2double(f111_test3,12,3);


	ifstream file2;
	file2.open("D:/cplusplus/HW3/prob1a/k3.txt");
	for(int i=0;i<12;i++)
	{
		for(int j=0;j<3;j++)
		{
			file2>>f111_test3[i][j];
		}		
	}
	file2.close();


	for(int i=0;i<12;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<f111_test3[i][j]<<"\t";
		}
		cout<<endl;	
	}

	double **f112_test3=NULL;
	f112_test3=alloc_mem2double(f112_test3,4,3);

	
	// Obtaining the 4 characteristics centroids upon which the nesarest neighbour test needs to be carried out
	f112=Kmeans(f111_i,f112,4);

//-------------------------------------------------------------------------------------------------------------------------------
	// Training ends , Testing Begins
	
	cout<<endl;
	cout<<"feature vector set for training"<<endl;
	cout<<endl;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<25;j++)
		{
			cout<<f111_test[i][j]<<" \t";
		}
	cout<<endl;
	}

	double mean_test[25],sd1_test[25];
	for(int i=0;i<25;i++)
	{
	mean_test[i]=0;
	sd1_test[i]=0;
	}

	for(int i=0;i<25;i++)
	{
	mean_test[i]=meanfv(f111_test,6, i);
	//cout<<"mean: "<<mean[i]<<endl;

	sd1_test[i]=sd(f111_test,mean_test[i], 6,i);
	//cout<<sd1[i]<<endl;
	//cout<<endl;
	}

	cout<<endl;

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<25;j++)
		{
			f111_i_test[i][j]=(f111_test[i][j]-mean_test[j])/sd1_test[j];
			//
			cout<<f111_i_test[i][j]<<" \t";
		}
		cout<<endl;
	}

	ofstream file5;
	file5.open("high_dim_test.xls",ios::out);
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<25;j++)
		{
			file5<<f111_i_test[i][j]<<"\t";
		}
		file5<<endl;	
	}
	file5.close();


	//Checking for the nearest neighbour and assignment to that centroid index.

	// Minimum value is obtained in this case.

	double **distance1=NULL;
	distance1=alloc_mem2double(distance1,6,4);// 16 case.

	for(int i=0;i<6;i++)
	{
		for(int r=0;r<4;r++)
		{	
			double sum=0.0;
			for(int k=0;k<25;k++)
			{	
			 sum=sum+((f112[r][k]-f111_i_test[i][k])*(f112[r][k]-f111_i_test[i][k]));// sum of each values for distance.
			//cout<<f112[r][k]<<endl;
			}
			distance1[i][r]=sqrt(sum);
		//cout<<i<< "  "<<distance1[i][r]<<endl;
		}
	//cout<< "   "<<endl;
	}

	cout<<endl;
	cout<<"Classified output for Textures"<<endl;
	for(int i=0;i<6;i++)
	{	
		int index=0;
		double min=distance1[i][0];

		for(int r=0;r<4;r++)
		{
			if(min>distance1[i][r])
			{
				min=distance1[i][r];
				index=r;
			}	
		}
		
		if(index==0)
		{cout<<"bark"<<endl;}
		if(index==1)
		{cout<<"sand"<<endl;}
		if(index==2)
		{cout<<"straw"<<endl;}
		if(index==3)
		{cout<<"grass"<<endl;}	
	}

//------------------------------------------------------------------------------------------------------------------------
	cout<<endl;
	cout<<endl;
	cout<<"PCA for 3D"<<endl;

	f112_test3=Kmeans3d(f111_test3,f112_test3,4);
	cout<<endl;
	cout<<"3d  Training begins here"<<endl;


	//-------------------------------------------------------------------------------------------------------------------------------
	
	ifstream file4;
	file4.open("D:/cplusplus/HW3/prob1a/k6.txt");
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			file4>>f111_test3d[i][j];
		}		
	}
	file4.close();

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<f111_test3d[i][j]<<"\t";
		}
		cout<<endl;
	}


	double **distance13d=NULL;
	distance13d=alloc_mem2double(distance13d,6,4);// 16 case.

	for(int i=0;i<6;i++)
	{
		for(int r=0;r<4;r++)
		{	
			double sum=0.0;
			for(int k=0;k<3;k++)
			{	
			 sum=sum+((f112_test3[r][k]-f111_i_test3d[i][k])*(f112_test3[r][k]-f111_i_test3d[i][k]));// sum of each values for distance.
			//cout<<f112[r][k]<<endl;
			}
			distance13d[i][r]=sqrt(sum);
		//cout<<i<< "  "<<distance1[i][r]<<endl;
		}
	//cout<< "   "<<endl;
	}

	cout<<endl;
	cout<<"Classified output for Textures"<<endl;
	for(int i=0;i<6;i++)
	{	
		int index=0;
		double min=distance1[i][0];

		for(int r=0;r<4;r++)
		{
			if(min>distance1[i][r])
			{
				min=distance1[i][r];
				index=r;
			}	
		}
		
		if(index==0)
		{cout<<"bark"<<endl;}
		if(index==1)
		{cout<<"sand"<<endl;}
		if(index==2)
		{cout<<"straw"<<endl;}
		if(index==3)
		{cout<<"grass"<<endl;}	
	}


	//	De-allocation of memory after processing.
	dealloc_mem2(Imgdatac1c,Size_h,Size_w);
	dealloc_mem2(Imgdatac2c,Size_h,Size_w);
	dealloc_mem2(Imgdatac3c,Size_h,Size_w);
	dealloc_mem2(Imgdatac4c,Size_h,Size_w);
	dealloc_mem2(Imgdatac5c,Size_h,Size_w);
	dealloc_mem2(Imgdatac6c,Size_h,Size_w);
	dealloc_mem2(Imgdatac7c,Size_h,Size_w);
	dealloc_mem2(Imgdatac8c,Size_h,Size_w);
	dealloc_mem2(Imgdatac9c,Size_h,Size_w);
	dealloc_mem2(Imgdatac10c,Size_h,Size_w);
	dealloc_mem2(Imgdatac11c,Size_h,Size_w);
	dealloc_mem2(Imgdatac12c,Size_h,Size_w);
	dealloc_mem2(ImgdatacAc,Size_h,Size_w);
	dealloc_mem2(ImgdatacBc,Size_h,Size_w);
	dealloc_mem2(ImgdatacCc,Size_h,Size_w);
	dealloc_mem2(ImgdatacDc,Size_h,Size_w);
	dealloc_mem2(ImgdatacEc,Size_h,Size_w);
	dealloc_mem2(ImgdatacFc,Size_h,Size_w);

	dealloc_mem2double(Imgdatac1,Size_h,Size_w);
	dealloc_mem2double(Imgdatac2,Size_h,Size_w);
	dealloc_mem2double(Imgdatac3,Size_h,Size_w);
	dealloc_mem2double(Imgdatac4,Size_h,Size_w);
	dealloc_mem2double(Imgdatac5,Size_h,Size_w);
	dealloc_mem2double(Imgdatac6,Size_h,Size_w);
	dealloc_mem2double(Imgdatac7,Size_h,Size_w);
	dealloc_mem2double(Imgdatac8,Size_h,Size_w);
	dealloc_mem2double(Imgdatac9,Size_h,Size_w);
	dealloc_mem2double(Imgdatac10,Size_h,Size_w);
	dealloc_mem2double(Imgdatac11,Size_h,Size_w);
	dealloc_mem2double(Imgdatac12,Size_h,Size_w);
	dealloc_mem2double(ImgdatacA,Size_h,Size_w);
	dealloc_mem2double(ImgdatacB,Size_h,Size_w);
	dealloc_mem2double(ImgdatacC,Size_h,Size_w);
	dealloc_mem2double(ImgdatacD,Size_h,Size_w);
	dealloc_mem2double(ImgdatacE,Size_h,Size_w);
	dealloc_mem2double(ImgdatacF,Size_h,Size_w);

	dealloc_mem2double(l5l5,5,5);
	dealloc_mem2double(l5e5,5,5);
	dealloc_mem2double(l5w5,5,5);
	dealloc_mem2double(l5s5,5,5);
	dealloc_mem2double(l5r5,5,5);
	
	dealloc_mem2double(e5l5,5,5);
	dealloc_mem2double(e5e5,5,5);
	dealloc_mem2double(e5w5,5,5);
	dealloc_mem2double(e5r5,5,5);
	dealloc_mem2double(e5s5,5,5);

	dealloc_mem2double(w5l5,5,5);
	dealloc_mem2double(w5e5,5,5);
	dealloc_mem2double(w5w5,5,5);
	dealloc_mem2double(w5r5,5,5);
	dealloc_mem2double(w5s5,5,5);

	dealloc_mem2double(r5l5,5,5);
	dealloc_mem2double(r5e5,5,5);
	dealloc_mem2double(r5w5,5,5);
	dealloc_mem2double(r5r5,5,5);
	dealloc_mem2double(r5s5,5,5);

	dealloc_mem2double(s5l5,5,5);
	dealloc_mem2double(s5e5,5,5);
	dealloc_mem2double(s5w5,5,5);
	dealloc_mem2double(s5r5,5,5);
	dealloc_mem2double(s5s5,5,5);


	delete[] Imagedatac1;
	delete[] Imagedatac2;
	delete[] Imagedatac3;
	delete[] Imagedatac4;
	delete[] Imagedatac5;
	delete[] Imagedatac6;
	delete[] Imagedatac7;
	delete[] Imagedatac8;
	delete[] Imagedatac9;
	delete[] Imagedatac10;
	delete[] Imagedatac11;
	delete[] Imagedatac12;
	delete[] ImagedatacA;
	delete[] ImagedatacB;
	delete[] ImagedatacC;
	delete[] ImagedatacD;
	delete[] ImagedatacE;
	delete[] ImagedatacF;
	return 0;
}


