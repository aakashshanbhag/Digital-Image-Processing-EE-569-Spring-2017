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
	int Size_h,Size_w ;
	int BytesPerPixel=3;
	

	if (argc < 1)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<  "program_name "<<endl;
		return 0;
	}
	
	Size_h=350;// Width of the image used.
	Size_w=590;// Height of the image used.
	const int n=5;//Size of the filter.
	
	unsigned char *Imagedatac_rgb;
	unsigned char *Imagedatac_gray;
	
	Imagedatac_rgb= new unsigned char [Size_w*Size_h*BytesPerPixel];// Input image matrix
	Imagedatac_gray= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Input image matrix
	
	unsigned char *Imagedatam_gray;
	unsigned char *IndexMatrix;

	Imagedatam_gray= new unsigned char [Size_w*Size_h*BytesPerPixel1];// Output image matrix
	IndexMatrix= new unsigned char [5*5];// Basic Index matrix needed.

	unsigned char ***img1 = NULL;
	img1 = alloc_mem(img1, Size_h, Size_w, BytesPerPixel);

	//	Reading Training data image textures.

	fileread(file,"D:/cplusplus/HW3/prob1b/kitten.raw",Imagedatac_rgb,Size_h,Size_w,BytesPerPixel);// Current working directory to be put in as input here.
	
	//	Conversion from rgb to gray.

	img1 = oned23d(img1,Imagedatac_rgb , Size_h, Size_w, BytesPerPixel);

	
	// Allocation of multi-dimensional array for easier handling of pixels.
	double **Imgdatac1=NULL;
	Imgdatac1=alloc_mem2double(Imgdatac1,Size_h,Size_w);
	
	double **Imgdatac2=NULL;
	Imgdatac2=alloc_mem2double(Imgdatac2,Size_h,Size_w);
	

	unsigned char **Imgdatac1c=NULL;
	Imgdatac1c=alloc_mem2(Imgdatac1c,Size_h,Size_w);
	
	unsigned char **Imgdatac2c=NULL;
	Imgdatac2c=alloc_mem2(Imgdatac2c,Size_h,Size_w);

	// Conversion to Gray image.

	for (int i=0;i<Size_h;i++)
	{
		for (int j = 0;j<Size_w;j++)
		{	
			Imgdatac1c[i][j] = unsigned char(0.2989*img1[i][j][0] + 0.5870*img1[i][j][1]+ 0.1140*img1[i][j][2]);
		}
	}
	
	
	// Convert to double for unsigned char 
	
	Imgdatac1=convert2double(Imgdatac1c,Imgdatac1,Size_h,Size_w);
	
	
	//Initially taking the mean of the image to subtract the dc component
	double mean1;
	mean1=meanimage(Imgdatac1,Size_h,Size_w);
	
	// Subtraction of dc component

	Imgdatac1=subtractdc(Imgdatac1,Size_h,Size_w,mean1);
	
	// Generating Laws filter.
	double* l5=new double[n];
	double* s5=new double[n];
	double* w5=new double[n];
	double* r5=new double[n];
	double* e5=new double[n];
	
	l5[0]=1; l5[1]=4; l5[2]=6; l5[3]=4; l5[4]=1;
	e5[0]=-1; e5[1]=-2; e5[2]=0; e5[3]=2; e5[4]=1;
	s5[0]=-1; s5[1]=0; s5[2]=2; s5[3]=0; s5[4]=-1;
	w5[0]=-1; w5[1]=2; w5[2]=0; w5[3]=-2; w5[4]=1;
	r5[0]=1; r5[1]=-4; r5[2]=6; r5[3]=-4; r5[4]=1;

	double **l5l5=NULL;
	l5l5=alloc_mem2double(l5l5,5,5);
	
	double **l5e5=NULL;
	l5e5=alloc_mem2double(l5e5,5,5);
		
	double **l5s5=NULL;
	l5s5=alloc_mem2double(l5s5,5,5);
	
	double **l5w5=NULL;
	l5w5=alloc_mem2double(l5w5,5,5);

	double **l5r5=NULL;
	l5r5=alloc_mem2double(l5r5,5,5);

