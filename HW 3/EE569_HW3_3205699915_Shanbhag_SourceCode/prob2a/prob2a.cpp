#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           

int main(int argc, char* argv[]) 
{
	cv::Mat imgOriginal;        // input image
	cv::Mat imgOriginal1;        // input image
	cv::Mat imgGrayscale;       // grayscale of input image
	cv::Mat imgBlurred;         // intermediate blurred image
	cv::Mat imgCanny;           // Canny edge image

	imgOriginal = imread(argv[1], cv::IMREAD_COLOR);
	if (imgOriginal.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}

	cv::cvtColor(imgOriginal, imgGrayscale, CV_RGB2GRAY);       // convert to grayscale

	cv::GaussianBlur(imgGrayscale,          // input image
		imgBlurred,                         // output image
		cv::Size(5, 5),                     // smoothing window width and height in pixels
		0.33);                               // sigma value, determines how much the image will be blurred

	cv::Canny(imgBlurred,           // input image
		imgCanny,                   // output image
		100,              // low threshold
		200);             // high threshold

									// declare windows
	cv::namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);     // note: you can use CV_WINDOW_NORMAL which allows resizing the window
	cv::namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
															// CV_WINDOW_AUTOSIZE is the default
	cv::imshow("imgOriginal", imgOriginal);     // show windows
	cv::imshow("imgCanny", imgCanny);

	imwrite(argv[2], imgCanny);

	cv::waitKey(0);                 // hold windows open until user presses a key

	return(0);
}