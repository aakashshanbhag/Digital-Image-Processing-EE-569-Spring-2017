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
	bool check;
	
int count=0;
int freq=0;
int size=0;
int freqnew=0;
int freqdiff=0;
int diff_iterations=0;
int prev_count=0;

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name input_image.raw output_image.raw Size_h Size_w"<<endl;
		return 0;
	}
	
	 int Size_h=atoi(argv[3]);// Width of the image used.
	 int Size_w=atoi(argv[4]);// Height of the image used.
	
	const int n=3;//  Pattern size value.
	
	//	Define 1 d array fr image printing

	unsigned char *Imagedatac;
	unsigned char *Imagedatam;
	unsigned char * valuecheck;
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	Imagedatam= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Output image matrix
	valuecheck=new unsigned char [n*n];

	//	Reading input image.

	fileread(file,argv[1],Imagedatac,Size_h,Size_w,BytesPerPixel1);
	
	// Allocation of multi-dimensional array for easier handling of pixels.

	unsigned char **Imgdatac=NULL;
	Imgdatac=alloc_mem2(Imgdatac,Size_h,Size_w);
	unsigned char **Imgdatam=NULL;
	Imgdatam=alloc_mem2(Imgdatam,Size_h,Size_w);
	
	unsigned char **imgext=NULL;// Initial value normalised.
	imgext=alloc_mem2(imgext,Size_h,Size_w);

	unsigned char **mmatrix=NULL;// Intermediate value normalised.
	mmatrix=alloc_mem2(mmatrix,Size_h,Size_w);
	
	
	//	Conversion from 1 dimensional array to Multi dimensional array for easier manipulation.

	Imgdatac=oned22d(Imgdatac,Imagedatac,Size_h,Size_w);//input.
	Imgdatam=oned22d(Imgdatam,Imagedatam,Size_h,Size_w);// output
	
	
	// Normalisation of the values.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
					imgext[i][j]= (Imgdatac[i][j]/255.0);	
							
		}
	}
	
	for(int o=1;o<=10;o++)
	{
	// Processing of the First phase.

	for(int i=0;i<Size_h-(n-1);i++)
	{
		for(int j=0;j<Size_w-(n-1);j++)
		{
			
		// storage of the values in a character array.	
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
					{
						valuecheck[n*k+l]=imgext[i+k][j+l];
					}
			}
		
		// setting up centre value by checking the patterns match.

			check=shrinkingtable(valuecheck);
			if(imgext[i+(n>>1)][j+(n>>1)]==1)
			{
			if(check)
				{
					mmatrix[i+(n>>1)][j+(n>>1)]=1;// setting to 1 if match occurs
				}
			else
				{
					mmatrix[i+(n>>1)][j+(n>>1)]=0;// else 0
				}
			}
			else
			{
				mmatrix[i+(n>>1)][j+(n>>1)]=0;
			}
		}
	
	}
	// 1st phase completed.

	for(int i=0;i<Size_h-(n-1);i++)
	{
		for(int j=0;j<Size_w-(n-1);j++)
		{
			
		// storage of the values in a character array.	
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
					{
						valuecheck[n*k+l]=mmatrix[i+k][j+l];
					}
			}
		
		// setting up centre value by checking the patterns match.
	
			check= shrink_thin2phase(valuecheck);
			
			if (mmatrix[i+(n>>1)][j+(n>>1)]==1)
			{
			if(check)
				{
					Imgdatam[i+(n>>1)][j+(n>>1)]=imgext[i+(n>>1)][j+(n>>1)]*255.0;// setting to original if match occurs
				}
			else
				{
					Imgdatam[i+(n>>1)][j+(n>>1)]=0;// else keep set to 0.
				}
			}
			else
			{
				Imgdatam[i+(n>>1)][j+(n>>1)]=imgext[i+(n>>1)][j+(n>>1)]*255.0;
			}
		}
	
	}

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
					imgext[i][j]=Imgdatam[i][j]/255.0;	
				//last output becomes input.		
		}
	}
	cout<<"  "<<endl;
	cout<<"iteration:"<<o<<endl;



	
// Count Generated. to check 1 pixel widths
	for(int i=1;i<=Size_h-2;i++)
	{
		for(int j=1;j<=Size_w-2;j++)
		{
			if(Imgdatam[i][j]==255 && Imgdatam[i][j-1]==0 && Imgdatam[i-1][j]==0 && Imgdatam[i+1][j]==0 && Imgdatam[i][j+1]==0 && Imgdatam[i-1][j-1]==0 && Imgdatam[i-1][j+1]==0 && Imgdatam[i+1][j-1]==0 && Imgdatam[i+1][j+1]==0 )
				count++; 
			

		}
	}
	cout<<"count:"<<count<< endl;
	
	if((count-prev_count)!=0)
	{
		freqnew=count-prev_count;// frequency of occurences.
		
		diff_iterations=2*o;
			if(diff_iterations==2)
				{
					size=1;
				}
			else
				{
					size=(diff_iterations)*(diff_iterations);
				}
	cout<<"size:   "<<size<<" frequency:   "<<freqnew<< endl;// Size calculated according to removal of 2 pixels each.
	cout<<"  "<<endl;
	}
	else
	{
	cout<<"No change at this iteration"<<endl;// No change if frequency doesnot change.
	cout<<"  "<<endl;
	}

	prev_count=count;
	count=0;

}
	
	
	
	count=0;
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			if(Imgdatam[i][j]==255)
				count++;// Setup for final count.
					
		}
	}
		cout<<"final count:"<<count<<endl;



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