//	
	double **e5l5=NULL;
	e5l5=alloc_mem2double(e5l5,5,5);
	
	double **e5e5=NULL;
	e5e5=alloc_mem2double(e5e5,5,5);
		
	double **e5s5=NULL;
	e5s5=alloc_mem2double(e5s5,5,5);
	
	double **e5w5=NULL;
	e5w5=alloc_mem2double(e5w5,5,5);
	
	double **e5r5=NULL;
	e5r5=alloc_mem2double(e5r5,5,5);

//
	
	double **s5l5=NULL;
	s5l5=alloc_mem2double(s5l5,5,5);
	
	double **s5e5=NULL;
	s5e5=alloc_mem2double(s5e5,5,5);
		
	double **s5s5=NULL;
	s5s5=alloc_mem2double(s5s5,5,5);
	
	double **s5w5=NULL;
	s5w5=alloc_mem2double(s5w5,5,5);
	
	double **s5r5=NULL;
	s5r5=alloc_mem2double(s5r5,5,5);
//

	double **w5l5=NULL;
	w5l5=alloc_mem2double(w5l5,5,5);
	
	double **w5e5=NULL;
	w5e5=alloc_mem2double(w5e5,5,5);
		
	double **w5s5=NULL;
	w5s5=alloc_mem2double(w5s5,5,5);
	
	double **w5w5=NULL;
	w5w5=alloc_mem2double(w5w5,5,5);
	
	double **w5r5=NULL;
	w5r5=alloc_mem2double(w5r5,5,5);
//

	double **r5l5=NULL;
	r5l5=alloc_mem2double(r5l5,5,5);
	
	double **r5e5=NULL;
	r5e5=alloc_mem2double(r5e5,5,5);
		
	double **r5s5=NULL;
	r5s5=alloc_mem2double(r5s5,5,5);
	
	double **r5w5=NULL;
	r5w5=alloc_mem2double(r5w5,5,5);
	
	double **r5r5=NULL;
	r5r5=alloc_mem2double(r5r5,5,5);
	
// Output of the Laws filters.
	cout<<endl;
	cout<<"l5l5"<<endl;
	l5l5=lawsfilter(l5,l5,l5l5);

	cout<<endl;
	cout<<"l5e5"<<endl;
	l5e5=lawsfilter(l5,e5,l5e5);
	
	cout<<endl;
	cout<<"l5w5"<<endl;
	l5w5=lawsfilter(l5,w5,l5w5);
	
	cout<<endl;
	cout<<"l5r5"<<endl;
	l5r5=lawsfilter(l5,r5,l5r5);
	
	cout<<endl;
	cout<<"l5s5"<<endl;
	l5s5=lawsfilter(l5,s5,l5s5);
