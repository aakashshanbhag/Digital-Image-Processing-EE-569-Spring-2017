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
		cout<< "Program_name.exe input_image.raw output_image.raw BytesPerPixel image_Height image_width"<<endl;
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
	unsigned char ***img2=NULL;
	img2=alloc_mem(img2,Size1,Size1,BytesPerPixel);
	

	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size,Size,BytesPerPixel);
	img1=oned23d(img1,Imagedata2,Size1,Size1,BytesPerPixel);
	img2=oned23d(img2,Imagedata2,Size1,Size1,BytesPerPixel);
	  

	// Algorithm for resizing the image.	
	int ar,ag,ab,br,bg,bb,cr,cg,cb,dr,dg,db,x,y;
		
	float ydiff;
	// first quarter.
	for(int i=0;i<Size/2;i++)
	{
		for(int j=0;j<i;j++)
		{
			float ratioy=(float)((Size/2)-1)/i;
			x=i;
			//ceiling and normalization
			y=ratioy*1.0*j;
			ydiff=(ratioy*1.0*j)-1.0*y;
			//	Obtaining the two neighbourhood points.
			ar=Imgdata[x][y][0];
			ag=Imgdata[x][y][1];
			ab=Imgdata[x][y][2];
			dr=Imgdata[x][y+1][0];
			dg=Imgdata[x][y+1][1];
			db=Imgdata[x][y+1][2];
			// Using the linear transformation formula for 2 neighbourhood points.
			img1[i][j][0]=unsigned char((1-ydiff)*ar+(ydiff)*dr);
			img1[i][j][1]=unsigned char((1-ydiff)*ag+(ydiff)*dg);
			img1[i][j][2]=unsigned char((1-ydiff)*ab+(ydiff)*db);
		}
	}
	
	int a=0;
	for(int i=0;i<Size/2;i++)
	{int b=0;
		for(int j=0;j<(Size/2-1)-i;j++)
		{
			img2[i][j][0]=0;
			img2[i][j][1]=0;
			img2[i][j][2]=0;
		}
		for (int k=0;k<=i;k++)
		{
			
			img2[i][(Size/2-1)-i+k][0]=(unsigned char)img1[a][b][0];
			img2[i][(Size/2-1)-i+k][1]=(unsigned char)img1[a][b][1];
			img2[i][(Size/2-1)-i+k][2]=(unsigned char)img1[a][b][2];
			b++;
		}
	a++;
	}
	//2nd quarter

	for(int i=0;i<Size/2;i++)
	{
		for(int j=0;j<i;j++)
		{
			float ratioy=(float)((Size/2)-1)/i;
			x=i;
			//ceiling and normalization
			y=(int)(ratioy*1.0*j)+(Size/2-1);
			ydiff=(ratioy*1.0*j)+(Size/2-1)-1.0*y;
			//	obtaining the 2 neighbourhood points.

			ar=Imgdata[x][y][0];
			ag=Imgdata[x][y][1];
			ab=Imgdata[x][y][2];
			dr=Imgdata[x][y+1][0];
			dg=Imgdata[x][y+1][1];
			db=Imgdata[x][y+1][2];
			// using the linear transformation formula for 2 neighbourhood points.
			img2[i][j+(Size/2)-1][0]=unsigned char((1-ydiff)*ar+(ydiff)*dr);
			img2[i][j+(Size/2)-1][1]=unsigned char((1-ydiff)*ag+(ydiff)*dg);
			img2[i][j+(Size/2)-1][2]=unsigned char((1-ydiff)*ab+(ydiff)*db);
		}
	}

	for(int i=0;i<Size/2;i++)
	{
		for(int j=Size-1;j>i+(Size/2-1);j--)
		{
		img2[i][j][0]=0;
			img2[i][j][1]=0;
			img2[i][j][2]=0;
		}
	}

	//3rd quarter.
	for(int i=Size/2-1;i>=0;i--)
	{
		for(int j=Size/2-1;j>=i;j--)
		{	
			float ratioy=(float)((Size/2)-1)/(Size/2-1-i);
			x=i+(Size/2)-1;
			//ceiling and normalization
			y=(int)(ratioy*1.0*(Size/2-1-j));
			ydiff=ratioy*1.0*(Size/2-1-j)-1.0*y;
			//	Obtaining the2 neighbourhood points.
			ar=Imgdata[x][Size/2-1-y][0];
			ag=Imgdata[x][Size/2-1-y][1];
			ab=Imgdata[x][Size/2-1-y][2];
			
			dr=Imgdata[x][Size/2-1-y+1][0];
			dg=Imgdata[x][Size/2-1-y+1][1];
			db=Imgdata[x][Size/2-1-y+1][2];
			// Using the linear transformation formula for 2 neighbourhood points.
			img2[i+Size/2-1][j][0]=unsigned char((1-ydiff)*ar+(ydiff)*dr);
			img2[i+Size/2-1][j][1]=unsigned char((1-ydiff)*ag+(ydiff)*dg);
			img2[i+Size/2-1][j][2]=unsigned char((1-ydiff)*ab+(ydiff)*db);
		}
	}
		
	for(int i=0;i<Size/2;i++)
	{
		for(int j=0;j<i;j++)
		{
		img2[i+Size/2][j][0]=0;
			img2[i+Size/2][j][1]=0;
			img2[i+Size/2][j][2]=0;
		}
	}
	//4th quarter

	for(int i=Size/2-1;i>=0;i--)
	{
		for(int j=0;j<Size/2-i;j++)
		{
			float ratioy=(float)((Size/2)-1)/(Size/2-1-i);
			x=i+(Size/2)-1;
			//ceiling and normalization
			y=((int)(ratioy*1.0*(j)))
				+(Size/2-1);
			
			ydiff=ratioy*1.0*(j)-1.0*y+(Size/2-1);
			//	Obtaining the 2 neighbourhood points.
			ar=Imgdata[x][y][0];
			ag=Imgdata[x][y][1];
			ab=Imgdata[x][y][2];
			
			dr=Imgdata[x][y+1][0];
			dg=Imgdata[x][y+1][1];
			db=Imgdata[x][y+1][2];
			// Using the bilinear transformation formula for 2 neighbourhood points.
			img2[i+Size/2-1][j+Size/2-1][0]=unsigned char((1-ydiff)*ar+(ydiff)*dr);
			img2[i+Size/2-1][j+Size/2-1][1]=unsigned char((1-ydiff)*ag+(ydiff)*dg);
			img2[i+Size/2-1][j+Size/2-1][2]=unsigned char((1-ydiff)*ab+(ydiff)*db);

			

		}
	}

	
	for(int i=0;i<Size/2;i++)
	{
		for(int j=Size/2-i;j<Size/2;j++)
		{
			img2[i+Size/2-1][j+Size/2-1][0]=0;
			img2[i+Size/2-1][j+Size/2-1][1]=0;
			img2[i+Size/2-1][j+Size/2-1][2]=0;
		}
	}

	
	
	//	Converting 3d array to 1d array for writing purpose.
	Imagedata2=threed21d(Imagedata2,img2,Size1,Size1);

	// Write image data (filename specified by second argument) from image data matrix
	fwrite(Imagedata2, sizeof(unsigned char), Size1*Size1*BytesPerPixel, file);
	fclose(file);
	cout << "File write successful" << endl;

    return 0;
}



