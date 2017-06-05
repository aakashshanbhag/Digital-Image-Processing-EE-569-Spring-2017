
#include "stdafx.h"
#include <iostream>
#include"Header1.h"
#include<math.h>
using namespace std;

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	int BytesPerPixel;
	int BytesPerPixel1=1;
	int Size_h,Size_w ;
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<"program_name.exe Top_layer.raw bottom_layer.raw BytesPerPixel  Size_h Size_w blend.raw "<<endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4)
	{
		BytesPerPixel = 1; // default is grey image
	}
	else
	{
		BytesPerPixel = atoi(argv[3]);
		if (argc >= 5)
		{
			// Check if size is specified
			Size_h = atoi(argv[4]);
			Size_w = atoi(argv[5]);
			
		}
	}
//------------------------------------------------------------------------------------------------------
	// Allocate image data array	
	unsigned char *Imagedata;
	unsigned char *Imagedata1;
	unsigned char *Imagedata2;
	
	//CONVERSION TO  1D ARRAY. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata1= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel];
	
//------------------------------------------------------------------------------------------------------
	
	// Reading input files. 

	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);
	fileread(file,argv[2],Imagedata1,Size_h,Size_w,BytesPerPixel);
	
	
//------------------------------------------------------------------------------------------------------	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);
	
	unsigned char ***Imgdata1=NULL;
	Imgdata1=alloc_mem(Imgdata1,Size_h,Size_w,BytesPerPixel);
	
	

//------------------------------------------------------------------------------------------------------
	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel);
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel);
	Imgdata1=oned23d(Imgdata1,Imagedata1,Size_h,Size_w,BytesPerPixel);
	
	
//------------------------------------------------------------------------------------------------------

	unsigned char rtop,gtop,btop,r,g,b;
	
	//	Algorithm for multiplying both layer pixels(Multiply blend)	
	for (int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			rtop=Imgdata[i][j][0];
			gtop=Imgdata[i][j][1];
			btop=Imgdata[i][j][2];

			r=Imgdata1[i][j][0];
			g=Imgdata1[i][j][1];
			b=Imgdata1[i][j][2];

			// Normalisation and Renormalisation.
			img1[i][j][0]=unsigned char(255*(rtop/255.0)*(r/255.0));
			img1[i][j][1]=unsigned char(255*(gtop/255.0)*(g/255.0));
			img1[i][j][2]=unsigned char(255*(btop/255.0)*(b/255.0));
			
		}
	}
	
//------------------------------------------------------------------------------------------------------
	//Converting multidimenional array to 1d array for writing purpose.
	
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);

//------------------------------------------------------------------------------------------------------
	// Write image (filename specified by first argument) into image data matrix.
	
	filewrite(file,argv[6],Imagedata2,Size_h,Size_w,BytesPerPixel);
    
//------------------------------------------------------------------------------------------------------	
	//Free memory after dynamic allocation.
	
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);
	dealloc_mem(Imgdata1,Size_h,Size_w);
	
	
	delete[] Imagedata;
	delete[] Imagedata1;
	delete[] Imagedata2;
	return 0;
}





	