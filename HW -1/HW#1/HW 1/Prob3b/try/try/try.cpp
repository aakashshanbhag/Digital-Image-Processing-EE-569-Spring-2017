

#include <iostream>
#include"Header1.h"
#include<math.h>
using namespace std;

int main(int argc, char* argv[])
{
//------------------------------------------------------------------------------------------------------	
	// Code runs for default value of h=10,sigma=1;
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
		cout << "try.exe pepper_noisy.raw filtered.raw 3 512 512 pepper.raw " << endl;
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
				
		}
	}
	const int n=7;
	//------------------------------------------------------------------------------------------------------	

	// Allocate image data array	
	unsigned char *Imagedata;//input
	
	unsigned char *Imagedata1r;unsigned char *Imagedata1g;unsigned char *Imagedata1b;//indivdual channel median;
	unsigned char *Imagedata2r;unsigned char *Imagedata2g;unsigned char *Imagedata2b;//indivdual channel median;
	
	unsigned char *Imagedata2;//extended storage
	
	unsigned char *Imagedatac;//output
	unsigned char *Imagedata3;//default image
	unsigned char *Imagedata4;//default image2
//------------------------------------------------------------------------------------------------------	
	
	//	CONVERSION TO  1D ARRAY. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];
	
	Imagedata1r= new unsigned char [(n)*(n)];Imagedata1g= new unsigned char [(n)*(n)];Imagedata1b= new unsigned char [(n)*(n)];
	Imagedata2r= new unsigned char [(n)*(n)];Imagedata2g= new unsigned char [(n)*(n)];Imagedata2b= new unsigned char [(n)*(n)];
	
	Imagedata2= new unsigned char [(Size_w+(n-1))*(Size_h+(n-1))*BytesPerPixel];
	
	Imagedatac= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata3= new unsigned char [Size_w*Size_h*BytesPerPixel];
	Imagedata4= new unsigned char [Size_w*Size_h*BytesPerPixel];
//------------------------------------------------------------------------------------------------------	
		
	//	Reading input and default file.
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);
	fileread(file,argv[6],Imagedata3,Size_h,Size_w,BytesPerPixel);
	//-----------------------------------------------------------------------------------------------------
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
	unsigned char ***img2=NULL;
	img2=alloc_mem(img1,(Size_h+(n-1)),(Size_w+(n-1)),BytesPerPixel);
	unsigned char ***Imgdata=NULL;
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata1=NULL;
	Imgdata1=alloc_mem(Imgdata1,Size_h,Size_w,BytesPerPixel);

	int *countlr=NULL;
	float gaus[n*n];
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
	img2=oned23d(img2,Imagedata4,(Size_h),(Size_w),BytesPerPixel);
	Imgdata1=oned23d(Imgdata1,Imagedata,Size_h,Size_w,BytesPerPixel);//reference input image
//------------------------------------------------------------------------------------------------------	

	//	Boundary extensionby replication.	
	img1=extend(Imgdata,Size_h,Size_w,n);
	img2=extend(Imgdata,Size_h,Size_w,n);
	
	//	Filtering
	float sigma=1;
	float wr[n*n],wg[n*n],wb[n*n];
	float diffr,diffg,diffb;
	
					

	//	Gausssian weight calculation
	for(int k=0;k<n;k++)
	{
		for(int l=0;l<n;l++)
		{

			gaus[k*n+l]=(1.0/((2*3.14159*sigma)))*expf(-0.5/(sigma*sigma)*(pow((k-(n>>1)),2.0)+(pow(l-(n>>1),2.0))));
			
			
		}
	}
