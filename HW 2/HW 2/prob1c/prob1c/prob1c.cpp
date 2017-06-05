

// Inclusion of headers
#include "stdafx.h"
#include <iostream>
#include "Header1.h"
using namespace std;

int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	int BytesPerPixel;
	int Size_h=648,Size_w=972 ;// field
	int piece_h=197,piece_w=350;// trojan
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<"program_name.exe field_image.raw output_image.raw trojans.raw "<<endl ;
		return 0;
	}
	
		BytesPerPixel = 3; // default is grey image
	
	//	Allocate image data array	
	unsigned char *Imagedata;// field
	unsigned char *Imagedata1;// trojanimage
	unsigned char *Imagedata2;// output image
	

	//	Conversion To 1D Array. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];// field
	Imagedata1= new unsigned char [piece_w*piece_h*BytesPerPixel];// trojan
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel];// op
	
	
	
	//	Reading input file.
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);// fieldread
	fileread(file,argv[3],Imagedata1,piece_h,piece_w,BytesPerPixel);//trojan read
	
	
//------------------------------------------------------------------------------------------------------	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	
	unsigned char ***img1=NULL;	// Output image
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata=NULL;	// field
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata1=NULL;
	Imgdata1=alloc_mem(Imgdata1,piece_h,piece_w,BytesPerPixel);// piece 3d allocation
	
	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel);// field
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel);// output
	Imgdata1=oned23d(Imgdata1,Imagedata1,piece_h,piece_w,BytesPerPixel);// piece

	//	Finding First coordinate location of field coordinates 4 control points.

	int j1,i1,j2,i2,j3,i3,j4,i4,q,p;// Image cordinates of field image.
	double x1,y1,x2,y2,x3,y3,x4,y4,x,y;// cartesian of the field image.
	int J1,I1,J2,I2,I3,J3,J4,I4;// Image cordinates of the trojan image;
	double X1,Y1,X2,Y2,X3,Y3,X4,Y4,xdiff,ydiff;// cartesian cordinates of the trojan image.
	int ar,ag,ab,br,bg,bb,cr,cg,cb,dr,dg,db;

	j1=356;i1=584;
	j2=541;i2=440;
	j3=522;i3=595;
	j4=630;i4=436;


	J1=1;I1=1;
	J2=349;I2=1;
	J3=1;I3=196;
	J4=349,I4=196;



	// Converting image to cartesian cordinates. 
	
	// Field image 4 points.
	
	x1=img2cartx(j1);
	x2=img2cartx(j2);
	x3=img2cartx(j3);
	x4=img2cartx(j4);
	
	y1=img2carty(i1,Size_h);
	y2=img2carty(i2,Size_h);
	y3=img2carty(i3,Size_h);
	y4=img2carty(i4,Size_h);

	// Trojan image 4 points

	X1=img2cartx(J1);
	X2=img2cartx(J2);
	X3=img2cartx(J3);
	X4=img2cartx(J4);
	
	Y1=img2carty(I1,piece_h);
	Y2=img2carty(I2,piece_h);
	Y3=img2carty(I3,piece_h);
	Y4=img2carty(I4,piece_h);


	cout<< "image to cartesian of field"<< endl;

	cout<<" x1:"<<x1 <<"  "<<"y1:"<<y1<<endl;
	cout<<" x2:"<<x2 <<"  "<<"y2:"<<y2<<endl;
	cout<<" x3:"<<x3 <<"  "<<"y3:"<<y3<<endl;
	cout<<" x4:"<<x4 <<"  "<<"y4:"<<y4<<endl;

	cout<< "image to cartesian of TROJAN"<< endl;

	cout<<" X1:"<<X1 <<"  "<<"Y1:"<<Y1<<endl;
	cout<<" X2:"<<X2 <<"  "<<"Y2:"<<Y2<<endl;
	cout<<" X3:"<<X3 <<"  "<<"Y3:"<<Y3<<endl;
	cout<<" X4:"<<X4 <<"  "<<"Y4:"<<Y4<<endl;
	
	// Traverse through the field image and find the location for remapping.

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			// convert to cartesian for manipulation in the field

			x=img2cartx(j);
			y=img2carty(i,Size_h);

			double L1=0.049*x+y;
			double L2=0.7783*x-y;
			double L3=1.4722*x-y;
			double L4=0.06626*x+y;

			if( L1<= 239.8371 && L2 >=213.9918 && L3 <= 716.7361 && L4 >= 87.1208 )
			{
				// transfromation matrix
				 double Xdash= 0.0692*x+1.0269*y-88.4776;
				 double Ydash=-1.0478*x +0.7099*y+510.723;
				 double Wdash=0.0005*x-0.0039*y+1;

				 // Normalisation
				 double X2=Xdash/(1.0*Wdash);
				 double Y2=Ydash/(1.0*Wdash);

				 // Conversion back to image coordinates 
				 double qdash=cart2imgx(X2);
				 double pdash=cart2imgy(Y2,piece_h);
				 //cout<<"qdash:"<< qdash<<"  "<<"pdash:"<< pdash << endl;
			
		 //Bilinear interpolation of floating point values.
				
		
		// New height and width
		
		int nh = (int)pdash;
		int nw = (int)qdash;
		double ydiff = pdash - 1.0*nh;
		double xdiff = qdash - 1.0*nw;
		
		//  Boundary conditions 
		if (nh < 0)
			{
				nh = 0;
			}
		if (nh >= piece_h - 2)
			{ 
				nh = piece_h - 2;
			}
		if (nw < 0)
			{ 
				nw = 0;
			}
		if (nw >= piece_w- 2)
			{ 
				nw = piece_w - 2;
			}
	
			// Resized image coordinates

			img1[i][j][0] = (unsigned char)
											((1 - ydiff) * (1 - xdiff) * Imgdata1[nh][nw][0] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][0] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][0] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][0]);

			img1[i][j][1] = (unsigned char)
											((1 - ydiff)*(1 - xdiff) * Imgdata1[nh][nw][1] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][1] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][1] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][1]);

			img1[i][j][2] = (unsigned char)
											((1 - ydiff)*(1 - xdiff) * Imgdata1[nh][nw][2] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][2] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][2] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][2]);	
			
			}

			else
			{ // Replace with old field values if not in the scope of interest.
				img1[i][j][0]=Imgdata[i][j][0];
				img1[i][j][1]=Imgdata[i][j][1];
				img1[i][j][2]=Imgdata[i][j][2];
			}

		}
	}
	
	// Removal of white background.

	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w;j++)
		{
			if(img1[i][j][0]>230 && img1[i][j][1]>230 && img1[i][j][2]>230)
			{
				img1[i][j][0]=Imgdata[i][j][0];
				img1[i][j][1]=Imgdata[i][j][1];
				img1[i][j][2]=Imgdata[i][j][2];

			}
		}
	}

	//	Converting multidimenional array to 1d array for writing purpose.
	
	Imagedata2=threed21d(Imagedata2,img1,Size_h,Size_w);


	// Read image (filename specified by first argument) into image data matrix
	
	filewrite(file,argv[2],Imagedata2,Size_h,Size_w,BytesPerPixel);
    
    
	//	Deallocation of memory after completion of tasks.

	dealloc_mem(Imgdata,Size_h,Size_w);
	dealloc_mem(img1,Size_h,Size_w);
	
	delete[] Imagedata;
	delete[] Imagedata1;
	delete[] Imagedata2;
	
	
	return 0;
}




