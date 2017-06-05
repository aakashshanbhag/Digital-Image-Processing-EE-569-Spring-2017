#include "stdafx.h"
#include <iostream>
#include"Header1.h"
#include<math.h>
using namespace std;

int main(int argc, char* argv[])
{

	// Define file pointer and variables
	FILE* file = NULL;
	int BytesPerPixel;
	int BytesPerPixel1 = 1;
	int Size_h, Size_w;

	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<"program_name.exe input_image.raw output_image.raw BytesPerPixel  Size_h Size_w r_image.raw g_image.raw b_image.raw gray.raw "<<endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4)
	{
		BytesPerPixel = 3; // default is grey image
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

	// Allocate image data array	
	unsigned char *Imagedata;
	unsigned char *Imagedata1;
	unsigned char *Imagedata2;
	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	unsigned char *Imagedatay;
	unsigned char *Imagedatar;

	//CONVERSION TO  1D ARRAY. 
	Imagedata = new unsigned char[Size_w*Size_h*BytesPerPixel];
	Imagedata1 = new unsigned char[Size_w*Size_h*BytesPerPixel];
	Imagedata2 = new unsigned char[Size_w*Size_h*BytesPerPixel];

	Imagedatac = new unsigned char[Size_w*Size_h*BytesPerPixel1];
	Imagedatay = new unsigned char[Size_w*Size_h*BytesPerPixel1];
	Imagedatam = new unsigned char[Size_w*Size_h*BytesPerPixel1];
	Imagedatar = new unsigned char[Size_w*Size_h*BytesPerPixel1];

//------------------------------------------------------------------------------------------------------	
	//	Reading input file from processing. 

	fileread(file, argv[1], Imagedata, Size_h, Size_w, BytesPerPixel);


//------------------------------------------------------------------------------------------------------	

	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1 = NULL;
	img1 = alloc_mem(img1, Size_h, Size_w, BytesPerPixel);
	unsigned char ***Imgdata = NULL;
	Imgdata = alloc_mem(Imgdata, Size_h, Size_w, BytesPerPixel);

	unsigned char **Imgdatac = NULL;
	Imgdatac = alloc_mem2(Imgdatac, Size_h, Size_w);
	unsigned char **Imgdatam = NULL;
	Imgdatam = alloc_mem2(Imgdatam, Size_h, Size_w);
	unsigned char **Imgdatay = NULL;
	Imgdatay = alloc_mem2(Imgdatay, Size_h, Size_w);
	unsigned char **Imgdatar = NULL;
	Imgdatar = alloc_mem2(Imgdatar, Size_h, Size_w);

	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata = oned23d(Imgdata, Imagedata, Size_h, Size_w, BytesPerPixel);
	img1 = oned23d(img1, Imagedata2, Size_h, Size_w, BytesPerPixel);

	Imgdatac = oned22d(Imgdatac, Imagedata, Size_h, Size_w);
	Imgdatam = oned22d(Imgdatam, Imagedata, Size_h, Size_w);
	Imgdatay = oned22d(Imgdatay, Imagedata, Size_h, Size_w);
	Imgdatar = oned22d(Imgdatar, Imagedata, Size_h, Size_w);

//------------------------------------------------------------------------------------------------------	


	float r, g, b;

	//	Algorithm for Sepia filter	
	for (int i = 0;i<Size_h;i++)
	{
		for (int j = 0;j<Size_w;j++)
		{	
			//Conversion according to the defined formula.
			
			int a = (0.393*Imgdata[i][j][0] + 0.769*Imgdata[i][j][1] + 0.189*Imgdata[i][j][2]);
			int b = (0.349*Imgdata[i][j][0] + 0.686*Imgdata[i][j][1] + 0.168*Imgdata[i][j][2]);
			int c = (0.272*Imgdata[i][j][0] + 0.534*Imgdata[i][j][1] + 0.131*Imgdata[i][j][2]);
			
			img1[i][j][0] = unsigned char (a);
			img1[i][j][1] = unsigned char (b);
			img1[i][j][2] = unsigned char (c);
			
			// Checking boundary conditions
			
			if (a < 0)
				img1[i][j][0] = 0;
			else if (a > 255)
				img1[i][j][0] = 255;

			if (b < 0)
				img1[i][j][1] = 0;
			else if (b > 255)
				img1[i][j][1] = 255;	

			if (c < 0)
				img1[i][j][2] = 0;
			else if (c > 255)
				img1[i][j][2] = 255;
				
			
			r = Imgdata[i][j][0];
			g = Imgdata[i][j][1];
			b = Imgdata[i][j][2];

			// Gray converted image.
			
			Imgdatar[i][j] = unsigned char(0.21*r + 0.72*g + 0.07*b);
		}
	}
//------------------------------------------------------------------------------------------------------	
	// Storage for display purposes
	
	for (int i = 0;i<Size_h;i++)
	{
		for (int j = 0;j<Size_w;j++)
		{
			Imgdatac[i][j] = img1[i][j][0];
			Imgdatam[i][j] = img1[i][j][1];
			Imgdatay[i][j] = img1[i][j][2];
		}
	}
//------------------------------------------------------------------------------------------------------	

	//	Converting multidimenional array to 1d array for writing purpose.

	Imagedata2 = threed21d(Imagedata2, img1, Size_h, Size_w);

	Imagedatac = twod21d(Imagedatac, Imgdatac, Size_h, Size_w);
	Imagedatam = twod21d(Imagedatam, Imgdatam, Size_h, Size_w);
	Imagedatay = twod21d(Imagedatay, Imgdatay, Size_h, Size_w);
	Imagedatar = twod21d(Imagedatar, Imgdatar, Size_h, Size_w);


	// Read image (filename specified by first argument) into image data matrix

	filewrite(file, argv[2], Imagedata2, Size_h, Size_w, BytesPerPixel);

	filewrite(file, argv[6], Imagedatac, Size_h, Size_w, BytesPerPixel1);
	filewrite(file, argv[7], Imagedatam, Size_h, Size_w, BytesPerPixel1);
	filewrite(file, argv[8], Imagedatay, Size_h, Size_w, BytesPerPixel1);
	filewrite(file, argv[9], Imagedatar, Size_h, Size_w, BytesPerPixel1);

//------------------------------------------------------------------------------------------------------	

	// Free memory after dynamic allocation is completed. 
	
	dealloc_mem(Imgdata, Size_h, Size_w);
	dealloc_mem(img1, Size_h, Size_w);

	dealloc_mem2(Imgdatac, Size_h, Size_w);
	dealloc_mem2(Imgdatam, Size_h, Size_w);
	dealloc_mem2(Imgdatay, Size_h, Size_w);
	dealloc_mem2(Imgdatar, Size_h, Size_w);


	delete[] Imagedata;
	delete[] Imagedata1;
	delete[] Imagedata2;
	delete[] Imagedatay;
	delete[] Imagedatac;
	delete[] Imagedatam;
	delete[] Imagedatar;
	
	return 0;
}