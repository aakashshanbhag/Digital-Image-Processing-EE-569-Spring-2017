	//	Headers included.
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
		cout<<"program_name.exe input_image.raw output_image.raw BytesPerPixel  Size_h Size_w h_image.raw s_image.raw l_image.raw "<<endl;
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
	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	unsigned char *Imagedatay;

	//CONVERSION TO  1D ARRAY. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata1= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel];
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedatay= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	
//------------------------------------------------------------------------------------------------------
	// Reading input file. 	
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);
	
//------------------------------------------------------------------------------------------------------
	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);
	
	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	unsigned char **Imgdatay=NULL;
	Imgdatay=alloc_mem2(Imgdatay,Size_h,Size_w);
//------------------------------------------------------------------------------------------------------


	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel);
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel);
	
	Imgdatac=oned22d(Imgdatac,Imagedata,Size_h,Size_w);
	Imgdatam=oned22d(Imgdatam,Imagedata,Size_h,Size_w);
	Imgdatay=oned22d(Imgdatay,Imagedata,Size_h,Size_w);
	
//------------------------------------------------------------------------------------------------------
	 
	float max,min;
	float r,g,h,s,b,l,l1;
	float c;
	
	//	Algorithm for generating the hsl image	
	for (int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			r=Imgdata[i][j][0]/255.0;
			g=Imgdata[i][j][1]/255.0;
			b=Imgdata[i][j][2]/255.0;

			
			//Max logic.
			
			if(r >= g && r >=b )
				max=r;
			if(g >= r && g >=b )
				max=g;
			if(b >= g && b >=r )
				max=b;
				

			//Min logic.
		
			if(r <= g && r <=b )
				min=r;
			if(g <= r && g <=b )
				min=g;
			if(b <= g && b <=r )
				min=b;
			
			c=max-min;
			
			//	L component

			l=unsigned char((255.0*((max+min)/2.0)));
			img1[i][j][2]=l;
			Imgdatay[i][j]=l;
			
			//	S component
			
			if(l/255.0==0)
			{s=0;}
			else if((l/255.0)>0 && (l/255.0)<0.5)
			{
				s=unsigned char((c/(2.0*(l/255.0)))*255);
				}
			else
			{
				s=unsigned char((c/(2.0-2.0*(l/255.0)))*255);
			}
			
			//	H component.
			
			if(c==0)
				h=0;
			
			if(max==r && c!=0)
			{
			h=unsigned char(((60/360.0)*255.0*((int)((g-b)/(c))%6)));
			}
			
			if(max==g && c!=0)
			{
			h=unsigned char(((60/360.0)*255.0*(((b-r)/(c))+2)));
			}
			
			if(max==b && c!=0)
			{
			h=unsigned char(((60/360.0)*255.0*(((r-g)/(c))+4)));
			}
			
			Imgdatac[i][j]=h;
			Imgdatam[i][j]=s;
		

			img1[i][j][0]=h;
			img1[i][j][1]=s;
		}
	}
//------------------------------------------------------------------------------------------------------	
	//	Converting multidimenional array to 1d array for writing purpose.
	
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);

	Imagedatac=twod21d(Imagedatac,Imgdatac,Size_h,Size_w);
	Imagedatam=twod21d(Imagedatam,Imgdatam,Size_h,Size_w);
	Imagedatay=twod21d(Imagedatay,Imgdatay,Size_h,Size_w);

//------------------------------------------------------------------------------------------------------
	// Write image (filename specified by first argument) into image data matrix
	
	filewrite(file,argv[2],Imagedata2,Size_h,Size_w,BytesPerPixel);
    
	filewrite(file,argv[6],Imagedatac,Size_h,Size_w,BytesPerPixel1);
    filewrite(file,argv[7],Imagedatam,Size_h,Size_w,BytesPerPixel1);
    filewrite(file,argv[8],Imagedatay,Size_h,Size_w,BytesPerPixel1);
//------------------------------------------------------------------------------------------------------    
	//	Cleaning the memory.
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);
	
	dealloc_mem2(Imgdatac,Size_h,Size_w);
	dealloc_mem2(Imgdatam,Size_h,Size_w);
	dealloc_mem2(Imgdatay,Size_h,Size_w);
	
	
	delete[] Imagedata;
	delete[] Imagedata1;
	delete[] Imagedata2;
	delete[] Imagedatay;
	delete[] Imagedatac;
	delete[] Imagedatam;
	
	return 0;
}





