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
	
	
	int BytesPerPixel1=3;
	int Size_h,Size_w ;
	if(argc<3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<< "program_name input_image.raw output_image.raw Size_h Size_w input.xls output_equalised.xls "<< endl;
		return 0;
	}
	
	Size_h=atoi(argv[3]);
	Size_w=atoi(argv[4]);
	
	//Define 1 d array fr image printing
	
	unsigned char *Imagedata;
	unsigned char *Imagedata2;

	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	
	//Read file.

	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel1);

	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel1);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel1);
//---------------------------------------------------------------------------------------------------------------
	
	//Conversion from 1d array to multidimensional array.
	
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel1);
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel1);
//---------------------------------------------------------------------------------------------------------------
	//Count to calculate the pdf,cdf and histograms.
	
	int countr[256]={},countg[256]={},countb[256]={};// Input histogram
	int countlr[256]={},countlg[256]={},countlb[256]={};// Output histogram
	float count1r[256]={},count1g[256]={},count1b[256]={};//	PDF
	float count2r[256]={},count2g[256]={},count2b[256]={};//	CDF
	unsigned char newpixelr[256]={},newpixelg[256]={},newpixelb[256]={};// Mapping.
	
	// Initial array set to 0.
	for(int i=0;i<256;i++)
	{
	countr[i]=0;countg[i]=0;countb[i]=0;
	countlr[i]=0;countlg[i]=0;countlb[i]=0;
	count1r[i]=0;count1g[i]=0;count1b[i]=0;
	count2r[i]=0;count2g[i]=0;count2b[i]=0;
	newpixelr[i]=0;newpixelg[i]=0;newpixelb[i]=0;
	}

	//Count generation for histogram.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countr[Imgdata[i][j][0]]++);
			(countg[Imgdata[i][j][1]]++);
			(countb[Imgdata[i][j][2]]++);
		}
	}

	//Probability generation.
	for(int i=0;i<256;i++)
	{
	count1r[i]=countr[i]/(1.0*(Size_w*Size_h));
	count1g[i]=countg[i]/(1.0*(Size_w*Size_h));
	count1b[i]=countb[i]/(1.0*(Size_w*Size_h));
	}
	
	
	//Cdf generated for each of the individual channels.
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

	//Renormalise to get count
	for(int i=0;i<256;i++)
	{
	count2r[i]=count2r[i]*255.0;
	count2g[i]=count2g[i]*255.0;
	count2b[i]=count2b[i]*255.0;
	}
	
	// Floor to round off to the nearest integer.
	for(int i=0;i<256;i++)
	{
	newpixelr[i]=floor(count2r[i]);
	newpixelg[i]=floor(count2g[i]);
	newpixelb[i]=floor(count2b[i]);
	}

	//Oneto one mapping
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			img1[i][j][0]=newpixelr[Imgdata[i][j][0]];
			img1[i][j][1]=newpixelg[Imgdata[i][j][1]];
			img1[i][j][2]=newpixelb[Imgdata[i][j][2]];
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
//---------------------------------------------------------------------------------------------------------------
	// Conversion from multi dimensional array to 1 d array
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);
//---------------------------------------------------------------------------------------------------------------
	// Writing back the equalised histogram.
	filewrite(file,argv[2],Imagedata2,Size_h,Size_w,BytesPerPixel1);

//---------------------------------------------------------------------------------------------------------------	
	//filewrite fr hist dataset.
	ofstream file1;
	file1.open(argv[5],ios::out);
	for(int i=0;i<256;i++)
	{
		file1<<i<<" \t     "<<int(countr[i])<<" \t     "<<int(countg[i])<<" \t     "<<int(countb[i])<<endl;

	}
	file1.close();

	ofstream file2;
	file2.open(argv[6],ios::out);
	for(int i=0;i<256;i++)
	{
		file2<<i<<" \t     "<<int(countlr[i])<<"\t      "<<int(countlg[i])<<" \t     "<<int(countlb[i])<<endl;
	}
	file2.close();

	// Transfer curve data
	ofstream file3;
	file3.open("transfer_curve.xls",ios::out);
	for(int i=0;i<256;i++)
	{
		file3<<i<<" \t     "<<int(newpixelr[i])<<"\t      "<<int(newpixelg[i])<<" \t     "<<int(newpixelb[i])<<endl;
	}
	file3.close();

//---------------------------------------------------------------------------------------------------------------	
	// Free memory after dynamic allocation.
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);


	delete[] Imagedata;
	delete[] Imagedata2;
	
	return 0;
}
	


