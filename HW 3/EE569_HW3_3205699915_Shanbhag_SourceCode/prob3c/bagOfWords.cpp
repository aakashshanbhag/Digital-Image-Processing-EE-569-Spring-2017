#include <stdio.h>
#include <iostream>
#include <fstream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <cmath>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

void readme();

/** @function main */
int main(int argc, char** argv)
{
	if (argc != 5)
	{
		readme(); return -1;
	}

	Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE); // suv
	Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE); // truck 
	Mat img_3 = imread(argv[3], IMREAD_GRAYSCALE); // c1
	Mat img_4 = imread(argv[4], IMREAD_GRAYSCALE); // c2

	if (!img_1.data || !img_2.data || !img_3.data || !img_4.data)
	{
		std::cout << " --(!) Error reading images " << std::endl; return -1;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 800;

	Ptr<SIFT> detector = SIFT::create(minHessian);

	std::vector<KeyPoint> keypoints_1, keypoints_2, keypoints_3, keypoints_4;
	Mat descriptors_1, descriptors_2, descriptors_3, descriptors_4;

	detector->detect(img_1, keypoints_1);
	detector->detect(img_2, keypoints_2);
	detector->detect(img_3, keypoints_3);
	detector->detect(img_4, keypoints_4);

	detector->compute(img_1, keypoints_1, descriptors_1);
	detector->compute(img_2, keypoints_2, descriptors_2);
	detector->compute(img_3, keypoints_3, descriptors_3);
	detector->compute(img_4, keypoints_4, descriptors_4);

	/* BAG OF WORDS */
	BOWKMeansTrainer BoW(8);
	
	BoW.add(descriptors_3);
	BoW.add(descriptors_1);
	BoW.add(descriptors_2);
	Mat vocabulary = BoW.cluster();

	/* debug data obtained */
	cout << descriptors_1.size() << endl;
	cout << descriptors_2.size() << endl;
	cout << descriptors_3.size() << endl;
	cout << descriptors_4.size() << endl;
	cout << vocabulary.size() << endl;

	/* for histograms data calculation and tranferring data to MATLAB for evaluation and plotting */
	int* hist_img1 = new int[vocabulary.rows]();
	int* hist_img2 = new int[vocabulary.rows]();
	int* hist_img3 = new int[vocabulary.rows]();
	int* hist_img4 = new int[vocabulary.rows]();
	for (int i = 0; i < vocabulary.rows;i++)
	{
		hist_img1[i] = 0;
		hist_img2[i] = 0;
		hist_img3[i] = 0;
		hist_img4[i] = 0;
	}

	/* write histogram data to file */
	double temp1[8] = { 0,0,0,0,0,0,0,0 };
	double d1[8] = { 0,0,0,0,0,0,0,0 };
	double temp2[8] = { 0,0,0,0,0,0,0,0 };
	double d2[8] = { 0,0,0,0,0,0,0,0 };
	double temp3[8] = { 0,0,0,0,0,0,0,0 };
	double d3[8] = { 0,0,0,0,0,0,0,0 };
	double temp4[8] = { 0,0,0,0,0,0,0,0 };
	double d4[8] = { 0,0,0,0,0,0,0,0 };
	
	//SUV
	for (int i = 0;i < descriptors_1.rows;i++)
	{
		for (int m = 0; m < 8;m++)
		{
			temp1[m] = 0;
			d1[m] = 0;
		}
		for (int j = 0; j < descriptors_1.cols; j++)
		{
			temp1[0] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(0, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(0, j));
			temp1[1] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(1, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(1, j));
			temp1[2] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(2, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(2, j));
			temp1[3] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(3, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(3, j));
			temp1[4] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(4, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(4, j));
			temp1[5] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(5, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(5, j));
			temp1[6] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(6, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(6, j));
			temp1[7] += (descriptors_1.at<float>(i, j) - vocabulary.at<float>(7, j)) * (descriptors_1.at<float>(i, j) - vocabulary.at<float>(7, j));
		}
		d1[0] = sqrt(temp1[0]);
		d1[1] = sqrt(temp1[1]);
		d1[2] = sqrt(temp1[2]);
		d1[3] = sqrt(temp1[3]);
		d1[4] = sqrt(temp1[4]);
		d1[5] = sqrt(temp1[5]);
		d1[6] = sqrt(temp1[6]);
		d1[7] = sqrt(temp1[7]);

		double min = d1[0];
		int index = 0;
		for (int k = 0; k < 8;k++)
		{
			if (d1[k] < min)
			{
				min = d1[k];
				index = k;
			}
		}
		hist_img1[index]++;
	}
	cout << endl;
	for (int i = 0;i < 8;i++)
	{
		cout << hist_img1[i] << "\t";
	}

	ofstream file1("hist_suv.txt");
	for (int i = 0;i < 8;i++)
	{
		file1 << hist_img1[i] << "\t";
	}


	// TRUCK
	for (int i = 0;i < descriptors_2.rows;i++)
	{
		for (int m = 0; m < 8;m++)
		{
			temp2[m] = 0;
			d2[m] = 0;
		}
		for (int j = 0; j < descriptors_2.cols; j++)
		{
			temp2[0] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(0, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(0, j));
			temp2[1] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(1, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(1, j));
			temp2[2] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(2, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(2, j));
			temp2[3] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(3, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(3, j));
			temp2[4] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(4, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(4, j));
			temp2[5] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(5, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(5, j));
			temp2[6] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(6, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(6, j));
			temp2[7] += (descriptors_2.at<float>(i, j) - vocabulary.at<float>(7, j)) * (descriptors_2.at<float>(i, j) - vocabulary.at<float>(7, j));
		}
		d2[0] = sqrt(temp2[0]);
		d2[1] = sqrt(temp2[1]);
		d2[2] = sqrt(temp2[2]);
		d2[3] = sqrt(temp2[3]);
		d2[4] = sqrt(temp2[4]);
		d2[5] = sqrt(temp2[5]);
		d2[6] = sqrt(temp2[6]);
		d2[7] = sqrt(temp2[7]);

		double min = d2[0];
		int index = 0;
		for (int k = 0; k < 8;k++)
		{
			if (d2[k] < min)
			{
				min = d2[k];
				index = k;
			}
		}
		hist_img2[index]++;
	}
	cout << endl;
	for (int i = 0;i < 8;i++)
	{
		cout << hist_img2[i] << "\t";
	}
	ofstream file2("hist_truck.txt");
	for (int i = 0;i < 8;i++)
	{
		file2 << hist_img2[i] << "\t";
	}

	// CONV1
	for (int i = 0;i < descriptors_3.rows;i++)
	{
		for (int m = 0; m < 8;m++)
		{
			temp3[m] = 0;
			d3[m] = 0;
		}
		for (int j = 0; j < descriptors_3.cols; j++)
		{
			temp3[0] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(0, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(0, j));
			temp3[1] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(1, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(1, j));
			temp3[2] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(2, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(2, j));
			temp3[3] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(3, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(3, j));
			temp3[4] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(4, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(4, j));
			temp3[5] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(5, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(5, j));
			temp3[6] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(6, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(6, j));
			temp3[7] += (descriptors_3.at<float>(i, j) - vocabulary.at<float>(7, j)) * (descriptors_3.at<float>(i, j) - vocabulary.at<float>(7, j));
		}
		d3[0] = sqrt(temp3[0]);
		d3[1] = sqrt(temp3[1]);
		d3[2] = sqrt(temp3[2]);
		d3[3] = sqrt(temp3[3]);
		d3[4] = sqrt(temp3[4]);
		d3[5] = sqrt(temp3[5]);
		d3[6] = sqrt(temp3[6]);
		d3[7] = sqrt(temp3[7]);

		double min = d3[0];
		int index = 0;
		for (int k = 0; k < 8;k++)
		{
			if (d3[k] < min)
			{
				min = d3[k];
				index = k;
			}
		}
		hist_img3[index]++;
	}
	cout << endl;
	for (int i = 0;i < 8;i++)
	{
		cout << hist_img3[i] << "\t";
	}
	ofstream file3("hist_c1.txt");
	for (int i = 0;i < 8;i++)
	{
		file3 << hist_img3[i] << "\t";
	}

	// CONV2
	for (int i = 0;i < descriptors_4.rows;i++)
	{
		for (int m = 0; m < 8;m++)
		{
			temp4[m] = 0;
			d4[m] = 0;
		}
		for (int j = 0; j < descriptors_4.cols; j++)
		{
			temp4[0] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(0, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(0, j));
			temp4[1] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(1, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(1, j));
			temp4[2] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(2, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(2, j));
			temp4[3] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(3, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(3, j));
			temp4[4] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(4, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(4, j));
			temp4[5] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(5, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(5, j));
			temp4[6] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(6, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(6, j));
			temp4[7] += (descriptors_4.at<float>(i, j) - vocabulary.at<float>(7, j)) * (descriptors_4.at<float>(i, j) - vocabulary.at<float>(7, j));
		}
		d4[0] = sqrt(temp4[0]);
		d4[1] = sqrt(temp4[1]);
		d4[2] = sqrt(temp4[2]);
		d4[3] = sqrt(temp4[3]);
		d4[4] = sqrt(temp4[4]);
		d4[5] = sqrt(temp4[5]);
		d4[6] = sqrt(temp4[6]);
		d4[7] = sqrt(temp4[7]);

		double min = d4[0];
		int index = 0;
		for (int k = 0; k < 8;k++)
		{
			if (d4[k] < min)
			{
				min = d4[k];
				index = k;
			}
		}
		hist_img4[index]++;
	}
	cout << endl;
	for (int i = 0;i < 8;i++)
	{
		cout << hist_img4[i] << "\t";
	}
	ofstream file4("hist_c2.txt");
	for (int i = 0;i < 8;i++)
	{
		file4 << hist_img4[i] << "\t";
	}

	waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{
	cout << " Usage: ./SIFT_detector <img1> <img2> <img3> <img4>" << std::endl;
}