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

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name input_image.raw output_image.raw Size_h Size_w input.xls output_equalised.xls "<<endl;
		return 0;
	}
	
	Size_h=atoi(argv[3]);
	Size_w=atoi(argv[4]);
	
	//	Define 1 d array fr image printing

	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	

	//	Reading input image.

	fileread(file,argv[1],Imagedatac,Size_h,Size_w,BytesPerPixel1);
	
	// Allocation of multi-dimensional array for easier handling of pixels.

	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	
	//	Conversion from 1 dimensional array to Multi dimensional array for easier manipulation.

	Imgdatac=oned22d(Imgdatac,Imagedatac,Size_h,Size_w);
	Imgdatam=oned22d(Imgdatam,Imagedatam,Size_h,Size_w);
	
	int count[256]={};// Input histogram
	int countb[256]={};// Output histogram
	
	
	for(int i=0;i<256;i++)// Initial setup to 0.
	{count[i]=0;countb[i]=0;}


	//	Histogram for input image.

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(count[Imgdatac[i][j]]++);
		}
	}


	// Calculation of minimum intensity value for input image 

	int i=0,min=0;
	while(count[i]==0)
	{
		i++;
	}
	min=i;

	// Calculation of maximum intensity value for input image

	int k=0,max=255;
	while(count[255-k]==0)
	{
		k++;
	}
	max=255-k;

	
	//	Oneto one mapping according to formula

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
				Imgdatam[i][j]=unsigned char(255.0/(1.0*(max-min))*(Imgdatac[i][j]-min));	
		}
	}

	// Calculation of output histogram.

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countb[Imgdatam[i][j]]++);
		}
	}

	cout<<"min: "<<min<<endl;
	cout<<"max: "<<max<<endl;

	// Conversion back to 1 dimensional array.

	Imagedatam=twod21d(Imagedatam,Imgdatam,Size_h,Size_w);
	
	//	Filewrite to output.

	filewrite(file,argv[2],Imagedatam,Size_h,Size_w,BytesPerPixel1);


	ofstream file1;// Input histogram
	file1.open(argv[5],ios::out);
	for(int i=0;i<256;i++)
	{
		file1<<i<<" \t     "<<int(count[i])<<endl;
	}
	file1.close();


	ofstream file2;// Output histogram
	file2.open(argv[6],ios::out);
	for(int i=0;i<256;i++)
	{
		file2<<i<<" \t     "<<int(countb[i])<<endl;
	}
	file2.close();


	int a[256]={};// Transfer curve data.
	ofstream file3;
	file3.open("transfer_curve.xls",ios::out);
	for(int i=0;i<256;i++)
	{
		if(i<min || i>max)
			a[i]=0;
		else
		{
				a[i]=int(255.0/(1.0*(max-min))*(i-min));
		}
		file3<<i<<" \t     "<<a[i]<<endl;
	}
	file3.close();


	//	De-allocation of memory after processing.
	dealloc_mem2(Imgdatac,Size_h,Size_w);
	delete[] Imagedatac;
	dealloc_mem2(Imgdatam,Size_h,Size_w);
	delete[] Imagedatam;

	return 0;
}
	

