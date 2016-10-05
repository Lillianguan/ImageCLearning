// ImageCLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

//test function that create an image
Mat function()
{
	//creste imgae
	Mat ima(500,500,CV_8U,50);
    // return it 
	return ima;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//define image windows
	namedWindow("Image 1");
    namedWindow("Image 2");
	namedWindow("Image 3");
	namedWindow("Image 4");
	namedWindow("Image 5");
	namedWindow("Image");

	//create a new image made of 240 rows and 320 columns
	Mat image1(240,320,CV_8U,100);

	imshow("Image", image1); //show the image
	//waitKey(0); //wait for a key pressed

	// re-allocate a new image 
	image1.create(200,200,CV_8U);
	image1=200;

	imshow("Image", image1);
	//waitKey(0);

	//create a red color image 
	//channel order is BGR
	Mat image2(240,320,CV_8UC3,Scalar(0,0,255));

	//or
	//Mat image2(Size(320,240),CV_8UC3);
	//image2=Scalar(0,0,255);

	imshow("Image",image2);
	//waitKey(0);

	//read an image 
	Mat image3=imread("C:\\Users\\Cailin\\Pictures\\IMG_0427.JPG",CV_LOAD_IMAGE_GRAYSCALE);
	if(image3.empty())
		cout<<"there is no picture found..."<<endl;

	//all these images point to the same data block 
	Mat image4(image3);
	image1=image3;

	// these images are now copies of the source image
	image3.copyTo(image2);
	Mat image5=image3.clone();
	
	//tranceform the image for testing 
	flip(image3,image3,1);

	//check which images have been affected by the processing 
	imshow("Image 3",image3);
	imshow("Image 1",image1);
	imshow("Image 2",image2);
	imshow("Image 4",image4);
	imshow("Image 5",image5);
	//waitKey(0);

	//get a gray-level image from a function 
	Mat gray=function();

	imshow("Image",gray);
	//waitKey(0);

	//read the image in gray scale
	image1=imread("C:\\Users\\Cailin\\Pictures\\IMG_0427.JPG",CV_LOAD_IMAGE_GRAYSCALE);
	image1.convertTo(image2,CV_32F,1/255.0,0.0);

	imshow("Image",image2);
	//waitKey(0);

    Ptr<IplImage> iplimage=cvLoadImage("C:\\Users\\Cailin\\Pictures\\logo.jpg",0);
	Mat logoimg(iplimage,false);

	//define image ROI at image bottom-right
	Mat imageROI=image5(Rect(image5.cols-logoimg.cols,image5.rows-logoimg.rows,logoimg.cols,logoimg.rows));
	
	//insert logo
	Mat mask(logoimg);
	logoimg.copyTo(imageROI,mask);
	imshow("Image",image5);

	waitKey(0);
	return 0;
}


