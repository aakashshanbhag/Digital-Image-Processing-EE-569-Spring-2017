// Inclusion of headers
#include "stdafx.h"
#include <iostream>
#include "Header1.h"
#include<math.h>
#include <fstream>
using namespace std;
int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<< "program_name input_image.raw output_image.raw Size_h Size_w input.xls output_equalised.xls "<< endl;
		return 0;
	}
	
	int BytesPerPixel1=3;
	int Size_h,Size_w ;
	
	Size_h=atoi(argv[3]);
	Size_w=atoi(argv[4]);
	
	//	Define 1 d array fr image printing
	
	unsigned char *Imagedata;
	unsigned char *Imagedata2;

	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel1];
	
	// Reading Input image data.
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel1);
	
	//	Multidimesional array for easier manipulation of data.
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel1);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel1);
	
	// Conversion to multidimensional array for easier access.
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel1);
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel1);

	int countr[256]={},countg[256]={},countb[256]={};// Input histogram
	int countlr[256]={},countlg[256]={},countlb[256]={};//	Output histogram
	
	// Initial count set to 0.
	for(int i=0;i<256;i++)
	{
	countr[i]=0;countg[i]=0;countb[i]=0;
	countlr[i]=0;countlg[i]=0;countlb[i]=0;
	}

	//Input Histogram.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countr[Imgdata[i][j][0]]++);
			(countg[Imgdata[i][j][1]]++);
			(countb[Imgdata[i][j][2]]++);
		}
	}
//--------------------------------------------------------------------------------
	//Minimisation.
	//-----------r
	int i=0,minr=0;
	while(countr[i]==0)
	{
		i++;
	}
	minr=i;
	//-----------g
	int i1=0,ming=0;
	while(countg[i]==0)
	{
		i1++;
	}
	ming=i1;
	//-----------b
	int i2=0,minb=0;
	while(countb[i]==0)
	{
		i2++;
	}
	minb=i2;
//------------------------------------------------------------------------------------------------
	//Max
	//-----------r
	int k=0,maxr=255;
	while(countr[255-k]==0)
	{
		k++;
	}
	maxr=255-k;
	//-----------g
	int k1=0,maxg=255;
	while(countg[255-k]==0)
	{
		k1++;
	}
	maxg=255-k1;
	//-----------b
	int k2=0,maxb=255;
	while(countb[255-k2]==0)
	{
		k2++;
	}
	maxb=255-k2;
//------------------------------------------------------------------------------------

	
	//Oneto one mapping
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
		img1[i][j][0]=unsigned char(255.0/(1.0*(maxr-minr))*(Imgdata[i][j][0]-minr));	
		img1[i][j][1]=unsigned char(255.0/(1.0*(maxg-ming))*(Imgdata[i][j][1]-ming));	
		img1[i][j][2]=unsigned char(255.0/(1.0*(maxb-minb))*(Imgdata[i][j][2]-minb));	
		}
	}

	// Output histogram.
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			(countlr[img1[i][j][0]]++);
			(countlg[img1[i][j][1]]++);
			(countlb[img1[i][j][2]]++);
		}
	}

	//	Conversion back to 1d array for printing.
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);

	// Writing back to output file.
	filewrite(file,argv[2],Imagedata2,Size_h,Size_w,BytesPerPixel1);

//-----------------------------------------------------	
	//	Filewrite fr hist dataset	
	ofstream file1;
	file1.open(argv[5],ios::out);
	for(int i=0;i<256;i++)
	{
		file1<<i<<" \t     "<<int(countr[i])<<" \t     "<<int(countg[i])<<" \t     "<<int(countb[i])<<endl;

	}
	file1.close();
	
	// Output histogram data set
	ofstream file2;
	file2.open(argv[6],ios::out);
	for(int i=0;i<256;i++)
	{
		file2<<i<<" \t     "<<int(countlr[i])<<"\t      "<<int(countlg[i])<<" \t     "<<int(countlb[i])<<endl;
	}
	file2.close();

	// Transfer curve data.
	int a[256]={};
	int b[256]={};
	int c[256]={};
	ofstream file3;
	file3.open("transfer_curve.xls",ios::out);
	for(int i=0;i<256;i++)
	{
		if(i<minr || i>maxr)
			a[i]=0;
		else
		{
				a[i]=int(255.0/(1.0*(maxr-minr))*(i-minr));
		}

		if(i<ming || i>maxg)
			b[i]=0;
		else
		{
				b[i]=int(255.0/(1.0*(maxg-ming))*(i-ming));
		}

		if(i<minb || i>maxb)
			c[i]=0;
		else
		{
				c[i]=int(255.0/(1.0*(maxb-minb))*(i-minb));
		}
		file3<<i<<" \t     "<<a[i]<<" \t     "<<b[i]<<" \t     "<<c[i]<<endl;
	}
	file3.close();
	

//------------------------------------------------------	
	// Free memory from heap after complete processing.

	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);

	delete[] Imagedata;
	delete[] Imagedata2;
	
	return 0;
}
	


