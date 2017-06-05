// Inclusion of headers
#include "stdafx.h"
#include <iostream>
#include "Header1.h"
#include <math.h>

using namespace std;
int main(int argc, char* argv[])
{
	// Define file pointer and variables
	FILE* file=NULL;
	int BytesPerPixel;
	int Size_h=512,Size_w=512 ;
	int piece_h=500,piece_w=500;
	
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect parameter usage:" << endl;
		cout<<"program_name.exe trump_image.raw output_image.raw piece.raw "<<endl ;
		return 0;
	}
	
		BytesPerPixel = 3; // default is grey image
	
	//	Allocate image data array	
	unsigned char *Imagedata;//  trump
	unsigned char *Imagedata1;// piece image
	unsigned char *Imagedata2;// output image
	

	//	Conversion To 1D Array. 
	Imagedata= new unsigned char [Size_w*Size_h*BytesPerPixel];// trump
	Imagedata1= new unsigned char [piece_w*piece_h*BytesPerPixel];// piece
	Imagedata2= new unsigned char [Size_w*Size_h*BytesPerPixel];// op
	
	
	
	//	Reading input file.
	fileread(file,argv[1],Imagedata,Size_h,Size_w,BytesPerPixel);// trump read
	fileread(file,argv[3],Imagedata1,piece_h,piece_w,BytesPerPixel);//picece read
	
	
//------------------------------------------------------------------------------------------------------	
		
	//	Creation of dynamic memory as a pointer to a pointer (creation of 3d array dynamically)
	unsigned char ***img1=NULL;	// Output image
	img1=alloc_mem(img1,Size_h,Size_w,BytesPerPixel);
	unsigned char ***Imgdata=NULL;	// trump
	Imgdata=alloc_mem(Imgdata,Size_h,Size_w,BytesPerPixel);

	unsigned char ***Imgdata1=NULL;
	Imgdata1=alloc_mem(Imgdata1,piece_h,piece_w,BytesPerPixel);// piece 3d allocation
	unsigned char ***Imgdata2=NULL;
	Imgdata2=alloc_mem(Imgdata2,piece_h,piece_w,BytesPerPixel);// piece op check

	unsigned char ***Imgdata3=NULL;
	Imgdata3=alloc_mem(Imgdata3,piece_h,piece_w,BytesPerPixel);// piece op check

	
	//	Conversion from 1d array to 3d array for easier manipulation of original image.
	Imgdata=oned23d(Imgdata,Imagedata,Size_h,Size_w,BytesPerPixel);// hillary
	img1=oned23d(img1,Imagedata2,Size_h,Size_w,BytesPerPixel);// output
	Imgdata1=oned23d(Imgdata1,Imagedata1,piece_h,piece_w,BytesPerPixel);// piece
	Imgdata2=oned23d(Imgdata2,Imagedata1,piece_h,piece_w,BytesPerPixel);// piececopy

	Imgdata3=oned23d(Imgdata3,Imagedata1,piece_h,piece_w,BytesPerPixel);//mirror purpose
	
//------------------------------------------------------------------------------------------------------	
	// Application of translated,scaled and rotated matrix correctly on to the 4 points with bilinear reverse mapping process.

	// Finding 4 cordinates of piece.- imgdata1 is the 3d equivalent.

	int i,j,itop,jtop,ileft,jleft,iright,jright,ibottom,jbottom;// clockwise consideration if confusion arises.

	int flag=0;
	for ( i=piece_h/2;i<piece_h;i++)
	{
		for( j=piece_w/2;j< piece_w;j++)
		{
			if(Imgdata1[i][j][0]!=255 && Imgdata1[i][j][1]!=255 && Imgdata1[i][j][2]!=255)
			{
				if (flag==0)
				{ 
					itop=i;
					jtop=j+11;

					jleft=j+11;// 1st instance set to compare with the following values.
					ibottom=i;
					jright=j+11;

					flag=1;
				}
				else{

					if(j<jleft && Imgdata1[i][j+1][0]!=255 && Imgdata1[i][j+1][1]!=255 && Imgdata1[i][j+1][2]!=255 )
					{
						ileft=i;// after top has been set check conditions.
						jleft=j;
					}

					if(j>jright && Imgdata1[i][j+1][0]==255 && Imgdata1[i][j+1][1]==255 && Imgdata1[i][j+1][2]==255)
					{
						jright=j;
						iright=i+5;
					}

					if(Imgdata1[i+1][j][0]==255 && Imgdata1[i+1][j][1]==255 && Imgdata1[i+1][j][2]==255 && i>ibottom)
					{
						ibottom=i;
						jbottom=j;
					}
				}
			}

		}
	}
	cout<<" "<<endl;

	 cout<<"Locations of Trump piece image are as follows:"<<endl;

	cout<<"topvalues:" <<jtop<<" "<<itop<< endl;
	cout<<"rightvalues:" <<jright<<" "<<iright<< endl;
	cout<<"leftvalues:" <<jleft<<" "<<ileft<< endl;
	cout<<"bottomvalues:" <<jbottom<<" "<<ibottom<< endl;
	cout<< "  "<<endl;
	
	//cartesian coordinates of the image
	
	double U1,V1,U2,V2,U3,V3,U4,V4;
			U1=img2cartx(jbottom);
			U2=img2cartx(jleft);
			U3=img2cartx(jright);
			U4=img2cartx(jtop);

		V1=img2carty(ibottom,piece_h);
		V2=img2carty(ileft,piece_h);
		V3=img2carty(iright,piece_h);
		V4=img2carty(itop,piece_h);

	cout<<"topvalues cart:" <<U1<<" "<<V1<< endl;
	cout<<"rightvalues cart:" <<U2<<" "<<V2<< endl;
	cout<<"leftvalues cart:" <<U3<<" "<<V3<< endl;
	cout<<"bottomvalues cart:" <<U4<<" "<<V4<< endl;
	cout<< "  "<<endl;
