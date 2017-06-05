	// Headers defined
#include "stdafx.h"
#include <iostream>
#include "Header1.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file;
	errno_t err;
	int BytesPerPixel;
	int Size_h,Size_w;
//-----------------------------------------------------------------------------------------------------------	
	// Check for proper syntax
	
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 300]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4)
		{
			BytesPerPixel = 1;		// default is grey image
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

	if ((err = fopen_s(&file, argv[1], "rb"))!=0)		//Reading argument.
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	
	

//------------------------------------------------------------------------------------------------------
	// Allocate image data array	
	unsigned char *Imagedata;
	unsigned char *Imagedata1;
	
	//CONVERSION TO  1D ARRAY. 
	Imagedata= new unsigned char [Size_h*Size_w*BytesPerPixel];
	Imagedata1= new unsigned char [Size_h*Size_w*BytesPerPixel];
	
	
	// Read image (filename specified by first argument) into image data matrix
	fread(Imagedata, sizeof(unsigned char), Size_h*Size_w*BytesPerPixel, file);
	fclose(file);
	cout << "File read successful" << endl;

	
	// Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	unsigned char ***Imgdata=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel);
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);

	

	// Conversion from 1d array to 3d array for easier manipulation.

	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_h,BytesPerPixel);

//------------------------------------------------------------------------------------------------------
	
	// Algorithm for exchanging and mirroring the pixels	
	for (int i=0;i<Size_h;i++)
	{
		
		for(int j=0;j<Size_w;j++)
		{			
			img1[i][j][0]=Imgdata[i][(Size_w-1)-j][0];
			img1[i][j][1]=Imgdata[i][(Size_w-1)-j][1];
			img1[i][j][2]=Imgdata[i][(Size_w-1)-j][2];
		}
	}
	
	// Converting 3d array to 1d array for writing purpose.

	Imagedata1=threed21d(Imagedata1,img1,Size_h,Size_w);

//------------------------------------------------------------------------------------------------------
	// Write image data (filename specified by second argument) from image data matrix
	
	if ((err = fopen_s(&file, argv[2], "wb"))!=0)//Writing argument. 
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	
	fwrite(Imagedata1, sizeof(unsigned char), Size_h*Size_w*BytesPerPixel, file);
	fclose(file);
	cout << "File write successful" << endl;
    return 0;
}

