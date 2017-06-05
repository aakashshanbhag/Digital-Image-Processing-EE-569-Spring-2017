
#include "stdafx.h"
#include <iostream>
#include "Header1.h"
#include <math.h>
#include <stdio.h>

using namespace std;
#include <fstream>
int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	
	if(argc<3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<< "program_name input_image.raw output_image.raw Size_h Size_w input.xls output_matched.xls "<< endl;
		return 0;
	}
	
	int BytesPerPixel1=3;
	int Size_h,Size_w ;
	
	Size_h=atoi(argv[3]);
	Size_w=atoi(argv[4]);
	
	//	Define 1 d array fr image printing
	
	unsigned char *Imagedata;
	unsigned char *Imagedata2;

	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	
	//	Read file.

	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel1);
	
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel1);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel1);

	//	Conversion from 1d array to multidimensional array.
	
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel1);
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel1);

	int countr[256]={},countg[256]={},countb[256]={};// Input histogram
	int countlr[256]={},countlg[256]={},countlb[256]={};// Output histogram
	float count1r[256]={},count1g[256]={},count1b[256]={};// PDF
	float count2r[256]={},count2g[256]={},count2b[256]={};//	CDF
	int newpixelr[256]={},newpixelg[256]={},newpixelb[256]={};// Mapping index.
	
	//	Gaussian requirement
	float count1r1[256]={},count1g1[256]={},count1b1[256]={};
	float count2r1[256]={},count2g1[256]={},count2b1[256]={};//cdf
	int newpixelr1[256]={},newpixelg1[256]={},newpixelb1[256]={};
	
	int newpixelr2[256]={},newpixelg2[256]={},newpixelb2[256]={};
	
	//	Initialisation of count to 0 
	for(int i=0;i<256;i++)
	{
	countr[i]=0;countg[i]=0;countb[i]=0;
	countlr[i]=0;countlg[i]=0;countlb[i]=0;
	count1r[i]=0;count1g[i]=0;count1b[i]=0;
	count2r[i]=0;count2g[i]=0;count2b[i]=0;
	newpixelr[i]=0;newpixelg[i]=0;newpixelb[i]=0;

	count1r1[i]=0;count1g1[i]=0;count1b1[i]=0;
	count2r1[i]=0;count2g1[i]=0;count2b1[i]=0;
	newpixelr1[i]=0;newpixelg1[i]=0;newpixelb1[i]=0;

	newpixelr2[i]=0;newpixelg2[i]=0;newpixelb2[i]=0;

	}

	//Histogram count of input.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countr[Imgdata[i][j][0]]++);
			(countg[Imgdata[i][j][1]]++);
			(countb[Imgdata[i][j][2]]++);
		}
	}

	// Distribution of Gaussian PDF
	int mean=70,sd=20;
	float pi=3.14159;
	for(int i=0;i<256;i++)
	{
			count1r1[i]=exp(-1.0*pow((i-70.0),2.0)/(2.0*(400.0)))* (1.0/((sqrt(2*pi*20*20))));
			count1g1[i]=exp(-1.0*pow((i-70.0),2.0)/(2.0*(400.0)))* (1.0/((sqrt(2*pi*20*20))));
			count1b1[i]=exp(-1.0*pow((i-70.0),2.0)/(2.0*(400.0)))* (1.0/((sqrt(2*pi*20*20))));

	}
	
	//	Calculation of CDF for Gaussian distribution.
	for(int i=1;i<255;i++)
	{
			count2r1[0]=count1r1[0];
			count2r1[i]=count1r1[i]+count2r1[i-1];
			count2r1[255]=1;
			
			count2g1[0]=count1g1[0];
			count2g1[i]=count1g1[i]+count2g1[i-1];
			count2g1[255]=1;
			
			count2b1[0]=count1b1[0];
			count2b1[i]=count1b1[i]+count2b1[i-1];
			count2b1[255]=1;
	}

	//	PDF calculation of input image.
	for(int i=0;i<256;i++)
	{
	count1r[i]=countr[i]/(1.0*(Size_w*Size_h));
	count1g[i]=countg[i]/(1.0*(Size_w*Size_h));
	count1b[i]=countb[i]/(1.0*(Size_w*Size_h));
	}
	
	
	//	CDF calculation
	for(int i=1;i<255;i++)
	{		
			count2r[0]=count1r[0];
			count2r[i]=count1r[i]+count2r[i-1];
			count2r[255]=1;
			
			count2g[0]=count1g[0];
			count2g[i]=count1g[i]+count2g[i-1];
			count2g[255]=1;
			
			count2b[0]=count1b[0];
			count2b[i]=count1b[i]+count2b[i-1];
			count2b[255]=1;
	}
			

	//to renormalise
	for(int i=0;i<256;i++)
	{
	count2r[i]=count2r[i]*255.0;
	count2g[i]=count2g[i]*255.0;
	count2b[i]=count2b[i]*255.0;

	count2r1[i]=count2r1[i]*255.0;
	count2g1[i]=count2g1[i]*255.0;
	count2b1[i]=count2b1[i]*255.0;
	
	}
	//	Histogram mapping

	for(int i=0;i<256;i++)
	{
	newpixelr[i]=floor(count2r[i]);
	newpixelg[i]=floor(count2g[i]);
	newpixelb[i]=floor(count2b[i]);
	
	
	newpixelr1[i]=floor(count2r1[i]);
	newpixelg1[i]=floor(count2g1[i]);
	newpixelb1[i]=floor(count2b1[i]);
	}

	//Many to one mapping after both input and given distribution have been converted to equalised values.

	//==============red
	int flag=1;
	for(int i=0;i<256;i++)
	{
		if(flag==1)
		{
		for (int j=0;j<256;j++)
			{
				if(newpixelr1[j]>=newpixelr[i] && flag==1)
				{
					newpixelr2[i]=j;
					flag=0;
				}
			}
		flag=1;
		}
	}	

	//-------------------green
	int flag1=1;
	for(int i=0;i<256;i++)
	{
		if(flag1==1)
		{
		for (int j=0;j<256;j++)
			{
				if(newpixelg1[j]>=newpixelg[i] && flag1==1)
				{
					newpixelg2[i]=j;
					flag1=0;
				}
			}
		flag1=1;
		}
	}

	//=============blue

	int flag2=1;
	for(int i=0;i<256;i++)
	{
		if(flag2==1)
		{
		for (int j=0;j<256;j++)
			{
				if(newpixelb1[j]>=newpixelb[i] && flag2==1)
				{
					newpixelb2[i]=j;
					flag2=0;
				}
			}
		flag2=1;
		}
	}

	
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			img1[i][j][0]=newpixelr2[Imgdata[i][j][0]];
			img1[i][j][1]=newpixelg2[Imgdata[i][j][1]];
			img1[i][j][2]=newpixelb2[Imgdata[i][j][2]];
		}
	}

	// Histogram Calculation.

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countlr[img1[i][j][0]]++);
			(countlg[img1[i][j][1]]++);
			(countlb[img1[i][j][2]]++);
		}
	}
	// Conversion from multi dimensional array to 1 d array
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);

	// Writing back the equalised histogram.
	filewrite(file,argv[2],Imagedata2,Size_h,Size_w,BytesPerPixel1);

//-----------------------------------------------------	
	//	Filewrite fr hist dataset.
	ofstream file1;
	file1.open(argv[5],ios::out);
	for(int i=0;i<256;i++)
	{
		file1<<i<<" \t     "<<int(countr[i])<<" \t     "<<int(countg[i])<<" \t     "<<int(countb[i])<<endl;

	}
	file1.close();

	//Output matched histogram data.
	ofstream file2;
	file2.open(argv[6],ios::out);
	for(int i=0;i<256;i++)
	{
		file2<<i<<" \t     "<<int(countlr[i])<<"\t      "<<int(countlg[i])<<" \t     "<<int(countlb[i])<<endl;
	}
	file2.close();


//------------------------------------------------------	
	//De-allocate memory after usage.
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);

	delete[] Imagedata;
	delete[] Imagedata2;
	
	return 0;
}