// Header definition.
#include "stdafx.h"
#include <iostream>
#include"Header1.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file;
	
	errno_t err;
	int BytesPerPixel,BytesPerPixel1;
	
	int Size_w,Size_w1;
	int Size_h,Size_h1;
	
	// Allocate image data array	
	unsigned char *Imagedata=NULL;
	unsigned char *Imagedata1=NULL;
	unsigned char *Img2=NULL;
	unsigned char *Img2data=NULL;
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<"Program_name.exe input_image.raw opposite_image.raw [BytesPerPixel = 3] [Size_h = 300] [Size_w = 300] background_image.raw output.raw BytesPerPixel1 Height Width"<<endl;	
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
		{// Check if size is specified
			Size_h = atoi(argv[4]);
			Size_w = atoi(argv[5]);
			BytesPerPixel1=atoi(argv[8]);
			Size_h1 = atoi(argv[10]);
			Size_w1 = atoi(argv[9]);

		}
	}
	
	//	Conversion To  1D Array.
	Imagedata= new unsigned char [Size_h*Size_w*BytesPerPixel];
	Imagedata1= new unsigned char [Size_h*Size_w*BytesPerPixel];
	Img2=new unsigned char[Size_h1*Size_w1*BytesPerPixel1];
	Img2data=new unsigned char[Size_h1*Size_w1*BytesPerPixel1];

	if ((err = fopen_s(&file, argv[1], "rb"))!=0)
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}

	//	Reading 1st dog image.
	fread(Imagedata, sizeof(unsigned char), Size_w*Size_h*BytesPerPixel, file);
	fclose(file);
	cout << "File1 read successful" << endl;

		if ((err = fopen_s(&file, argv[6], "rb"))!=0)
	{
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}

	// Read image (filename specified by first argument) into image data matrix
	
	fread(Img2, sizeof(unsigned char), Size_w1*Size_h1*BytesPerPixel1, file);
	fclose(file);
	cout << "File2 read successful" << endl;

	
    if ((err = fopen_s(&file, argv[2], "wb"))!=0)
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	
	
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	unsigned char ***Imgdata=NULL;

	img1=alloc_mem(img1,Size_w,Size_h,BytesPerPixel);
	Imgdata=alloc_mem(Imgdata,Size_w,Size_h,BytesPerPixel);

	unsigned char ***img2=NULL;
	unsigned char ***Imgdata2=NULL;

	img2=alloc_mem(img2,Size_w1,Size_h1,BytesPerPixel1);
	Imgdata2=alloc_mem(Imgdata2,Size_w1,Size_h1,BytesPerPixel1);


	//	Conversion from 1d array to 3d array for easier manipulation.

	Imgdata=oned23d(Imgdata,Imagedata,Size_w,Size_h,BytesPerPixel);
	Imgdata2=oned23d(Imgdata2,Img2,Size_w1,Size_h1,BytesPerPixel1);


	
	//	Algorithm for exchanging the pixels	
	for (int i=0;i<Size_h;i++)
	{
		
		for(int j=0;j<Size_w;j++)
		{			
			img1[i][j][0]=Imgdata[i][(Size_w-1)-j][0];
			img1[i][j][1]=Imgdata[i][(Size_w-1)-j][1];
			img1[i][j][2]=Imgdata[i][(Size_w-1)-j][2];
		}
	}
	// Setting background white for the dog image.	
	for (int i=0;i<Size_h;i++)
	{
		
		for(int j=0;j<Size_w;j++)
		{			
			if(img1[i][j][0]<100 && img1[i][j][1]<100 && img1[i][j][2]>180)
			{
				img1[i][j][0]=255;
				img1[i][j][1]=255;
				img1[i][j][2]=255;
			}
			

		}
	}
	
	// Setting up threshold for consideration of edges.
	for(int i=0;i<Size_h1;i++)
	{
		for(int j=0;j<Size_w1;j++)
		{
			if(i>=400 && i<700 && j>=1100 && j<1400)
			{
				if((img1[i-400][j-1100][0]!=255) && (img1[i-400][j-1100][1]!=255) && (img1[i-400][j-1100][2]!=255))
				{
					Imgdata2[i][j][0]=img1[i-400][j-1100][0];
					Imgdata2[i][j][1]=img1[i-400][j-1100][1];
					Imgdata2[i][j][2]=img1[i-400][j-1100][2];
				}
			}
		}
	}

	//	Converting 3d array to 1d array for writing purpose.

	Imagedata1=threed21d(Imagedata1,img1,Size_w,Size_h);
	Img2data=threed21d(Img2data,Imgdata2,Size_w1,Size_h1);


	// Write image data (filename specified by second argument) from image data matrix
	fwrite(Imagedata1, sizeof(unsigned char), Size_w*Size_h*BytesPerPixel, file);
	fclose(file);
	cout << "File write successful" << endl;
	
	if ((err = fopen_s(&file, argv[7], "wb"))!=0)
	{
		cout << "Cannot open file: " << argv[7] << endl;
		exit(1);
	}

	fwrite(Img2data, sizeof(unsigned char), Size_w1*Size_h1*BytesPerPixel1, file);
	fclose(file);
	cout << "File write successful" << endl;
    return 0;
}


