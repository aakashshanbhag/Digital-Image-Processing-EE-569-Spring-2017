
#include "stdafx.h"
#include <iostream>
#include"Header1.h"
#include<math.h>
#include <cmath>
using namespace std;

int main(int argc, char* argv[])
{
//--------------------------------------------------------------------------------------------------------------

	// Define file pointer and variables
	FILE* file=NULL;
	int BytesPerPixel;
	int BytesPerPixel1=1;
	int Size_h,Size_w ;
	int type;

	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<< "program_name noisy_image.raw filtered_output_image.raw BytesPerPixel Size_h Size_w original_image type order_mask "<< endl;
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
			Size_h = atoi(argv[5]);
			Size_w = atoi(argv[4]);
			type=atoi(argv[7]);
			
		}
	}
	const int n=atoi(argv[8]);
	
//----------------------------------------------------------------------------------------------------------------	

	// Allocate image data array	
	unsigned char *Imagedata;//input
	unsigned char *Imagedata1r;unsigned char *Imagedata1g;unsigned char *Imagedata1b;//indivdual channel median;
	unsigned char *Imagedata2;//extended storage
	unsigned char *Imagedatac;//output
	unsigned char *Imagedata3;//default image
//---------------------------------------------------------------------------------------------------------------
	
	//	CONVERSION TO  1D ARRAY. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata1r= new unsigned char [(n)*(n)];Imagedata1g= new unsigned char [(n)*(n)];Imagedata1b= new unsigned char [(n)*(n)];
	Imagedata2= new unsigned char [(Size_w+(n-1))*(Size_h+(n-1))*BytesPerPixel];
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata3= new unsigned char [Size_w*Size_h*BytesPerPixel];
//------------------------------------------------------------------------------------------------------------------
		
	//	Reading input and default file.
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);
	fileread(file,argv[6],Imagedata3,Size_h,Size_w,BytesPerPixel);
//------------------------------------------------------------------------------------------------------------------
	//  Calculating the psnr for initial.
	float psnrr1,psnrg1,psnrb1;
	
	psnrr1=psnrr(Imagedata,Imagedata3,Size_w,Size_h);

	psnrg1=psnrg(Imagedata,Imagedata3,Size_w,Size_h);
	psnrb1=psnrb(Imagedata,Imagedata3,Size_w,Size_h);


	cout<<"Psnr Initial red= "<<psnrr1<<endl;
	cout<<"Psnr Initial green= "<<psnrg1<<endl;
	cout<<"Psnr Initial blue= "<<psnrb1<<endl;

//------------------------------------------------------------------------------------------------------	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;
	img1=alloc_mem(img1,(Size_h+(n-1)),(Size_w+(n-1)),BytesPerPixel);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata1=NULL;
	Imgdata1=alloc_mem(Imgdata1,Size_h,Size_w,BytesPerPixel);
	
	//	Calculation of the histograms of the original and noisy image.
	int *countlr=NULL;
	countlr=new int[256];
	int *countlg=NULL;
	countlg=new int[256];
	int *countlb=NULL;
	countlb=new int[256];
	
	for(int i=0;i<256;i++)
	{countlr[i]=0;countlg[i]=0;countlb[i]=0;}
		

	countlr=hist1r(Size_w,Size_h,Imagedata,countlr);
	countlg=hist1g(Size_w,Size_h,Imagedata,countlg);
	countlb=hist1b(Size_w,Size_h,Imagedata,countlb);

	hist_and_psnr_data_noise(countlr,countlb,countlg);

	for(int i=0;i<256;i++)
	{countlr[i]=0;countlg[i]=0;countlb[i]=0;}
	
	countlr=hist1r(Size_w,Size_h,Imagedata3,countlr);
	countlg=hist1g(Size_w,Size_h,Imagedata3,countlg);
	countlb=hist1b(Size_w,Size_h,Imagedata3,countlb);

	hist_and_psnr_data_org(countlr,countlb,countlg);

//------------------------------------------------------------------------------------------------------	

	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel);//final output goes in here.
	img1=oned23d(img1,Imagedata2,(Size_h+(n-1)),(Size_w+(n-1)),BytesPerPixel);
	Imgdata1=oned23d(Imgdata1,Imagedata,Size_h,Size_w,BytesPerPixel);//reference input image
//------------------------------------------------------------------------------------------------------	

	//	Boundary extension by replication.	
	img1=extend(Imgdata,Size_h,Size_w,n);
//----------------------------------------------------------------------------------------------------------
	//	Filtering

	switch(type)
	{
	case 1:	{img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 2:{img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 3:	{img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);
			img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 4: {img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 5:{img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 6:{img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 7:{for (int i=0;i<5;i++)
		   {img1=meanfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);};break;}
	case 8:{for (int i=0;i<5;i++)
		   {img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);};break;}
	case 9:{img1=mean1filter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 10:{for (int i=0;i<2;i++)
		   {img1=mean1filter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);};break;}
	case 11:{img1=mean1filter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}
	case 12:{img1=medianfilter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);img1=mean1filter(img1,n,Size_w,Size_h,Imagedata1r,Imagedata1g,Imagedata1b);break;}

	}
//----------------------------------------------------------------------------------------------------------------------
	
	//	Mapping from extended image to normal size image. 
	Imgdata=mapback(img1,Size_w,Size_h,n,Imgdata);
//----------------------------------------------------------------------------------------------------------------------


	//	Converting multidimenional array to 1d array for writing purpose.
	Imagedatac=threed21d(Imagedatac,Imgdata,Size_h,(Size_w));
	
//----------------------------------------------------------------------------------------------------------------------
	//	Calculation of Psnr
	float psnrr2,psnrg2,psnrb2;
	
	psnrr2=psnrr(Imagedatac,Imagedata3,Size_w,Size_h);
	psnrg2=psnrg(Imagedatac,Imagedata3,Size_w,Size_h);
	psnrb2=psnrb(Imagedatac,Imagedata3,Size_w,Size_h);

	cout<<"Psnr final red= "<<psnrr2<<endl;
	cout<<"Psnr final green= "<<psnrg2<<endl;
	cout<<"Psnr final blue= "<<psnrb2<<endl;
	
	for(int i=0;i<256;i++)
	{countlr[i]=0;countlg[i]=0;countlb[i]=0;}
	
	countlr=hist1r(Size_w,Size_h,Imagedatac,countlr);
	countlg=hist1g(Size_w,Size_h,Imagedatac,countlg);
	countlb=hist1b(Size_w,Size_h,Imagedatac,countlb);

	hist_and_psnr_data_filt(countlr,countlb,countlg);
	
	// Data collection in excel sheet for PSNR values.  
	ofstream file4;
	file4.open("map.xls",ios::app);
	file4<<n<<" \t     "<<type<<" \t     "<<psnrr2<<" \t     "<<psnrg2<<" \t     "<<psnrb2<<endl;
	file4.close();


//--------------------------------------------------------------------------------------------------------------------------
	// Read image (filename specified by first argument) into image data matrix 
	filewrite(file,argv[2],Imagedatac,(Size_h),(Size_w),BytesPerPixel);
//--------------------------------------------------------------------------------------------------------------------------
    
	// Free memory allocated.
	
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,(Size_h+(n-1)),(Size_w+(n-1)));
	
	delete[] Imagedata;
	delete[] Imagedata1r;delete[] Imagedata1g;delete[] Imagedata1b;
	delete[] Imagedata2;
	delete[] Imagedata3;
	
	return 0;
}





