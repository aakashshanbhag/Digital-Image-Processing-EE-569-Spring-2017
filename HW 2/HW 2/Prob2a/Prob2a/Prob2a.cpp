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
	int type;

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name input_image.raw output_image.raw Size_h Size_w SizeBayer type"<<endl;
		return 0;
	}
	
	Size_h=atoi(argv[3]);// Width of the image used.
	Size_w=atoi(argv[4]);// Height of the image used.
	const int n=atoi(argv[5]);//Size of the Bayer index.
	type=atoi(argv[6]);
	
	//	Define 1 d array fr image printing

	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	unsigned char *IndexMatrix;
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Output image matrix
	IndexMatrix= new unsigned char [2*2];// Basic Index matrix needed.

	//	Reading input image.

	fileread(file,argv[1],Imagedatac,Size_h,Size_w,BytesPerPixel1);
	
	// Allocation of multi-dimensional array for easier handling of pixels.

	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	unsigned char **indmat2=NULL;
	indmat2=alloc_mem2(indmat2,2,2);
	unsigned char **threshold=NULL;
	threshold=alloc_mem2(threshold,n,n);
	unsigned char **IndexMatrix4=NULL;
	IndexMatrix4=alloc_mem2(IndexMatrix4,4,4);
	unsigned char **diff4=NULL;
	diff4=alloc_mem2(diff4,4,4);
	unsigned char **IndexMatrix8=NULL;
	IndexMatrix8=alloc_mem2(IndexMatrix8,8,8);

	
	//	Conversion from 1 dimensional array to Multi dimensional array for easier manipulation.

	Imgdatac=oned22d(Imgdatac,Imagedatac,Size_h,Size_w);
	Imgdatam=oned22d(Imgdatam,Imagedatam,Size_h,Size_w);
	indmat2=oned22d(indmat2,IndexMatrix,2,2);

	// Generate the 2d indexmatrix to be used.
	if(n==2)
	{
		indmat2=indexmatrix2(indmat2);// Index matrix to be used
		threshold=thresholdtake(indmat2,2,threshold);// Threshold matrix generated.

	}
	else if(n==8)
	{
		indmat2=indexmatrix2(indmat2);
		IndexMatrix8=matrixcreate8(indmat2,IndexMatrix4,IndexMatrix8);// Index matrix to be used
	

	threshold=thresholdtake(IndexMatrix8,8,threshold);// Threshold matrix generated.

	}
	else
	{
		if(type==0)
		{
		indmat2=indexmatrix2(indmat2);
		IndexMatrix4=matrixcreate4(indmat2,IndexMatrix4);// Index matrix to be used
		
				threshold=thresholdtake(IndexMatrix4,4,threshold);// Threshold matrix generated.
		}
		else
		{
		diff4=different4(diff4);// Index matrix to be used
		threshold=thresholdtake(diff4,4,threshold);// Threshold matrix generated.
		}


	}

	
	// Dithering process carried out. 

	Imgdatam=Dither(Imgdatac,Imgdatam,threshold, Size_w,Size_h,n);

	// Conversion back to 1 dimensional array.

	Imagedatam=twod21d(Imagedatam,Imgdatam,Size_h,Size_w);
	filewrite(file,argv[2],Imagedatam,Size_h,Size_w,BytesPerPixel1);
	
	//	De-allocation of memory after processing.
	dealloc_mem2(Imgdatac,Size_h,Size_w);
	delete[] Imagedatac;
	dealloc_mem2(Imgdatam,Size_h,Size_w);
	delete[] Imagedatam;

	return 0;
}

