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
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout << "program_name.exe input_image.raw output_image.raw Size_h Size_w input.xls output_equalised.xls " << endl;
		return 0;
	}
	
	
	int BytesPerPixel1=1;
	int Size_h,Size_w ;
	
	Size_h=atoi(argv[3]);
	Size_w=atoi(argv[4]);
//------------------------------------------------------------------------------------------------------	
	//	Define 1 d array fr image printing
	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	
//------------------------------------------------------------------------------------------------------
	//	Reading the image as a first parameter
	fileread(file,argv[1],Imagedatac,Size_h,Size_w,BytesPerPixel1);
//------------------------------------------------------------------------------------------------------	
	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	
//------------------------------------------------------------------------------------------------------
	//	Conversion from 1d array to multidimensioal array.
	Imgdatac=oned22d(Imgdatac,Imagedatac,Size_h,Size_w);
	Imgdatam=oned22d(Imgdatam,Imagedatam,Size_h,Size_w);
	
	int count[256]={};//Histogram input
	int countb[256]={};//Histogram output 
	float count1[256]={};//pdf
	float count2[256]={};//cdf
	unsigned char newpixel[256]={};//mapping count
	
	// Initialization to a set of zeros.
	for(int i=0;i<256;i++)
	{count[i]=0;countb[i]=0;count1[i]=0;count2[i]=0;newpixel[i]=0;}
//------------------------------------------------------------------------------------------------------
	//	Count calculation for input histogram
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(count[Imgdatac[i][j]]++);
		}
	}

//------------------------------------------------------------------------------------------------------	
	//	Probability calculation.
	for(int i=0;i<256;i++)
	{count1[i]=count[i]/(1.0*(Size_w*Size_h));
	}

	//	Cdf calculation.
	for(int i=1;i<255;i++)
	{		count2[0]=count1[0];
			count2[i]=count1[i]+count2[i-1];
			count2[255]=1;
	}

	//	Renormalise
	for(int i=0;i<256;i++)
	{count2[i]=count2[i]*255.0;
	}

	//	Floor Calculation.
	for(int i=0;i<256;i++)
	{newpixel[i]=floor(count2[i]);
	}


	//	Oneto one mapping
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			Imgdatam[i][j]=newpixel[Imgdatac[i][j]];
		}
	}

	//	New histogram count.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countb[Imgdatam[i][j]]++);
		}
	}

//------------------------------------------------------------------------------------------------------
	// Conversion of multi deimensional array to 1 dimensional array

	Imagedatam=twod21d(Imagedatam,Imgdatam,Size_h,Size_w);
	
	filewrite(file,argv[2],Imagedatam,Size_h,Size_w,BytesPerPixel1);

//------------------------------------------------------------------------------------------------------
	//Filewrite for hist dataset.
	ofstream file1;//input hist
	file1.open(argv[5],ios::out);
	for(int i=0;i<256;i++)
	{
		file1<<i<<" \t     "<<int(count[i])<<endl;
	}
	file1.close();

	ofstream file2;//equalised hist
	file2.open(argv[6],ios::out);
	for(int i=0;i<256;i++)
	{
		file2<<i<<" \t     "<<int(countb[i])<<endl;
	}
	file2.close();

	ofstream file3;//matched hist
	file3.open("transfer_curve.xls",ios::out);
	for(int i=0;i<256;i++)
	{
		file3<<i<<" \t     "<<int(newpixel[i])<<endl;
	}
	file3.close();

//------------------------------------------------------------------------------------------------------
	//Free memory after dynamic allocation.
	
	dealloc_mem2(Imgdatac,Size_h,Size_w);
	delete[] Imagedatac;
	dealloc_mem2(Imgdatam,Size_h,Size_w);
	delete[] Imagedatam;

	return 0;
}
	