//
	cout<<endl;
	cout<<"e5l5"<<endl;
	e5l5=lawsfilter(e5,l5,e5l5);

	cout<<endl;
	cout<<"e5e5"<<endl;
	e5e5=lawsfilter(e5,e5,e5e5);
	
	cout<<endl;
	cout<<"e5w5"<<endl;
	e5w5=lawsfilter(e5,w5,e5w5);
	
	cout<<endl;
	cout<<"e5r5"<<endl;
	e5r5=lawsfilter(e5,r5,e5r5);
	
	cout<<endl;
	cout<<"e5s5"<<endl;
	e5s5=lawsfilter(e5,s5,e5s5);

	//
	cout<<endl;
	cout<<"w5l5"<<endl;
	w5l5=lawsfilter(w5,l5,w5l5);

	cout<<endl;
	cout<<"w5e5"<<endl;
	w5e5=lawsfilter(w5,e5,w5e5);
	
	cout<<endl;
	cout<<"w5w5"<<endl;
	w5w5=lawsfilter(w5,w5,w5w5);
	
	cout<<endl;
	cout<<"w5r5"<<endl;
	w5r5=lawsfilter(w5,r5,w5r5);
	
	cout<<endl;
	cout<<"w5s5"<<endl;
	w5s5=lawsfilter(w5,s5,w5s5);

	//
	cout<<endl;
	cout<<"s5l5"<<endl;
	s5l5=lawsfilter(s5,l5,s5l5);

	cout<<endl;
	cout<<"s5e5"<<endl;
	s5e5=lawsfilter(s5,e5,s5e5);
	
	cout<<endl;
	cout<<"s5w5"<<endl;
	s5w5=lawsfilter(s5,w5,s5w5);
	
	cout<<endl;
	cout<<"s5r5"<<endl;
	s5r5=lawsfilter(l5,r5,s5r5);
	
	cout<<endl;
	cout<<"s5s5"<<endl;
	s5s5=lawsfilter(s5,s5,s5s5);

	cout<<endl;
	cout<<"r5l5"<<endl;
	r5l5=lawsfilter(r5,l5,r5l5);

	cout<<endl;
	cout<<"r5e5"<<endl;
	r5e5=lawsfilter(r5,e5,r5e5);
	
	cout<<endl;
	cout<<"r5w5"<<endl;
	r5w5=lawsfilter(r5,w5,r5w5);
	
	cout<<endl;
	cout<<"r5r5"<<endl;
	r5r5=lawsfilter(r5,r5,r5r5);
	
	cout<<endl;
	cout<<"r5s5"<<endl;
	r5s5=lawsfilter(r5,s5,r5s5);

	// Making the image textures set a 3 dimensional array where the 3rd dimesnion denotes the number of the image.

	double ***op1=NULL;
	op1=alloc_memdouble(op1,Size_h,Size_w,25);

	unsigned char *output_final=new unsigned char [Size_w*Size_h*BytesPerPixel];
	unsigned char *output_final3d=new unsigned char [Size_w*Size_h*BytesPerPixel];
	unsigned char *output_final3d1=new unsigned char [Size_w*Size_h*BytesPerPixel];
	
	
	double ***op_fv=NULL;
	op_fv=alloc_memdouble(op_fv,Size_h,Size_w,25);
	
	double ***op_fv1=NULL;
	op_fv1=alloc_memdouble(op_fv1,Size_h,Size_w,25);

	double **centroid=NULL;
	centroid=alloc_mem2double(centroid,Size_h*Size_w,25);
	
	double **output=NULL;
	output=alloc_mem2double(output,Size_h,Size_w);
	

	unsigned char **outputc=NULL;
	outputc=alloc_mem2(outputc,Size_h,Size_w);

	double **trial=NULL;
	trial=alloc_mem2double(trial,Size_h*Size_w,1);

	unsigned char *outputc1=new unsigned char [Size_w*Size_h];
	unsigned char *outputc13d=new unsigned char [Size_w*Size_h];
	unsigned char *outfine=new unsigned char[Size_w*Size_h];
	
	// Creation of filter set.
	double ***filterset=NULL;
	filterset=alloc_memdouble(filterset,5,5,25);

	filterset=filterset25(l5l5,filterset,0);
	filterset=filterset25(l5e5,filterset,1);
	filterset=filterset25(l5w5,filterset,2);
	filterset=filterset25(l5r5,filterset,3);
	filterset=filterset25(l5s5,filterset,4);

	filterset=filterset25(e5l5,filterset,5);
	filterset=filterset25(e5e5,filterset,6);
	filterset=filterset25(e5w5,filterset,7);
	filterset=filterset25(e5r5,filterset,8);
	filterset=filterset25(e5s5,filterset,9);

	filterset=filterset25(w5l5,filterset,10);
	filterset=filterset25(w5e5,filterset,11);
	filterset=filterset25(w5w5,filterset,12);
	filterset=filterset25(w5r5,filterset,13);
	filterset=filterset25(w5s5,filterset,14);

	filterset=filterset25(r5l5,filterset,15);
	filterset=filterset25(r5e5,filterset,16);
	filterset=filterset25(r5w5,filterset,17);
	filterset=filterset25(r5r5,filterset,18);
	filterset=filterset25(r5s5,filterset,19);

	filterset=filterset25(s5l5,filterset,20);
	filterset=filterset25(s5e5,filterset,21);
	filterset=filterset25(s5w5,filterset,22);
	filterset=filterset25(s5r5,filterset,23);
	filterset=filterset25(s5s5,filterset,24);

	// Each texture image now has 25 filtered copies stored in op
	op1=texture_app(Imgdatac1,filterset,Size_h, Size_w,n);

	// Making the feature vector set as 350*590*25 matrix.
	
	op_fv=energy_window(op1,Size_h,Size_w,13,op_fv);

	// Normalisation wrt l5l5

	for(int k=0;k<25;k++)
	{
		for(int i=0;i<Size_h;i++)
		{
		for(int j=0;j<Size_w;j++)
		{
			op_fv1[i][j][k]=op_fv[i][j][k]/op_fv[i][j][0];
			
		}
		
		}
	}

	// Convert to 2d array for k mean application.
	double **op_fv12d=NULL;
	op_fv12d=alloc_mem2double(op_fv12d,Size_h*Size_w,25);

	double **op_fv12d3d=NULL;
	op_fv12d3d=alloc_mem2double(op_fv12d3d,Size_h*Size_w,3);

	for(int i=0;i<Size_h;i++)
	{
		for (int j=0;j<Size_w;j++)
		{
			for(int k=0;k<25;k++)
			{
				op_fv12d[i*Size_w+j][k]=op_fv1[i][j][k];
			}
		}
	}

	// Application of K means.
	outputc1=Kmeans_window_2d(op_fv12d,outputc1,3,Size_h,Size_w);

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
	{
		if(outputc1[i*Size_w+j]==0)
		{
			output_final[i*Size_w*3+3*j]=51;
			output_final[i*Size_w*3+3*j+1]=255;
			output_final[i*Size_w*3+3*j+2]=51;
		}
		if(outputc1[i*Size_w+j]==64)
		{
			output_final[i*Size_w*3+3*j]=255;
			output_final[i*Size_w*3+3*j+1]=51;
			output_final[i*Size_w*3+3*j+2]=255;

		}
		if(outputc1[i*Size_w+j]==128)
		{
			output_final[i*Size_w*3+3*j]=255;
			output_final[i*Size_w*3+3*j+1]=178;
			output_final[i*Size_w*3+3*j+2]=102;
		}
		if(outputc1[i*Size_w+j]==192)
		{
			output_final[i*Size_w*3+3*j]=51;
			output_final[i*Size_w*3+3*j+1]=255;
			output_final[i*Size_w*3+3*j+2]=255;	
		}
		if(outputc1[i*Size_w+j]==255)
		{
			output_final[i*Size_w*3+3*j]=102;
			output_final[i*Size_w*3+3*j+1]=0;
			output_final[i*Size_w*3+3*j+2]=102;
		}
	}

	}

	// Conversion back to 1 dimensional array.

	filewrite(file,"D:/cplusplus/HW3/prob1b/kitten_output.raw",output_final,Size_h,Size_w,BytesPerPixel);

	// PCA for 3d data
	ofstream file1;
	file1.open("high_dim.xls",ios::out);
	for(int i=0;i<Size_w*Size_h;i++)
	{
		for(int j=0;j<25;j++)
		{
			file1<<op_fv12d[i][j]<<"\t";
		}
		file1<<endl;	
	}
	file1.close();
	
	// File read after PCA conversion on Matlab.
	ifstream file4;
	file4.open("D:/cplusplus/HW3/prob1b/k3.txt");
	for(int i=0;i<Size_w*Size_h;i++)
	{
		for(int j=0;j<3;j++)
		{
			file4>>op_fv12d3d[i][j];
		}		
	}
	file4.close();
	
	// K means over 3 D data
	outputc13d=Kmeans_window_2d3d(op_fv12d3d,outputc13d,5,Size_h,Size_w);

	// Assigning specific colors to individual clusters.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
	{
		if(outputc13d[i*Size_w+j]==0)
		{
			output_final3d[i*Size_w*3+3*j]=51;
			output_final3d[i*Size_w*3+3*j+1]=255;
			output_final3d[i*Size_w*3+3*j+2]=51;
		trial[i*Size_w+j][0]=0;
		}
		if(outputc13d[i*Size_w+j]==64)
		{
			output_final3d[i*Size_w*3+3*j]=255;
			output_final3d[i*Size_w*3+3*j+1]=51;
			output_final3d[i*Size_w*3+3*j+2]=255;
					trial[i*Size_w+j][0]=64;
		}
		if(outputc13d[i*Size_w+j]==128)
		{
			output_final3d[i*Size_w*3+3*j]=255;
			output_final3d[i*Size_w*3+3*j+1]=178;
			output_final3d[i*Size_w*3+3*j+2]=102;
			trial[i*Size_w+j][0]=128;
		}
		if(outputc13d[i*Size_w+j]==192)
		{
			output_final3d[i*Size_w*3+3*j]=51;
			output_final3d[i*Size_w*3+3*j+1]=255;
			output_final3d[i*Size_w*3+3*j+2]=255;	
				trial[i*Size_w+j][0]=192;
		}
		if(outputc13d[i*Size_w+j]==255)
		{
			output_final3d[i*Size_w*3+3*j]=102;
			output_final3d[i*Size_w*3+3*j+1]=0;
			output_final3d[i*Size_w*3+3*j+2]=102;
			trial[i*Size_w+j][0]=255;
		}
	}

	}
	// File write to output.
	filewrite(file,"D:/cplusplus/HW3/prob1b/kitten_output3d.raw",output_final3d,Size_h,Size_w,BytesPerPixel);
	
	//	De-allocation of memory after processing.
	dealloc_mem2(Imgdatac1c,Size_h,Size_w);
	dealloc_mem2(Imgdatac2c,Size_h,Size_w);
	dealloc_mem2double(l5l5,5,5);
	dealloc_mem2double(l5e5,5,5);
	dealloc_mem2double(l5w5,5,5);
	dealloc_mem2double(l5s5,5,5);
	dealloc_mem2double(l5r5,5,5);
	
	dealloc_mem2double(e5l5,5,5);
	dealloc_mem2double(e5e5,5,5);
	dealloc_mem2double(e5w5,5,5);
	dealloc_mem2double(e5r5,5,5);
	dealloc_mem2double(e5s5,5,5);

	dealloc_mem2double(w5l5,5,5);
	dealloc_mem2double(w5e5,5,5);
	dealloc_mem2double(w5w5,5,5);
	dealloc_mem2double(w5r5,5,5);
	dealloc_mem2double(w5s5,5,5);

	dealloc_mem2double(r5l5,5,5);
	dealloc_mem2double(r5e5,5,5);
	dealloc_mem2double(r5w5,5,5);
	dealloc_mem2double(r5r5,5,5);
	dealloc_mem2double(r5s5,5,5);

	dealloc_mem2double(s5l5,5,5);
	dealloc_mem2double(s5e5,5,5);
	dealloc_mem2double(s5w5,5,5);
	dealloc_mem2double(s5r5,5,5);
	dealloc_mem2double(s5s5,5,5);


	delete[] Imagedatac_rgb;
	delete[] Imagedatac_gray;
	return 0;
}



