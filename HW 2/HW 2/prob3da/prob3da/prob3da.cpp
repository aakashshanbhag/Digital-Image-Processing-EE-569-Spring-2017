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
int count1=0;
int count2=0;
int count=0;
int freq=0;
int size=0;
int freqnew=0;
int freqdiff=0;
int diff_iterations=0;
int prev_count=0;
int i2,j2;

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
	unsigned char **Imgdatam1=NULL;
	Imgdatam1=alloc_mem2(Imgdatam1,Size_h,Size_w);// flood filled.

	
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
					imgext[i][j]= (255-Imgdatac[i][j])/255.0;// complement	
				Imgdatam1[i][j]=Imgdatac[i][j];	// setting up floodfill to original intially	
		}
	}
	



	for(int o=1;o<=16;o++)
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
					mmatrix[i+(n>>1)][j+(n>>1)]=1;// setting to zero if match occurs
				}
			else
				{
					mmatrix[i+(n>>1)][j+(n>>1)]=0;// else keep original matrix.
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
	cout<<"Iteration success for shrinking of holes:"<<o<<endl;
	
	}

// Checking the centre pixel equal to white and rest black in the complemented image
	
	
	for(int i=0;i<Size_h-(n-1);i++)
	{
		for(int j=0;j<Size_w-(n-1);j++)
		{
			
		// storage of the values in a character array.	
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
					{
						valuecheck[n*k+l]=Imgdatam[i+k][j+l];
					}
			}

			if(valuecheck[4]==255 && valuecheck[0]==0 && valuecheck[1]==0 && valuecheck[2]==0 && valuecheck[3]==0 && valuecheck[5]==0 && valuecheck[6]==0 && valuecheck[7]==0 && valuecheck[8]==0)
			{

				int i1=i+(n>>1);
				int j1=j+(n>>1);
			floodfill(Imgdatam1, i1, j1);
			count1++;
			}

		}
	}


	cout<<"The total number of holes: "<<count1<<endl;
	cout<<"    "<<endl;



	// Shrinking to obtain white objects.

	
		for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
					imgext[i][j]=Imgdatam1[i][j]/255.0;// complement	
					// setting up floodfill to original intially	
					
		}
	}
	

	for(int o=1;o<=50;o++)
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
					mmatrix[i+(n>>1)][j+(n>>1)]=0;// else 0.
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
	cout<<"Iteration success for number of white objects :"<<o<<endl;
	
	}


	 
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			if(Imgdatam[i][j]==255)
				count2++;
		
				// Number of 1 pixel white objects after shrinking. 		
		}
	}
	cout<<"  "<<endl;
	cout<<"The number of white objects: "<<count2<<endl;
	cout<<"  "<<endl;

	int squarecount=0;
	int circlecount=0;
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
		// take the index for the centroid.
		if(Imgdatam[i][j]==255)
		{
			i2=i;
			j2=j;
			count=0;count1=0;
			 while(Imgdatam1[i2][j2]!=0)
			 {
				j2++; count++;
			 }
			 while(Imgdatam1[i2][j2]!=0)
			 {
				i2++; count1++;
			 }

			 if(count==count1)
			 {
				 squarecount++;// Squarecount
			 }
			 else
			 {
				 circlecount++;// Circlecount
			 }


		}

		}

	}

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






