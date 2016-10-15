// ImageCLearning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ImageOperations.h"
#include "ColorDetector.h"

static string path = "IMG_0427.JPG";

int _tmain()
{
	const int64 start = getTickCount(); 

	ImageOperations* myimageoperations = ImageOperations::getInstance();
	ColorDetector *my_color_detector = ColorDetector::getInstance();
	Mat image=my_color_detector->loadImage(path);
	my_color_detector->setTargetColor(230, 160, 130);
	my_color_detector->process(image);
	ColorDetector color_detector(200,150,100,180);
	Mat result = color_detector(image);

	//elapsed time in seconds
	double duration = (getTickCount() - start) / getTickFrequency();
	cout << "Program runtime :" << duration <<"s"<< endl;
	cin.get();

	return 0;
}


