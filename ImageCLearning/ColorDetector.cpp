#include "stdafx.h"
#include "ColorDetector.h"


ColorDetector* ColorDetector::init_ = nullptr;

ColorDetector::ColorDetector() : target(0, 0, 0), maxDist(100)
{
}


ColorDetector::~ColorDetector()
{
}

Mat ColorDetector::loadImage(string path)
{
	Mat myimage = imread(path, 1);
	if (!myimage.empty())
	{
		return myimage;
			
	}

	else { cout << "There is no image hier....." << endl; }
	
}

ColorDetector* ColorDetector::getInstance()
{
	if (init_ == nullptr)
	{
		init_ = new ColorDetector();
	}
	return init_;
}

void ColorDetector::setTargetColor(uchar blue, uchar green, uchar red)
{
	//RGB order 
	target = Vec3b(blue, green, red);
}

void ColorDetector::process(const Mat& image)
{
	//re-allocate binary map if necessary 
	//same size as input image, but 1-channel
	result.create(image.size(), CV_8U);
	//processing loop hier.....
	//get the iterators
	Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
	Mat_<uchar>::iterator itout = result.begin<uchar>();
	//for each pixel
	for (; it != itend; ++it , ++itout)
	{
		//compute distance from target color 
		if (getDistanceToTargetColor(*it) <= maxDist)
		{
			*itout = 255;
		}
		else *itout = 0;
	}
	namedWindow("Result", CV_WINDOW_NORMAL);
	imshow("Result", result);
	waitKey(0);
}

void ColorDetector::opencv_process(const Mat& image) const
{
	// use opencv function
	Mat output;
	absdiff(image, Scalar(target), output);
	std::vector<Mat> images;
	split(output, images);
	output = images[0] + images[1] + images[2];
	threshold(output, output, maxDist, 255, THRESH_BINARY);
	namedWindow("ResultOpencv", CV_WINDOW_NORMAL);
	imshow("ResultOpencv", output);
	waitKey(0);
}
