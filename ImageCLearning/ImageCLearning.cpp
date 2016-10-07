// ImageCLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ImageOperations.h"

static string path = "IMG_0427.JPG";

int _tmain()
{
	const int64 start = getTickCount(); 
	ImageOperations* myimageoperations = ImageOperations::getInstance();
	myimageoperations->loadimage(path);
	//myimageoperations->imagedatastructure();
	//myimageoperations->salt(20000);
	//myimageoperations->colorReduce(64);
	//myimageoperations->colorReduceIterator(2000);
	//myimageoperations->sharpen();
	myimageoperations->sharpen2D();


	//elapsed time in seconds
	double duration = (getTickCount() - start) / getTickFrequency();
	cout << "Program runtime :" << duration <<"s"<< endl;
	cin.get();

	return 0;
}


