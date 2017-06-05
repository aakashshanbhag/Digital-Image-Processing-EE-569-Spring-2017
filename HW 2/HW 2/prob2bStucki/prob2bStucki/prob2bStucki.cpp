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
	
	int factor;
	
	
	double error;

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name input_image.raw output_image.raw Size_h Size_w"<<endl;
		return 0;
	}
	
	 int Size_h=atoi(argv[3]);// Width of the image used.
	 int Size_w=atoi(argv[4]);// Height of the image used.
	
	const int n=5;// Stucki mask size value.
	 factor=42;// Normalisation factor.

	//	Define 1 d array fr image printing

	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Output image matrix
	

	//	Reading input image.

	fileread(file,argv[1],Imagedatac,Size_h,Size_w,BytesPerPixel1);
	
	// Allocation of multi-dimensional array for easier handling of pixels.

	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	
	unsigned char **ImgdataExtend=NULL;
	ImgdataExtend=alloc_mem2(ImgdataExtend,Size_h+(n-1),Size_w+(n-1));
	double **imgext=NULL;
	imgext=alloc_mem2double(imgext,Size_h+(n-1),Size_w+(n-1));
	
	unsigned char **ImgdataExtend1=NULL;
	ImgdataExtend1=alloc_mem2(ImgdataExtend1,Size_h+(n-1),Size_w+(n-1));

	double **fsd=NULL;
	fsd=alloc_mem2double(fsd,n,n);

	
	//	Conversion from 1 dimensional array to Multi dimensional array for easier manipulation.

	Imgdatac=oned22d(Imgdatac,Imagedatac,Size_h,Size_w);//input.
	Imgdatam=oned22d(Imgdatam,Imagedatam,Size_h,Size_w);// output
	
	// Extend image

	ImgdataExtend=extend2d(Imgdatac, Size_h,Size_w,n);
	
	// Normalisation of the values.
	for(int i=0;i<Size_h+(n-1);i++)
	{
		for(int j=0;j<Size_w+(n-1);j++)
		{
					imgext[i][j]= (ImgdataExtend[i][j]/255.0);	
					
		}
	}

	// Processing of the error diffusion matrix.
	for(int i=0;i<Size_h;i++)
	{
		// If even thrn move from left to right.
		if(i%2==0)
		{
			for(int j=0;j<Size_w;j++)
				{
					fsd=stucki(fsd);
					error=0;
					// Calculation of the nearest pixel value for error propogation.
					if(imgext[i+(n>>1)][j+(n>>1)]>0.5)
					{
						ImgdataExtend1[i+(n>>1)][j+(n>>1)]=255;
						error=imgext[i+(n>>1)][j+(n>>1)]-1;
					}
					else
					{
						ImgdataExtend1[i+(n>>1)][j+(n>>1)]=0;
						error=imgext[i+(n>>1)][j+(n>>1)]-0;
					}
					
					// Forward propogation of error in the left to right direction.
						int m=0,n1=0;
						for(int k=i;k<=i+(n-1);k++)
						{ 
							for(int l=j;l<=j+(n-1);l++)
							{
								imgext[k][l]=imgext[k][l]+(error*fsd[m][n1]/factor);
								n1++;
							}
						m++;
						n1=0;
						}
			error=0;
			
			}
		}
		else// Movement from right to left.
		{

			for( int j=Size_w-1;j>=0;j--)
			{ error=0;
			fsd=stuckirev(fsd);
					// Calculation of the error						
					if(imgext[i+(n>>1)][j+(n>>1)]>0.5)
					{
						ImgdataExtend1[i+(n>>1)][j+(n>>1)]=255;
						error=imgext[i+(n>>1)][j+(n>>1)]-1;	
					}
					else
					{
						ImgdataExtend1[i+(n>>1)][j+(n>>1)]=0;
						error=imgext[i+(n>>1)][j+(n>>1)]-0;	
						
					}
					
					//Prpogation of the error from right to left. 
						int m=0,n1=0;
						for(int k=i;k<=i+(n-1);k++)
						{
							for(int l=j;l<=j+(n-1);l++)
							{
								
								imgext[k][l]=imgext[k][l]+(error*fsd[m][n1]/factor);
								n1++;
							}
							m++;n1=0;
						}
			error=0;		

		}
		}
}



	

	// Mapback to original size.
	
	Imgdatam=mapback2d( ImgdataExtend1,Size_w,Size_h,n,Imgdatam);
	
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



