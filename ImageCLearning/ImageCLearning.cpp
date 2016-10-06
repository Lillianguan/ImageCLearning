// ImageCLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ImageOperations.h"

static string path = "C:\\Users\\Cailin\\Pictures\\IMG_0427.JPG";

int _tmain()
{
	ImageOperations* myimageoperations = ImageOperations::getInstance();
	myimageoperations->loadimage(path);
	//myimageoperations->imagedatastructure();
	myimageoperations->salt(20000);
	myimageoperations->colorReduce(64);

	return 0;
}