//--------------------------------------------------------------------------------------------------------
	// NLM algorithm.
	int s=21; // Size of search window to be applied.
	int distort=10;//parameter for distortion.
	for (int i = 0;i < Size_h;i++)
	{
		for (int j = 0;j < Size_w;j++)
		{
			
			int i1 = i + (n>>1);
			int j1 = j +(n>>1);
			
			int imin = i1 - (n>>1);// top
			int imax = i1 + (n>>1);// bottom
			int jmin = j1 - (n>>1);// left
			int jmax = j1 + (n>>1);//right

			int p = 0;
			for (int h1 =imin;h1 < imax;h1++)
			{
				for (int w1 = jmin;w1 < jmax;w1++)
				{
					Imagedata1r[p] = img1[h1][w1][0];
					Imagedata1g[p] = img1[h1][w1][1];				
					Imagedata1b[p] = img1[h1][w1][2];
					p++;	
				}
			}

			//Initialing Counts to 0 before beginning of search
			float sumr=0,sumr1=0,sumr2=0,sumg=0,sumg1=0,sumg2=0,sumb=0,sumb1=0,sumb2=0;
			float diffr,diffg,diffb;
			
			//Boundary values for the search window to avoid negligence of any pixels around the boundary of the seearch window.
			int kmin = max(i1 - s, (n>>1) +1);
			int kmax = min(i1 + s, Size_h + (n>>1));
			int lmin= max(j1 - s, (n>>1) + 1);
			int lmax = min(j1 + s , Size_w + (n>>1));

			
			for (int k = kmin; k <= kmax;k++)
			{
				for (int l = lmin; l <= lmax;l++)
				{
					// Similar to original patch and hence omit.
					if (k == i1 && l == j1)
						break;

					//Same process of mapping.
					int h2min = k - (n>>1);
					int h2max = k + (n>>1);
					int w2min = l - (n>>1);
					int w2max = l + (n>>1);

					int q = 0;
					for (int h2 = h2min;h2 < h2max;h2++)
					{
						for (int w2 =w2min;w2 < w2max;w2++)
						{
					Imagedata2r[q] = img1[h2][w2][0];
					Imagedata2g[q] = img1[h2][w2][1];				
					Imagedata2b[q] = img1[h2][w2][2];
					q++;
						}

					}


					for (int b = 0;b < n;b++)
					{
						for (int b1 = 0;b1 < n;b1++)
						{
							diffr=(Imagedata1r[b*n+b1] - Imagedata2r[b*n+b1]);
							sumr = sumr +  (gaus[b*n+b1]*(pow(diffr, 2)));

							diffg=(Imagedata1g[b*n+b1] - Imagedata2g[b*n+b1]);
							sumg = sumg +  (gaus[b*n+b1]*(pow(diffg, 2)));
							
							diffb=(Imagedata1b[b*n+b1] - Imagedata2b[b*n+b1]);
							sumb = sumb +  (gaus[b*n+b1]*(pow(diffb, 2)));
						}
					}

					//	Zi calculation.
					sumr1=sumr1+ exp(-sumr / (1.0*distort*distort));
					sumg1=sumg1+ exp(-sumg / (1.0*distort*distort));
					sumb1=sumb1+ exp(-sumb / (1.0*distort*distort));

					

					//	Product of search window pixel with corresponding weights
					sumr2 = sumr2 + exp(-sumr / (1.0*distort*distort))*  img1[k][l][0];
					sumg2 = sumg2 + exp(-sumg / (1.0*distort*distort))*  img1[k][l][1];
					sumb2 = sumb2 + exp(-sumb / (1.0*distort*distort))*  img1[k][l][2];
				}
			}

			
				img2[i][j][0] = unsigned char(sumr2/(1.0*sumr1));
				img2[i][j][1] = unsigned char(sumg2/(1.0*sumg1));	
				img2[i][j][2] = unsigned char(sumb2/(1.0*sumb1));
	
		}
	}

//------------------------------------------------------------------------------------------------------	
	
	
//------------------------------------------------------------------------------------------------------	


	//	Converting multidimenional array to 1d array for writing purpose.
	Imagedatac=threed21d(Imagedatac,img2,Size_h,(Size_w));
	
//------------------------------------------------------------------------------------------------------	
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


//------------------------------------------------------------------------------------------------------	
	// Read image (filename specified by first argument) into image data matrix
	filewrite(file,argv[2],Imagedatac,(Size_h),(Size_w),BytesPerPixel);
//------------------------------------------------------------------------------------------------------	
    ofstream file4;
	file4.open("map.xls",ios::out);
	for (int i=0;i<Size_w;i++)
		{
			for(int j=0; j<Size_h;j++)

			{
				int a=(int)Imgdata[i][j][0];


	file4<<a<<endl;
			}
	}
	file4.close();



	// Free memory allocated.
	
	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,(Size_h+(n-1)),(Size_w+(n-1)));
	
	delete[] Imagedata;
	delete[] Imagedata1r;delete[] Imagedata1g;delete[] Imagedata1b;
	delete[] Imagedata2;
	delete[] Imagedata3;
	
	return 0;







}