//------------------------------------------------------------------------------------------------------	
	// Calculation of the width and height
	double wdistance=sqrt(pow((V4-V3),2.0)+pow((U4-U3),2.0));
	double hdistance=sqrt(pow((V1-V3),2.0)+pow((U1-U3),2.0));
	cout<<"height:"<<hdistance<< "   "<<"width:"<<wdistance<<endl;

	// Calculation of the scale factors in consideration.
	double scalefactorx=103/(wdistance);
	double scalefactory=103/(hdistance);


	// find the angle of the rotation
	double divfactor=(V3-V1)/(1.0*(U3-U1));
	double angle=-atan(divfactor)-(3.14159/2);
	cout<<"Angle in degrees:"<<angle*(180/3.14159)<<endl;
	cout<< "  "<<endl;

//------------------------------------------------------------------------------------------------------		

	// Find the uv cordinates by reverse mapping logic

	for(int i=0;i<piece_h;i++)
	{
		for(int j=0;j<piece_w;j++)
		{
			
		// image to cartesian and translate.
		double x=img2cartx(j);
		double y=img2carty(i,piece_h)-12*hdistance;

		
		// Rotation 

		double u=x*cos(angle)+y*sin(angle);
		double v=-1*x*sin(angle)+y*cos(angle);


	
		//Scaled value change 
		
		double u1=u/(1.0*scalefactorx);
		double v1=v/(1.0*scalefactory);

		
		// Convert to image cordinates and apply bilinear  

		double X=cart2imgx(u1);
		double Y=cart2imgy(v1,piece_h);

		 //Bilinear interpolation of floating point values.
				
		// New height and new height. 
		int nh = (int)Y;
		int nw = (int)X;
		
		// Checking boundary conditions
		
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


		// Calulate by how much the pixels along the height of the image would translate 
		double ydiff = Y - 1.0*nh;
		double xdiff = X - 1.0*nw;	

		// Resized values 
			Imgdata2[i][j][0] = (unsigned char)
											((1 - ydiff) * (1 - xdiff) * Imgdata1[nh][nw][0] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][0] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][0] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][0]);

			Imgdata2[i][j][1] = (unsigned char)
											((1 - ydiff)*(1 - xdiff) * Imgdata1[nh][nw][1] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][1] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][1] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][1]);

			Imgdata2[i][j][2] = (unsigned char)
											((1 - ydiff)*(1 - xdiff) * Imgdata1[nh][nw][2] +
											ydiff * (1 - xdiff) * Imgdata1[nh + 1][nw][2] +
											(1 - ydiff) * xdiff * Imgdata1[nh][nw + 1][2] +
											ydiff * xdiff * Imgdata1[nh + 1][nw + 1][2]);
		}
	}
//------------------------------------------------------------------------------------------------------	
	//location of trump top left.

	int xhill=0;
	int yhill=0;
	int xeye=0;
	int yeye=0;
	int flag1=0;
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w ;j++)
		{

			
			if(Imgdata[i][j][0]>252 && Imgdata[i][j][1]>252 && Imgdata[i][j][2]>252 && flag1==0 )
			{
				xhill=j;
				yhill=i;
				flag1=1;
			}
		}
	}
	cout<< "  "<<endl;
	cout<<"Missing Puzzle top value locations from where one to one mapping is needed to be carried out"<<endl;
	cout<<"Puzzle top location x:"<<xhill<<endl;
	cout<<"Puzzle top location y:"<<yhill<<endl;
	cout<< "  "<<endl;

	// First coordinate of the Trump missing piece image to remap.
	int flag2=0;
	for(int i=0;i<piece_h;i++)
	{
		for(int j=0;j<piece_w ;j++)
		{

			if(Imgdata2[i][j][0]<252 && Imgdata2[i][j][1]<252 && Imgdata2[i][j][2]<252 && flag2==0)
			
			{
				xeye=j;
				yeye=i;
				 flag2=1;
			}

		}
	}
	//cout<<xeye<<endl;
	//cout<<yeye<<endl;


	// Setting the output to the  missing puzzle .
	
	for(int i=0;i<Size_h;i++)
	{
		for(int j=0;j<Size_w ;j++)
		{
			if(Imgdata[i][j][0]>252 && Imgdata[i][j][1]>252 && Imgdata[i][j][2]>252 )
			{
				img1[i][j][0]=Imgdata2[yeye+i-yhill+2][xeye+j-xhill+1][0];
				img1[i][j][1]=Imgdata2[yeye+i-yhill+2][xeye+j-xhill+1][1];
				img1[i][j][2]=Imgdata2[yeye+i-yhill+2][xeye+j-xhill+1][2];
			}
			else
			{
				img1[i][j][0]=Imgdata[i][j][0];
				img1[i][j][1]=Imgdata[i][j][1];
				img1[i][j][2]=Imgdata[i][j][2];

			}
		}
	}
//------------------------------------------------------------------------------------------------------	
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





