// Headers Defined
#include "stdafx.h"
#include <iostream>
#include"Header1.h"
using namespace std;

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file;
	errno_t err;
	int BytesPerPixel;
	int Size ;
	int Size1;

	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<< "Program_name.exe input_image.raw output_image.raw [BytesPerPixel = 3] [Size = 300] [Size1=resize value]"<<endl;
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
			Size = atoi(argv[4]);
			Size1=atoi(argv[5]);
		}
	}

	if ((err = fopen_s(&file, argv[1], "rb"))!=0)
	{
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}

	// Allocate image data array	
	unsigned char *Imagedata;
	unsigned char *Imagedata1;
	unsigned char *Imagedata2;

	//	Conversion to 1D array. 
	Imagedata= new unsigned char [Size*Size*BytesPerPixel];
	Imagedata1= new unsigned char [Size*Size*BytesPerPixel];
	Imagedata2= new unsigned char [Size1*Size1*BytesPerPixel];
	

	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	cout << "File read successful" << endl;
	
	
	// Read image (filename specified by first argument) into image data matrix
	if ((err = fopen_s(&file, argv[2], "wb"))!=0)
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size1,Size1,BytesPerPixel);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size,Size,BytesPerPixel);
	

	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size,Size,BytesPerPixel);
	img1=oned23d(img1,Imagedata2,Size1,Size1,BytesPerPixel);
	 

	// Algorithm for resizing the image.	
	int ar,ag,ab,br,bg,bb,cr,cg,cb,dr,dg,db,x,y;
	float ratiox=(float)(Size-1)/Size1;
	float ratioy=(float)(Size-1)/Size1;
	float xdiff,ydiff;

	for(int i=0;i<Size1;i++)
	{
		for(int j=0;j<Size1;j++)
		{
			x=ratiox*1.0*j;//ceiling and normalization
			y=ratioy*1.0*i;
			
		
			xdiff=(ratiox*1.0*j)-1.0*x;
			ydiff=(ratioy*1.0*i)-1.0*y;

			ar=Imgdata[x][y][0];//	Obtaining the four neighbourhood points.
			ag=Imgdata[x][y][1];
			ab=Imgdata[x][y][2];

			br=Imgdata[x+1][y][0];
			bg=Imgdata[x+1][y][1];
			bb=Imgdata[x+1][y][2];
			
			cr=Imgdata[x][y+1][0];
			cg=Imgdata[x][y+1][1];
			cb=Imgdata[x][y+1][2];

			dr=Imgdata[x+1][y+1][0];
			dg=Imgdata[x+1][y+1][1];
			db=Imgdata[x+1][y+1][2];

			// Using the bilinear transformation formula for 4 neighbourhood points.
			img1[j][i][0]=unsigned char((1-xdiff)*(1-ydiff)*ar+(xdiff)*(1-ydiff)*br+(1-xdiff)*(ydiff)*cr+(xdiff)*(ydiff)*dr);
			img1[j][i][1]=unsigned char((1-xdiff)*(1-ydiff)*ag+(xdiff)*(1-ydiff)*bg+(1-xdiff)*(ydiff)*cg+(xdiff)*(ydiff)*dg);
			img1[j][i][2]=unsigned char((1-xdiff)*(1-ydiff)*ab+(xdiff)*(1-ydiff)*bb+(1-xdiff)*(ydiff)*cb+(xdiff)*(ydiff)*db);



		}
	}
	
	
	//	Converting 3d array to 1d array for writing purpose.
	Imagedata2=threed21d(Imagedata2,img1,Size1,Size1);

	// Write image data (filename specified by second argument) from image data matrix
	fwrite(Imagedata2, sizeof(unsigned char), Size1*Size1*BytesPerPixel, file);
	fclose(file);
	cout << "File write successful" << endl;

    return 0;
}


