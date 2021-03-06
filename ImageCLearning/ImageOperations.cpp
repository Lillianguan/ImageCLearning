#include "StdAfx.h"
#include "ImageOperations.h"

ImageOperations* ImageOperations::inst_ = nullptr;


ImageOperations::ImageOperations(void)
{
	i=0;
	j=0;
}


ImageOperations::~ImageOperations(void)
{
}

ImageOperations* ImageOperations::getInstance()
{
	if (inst_ == nullptr)
	{
		inst_ = new ImageOperations();
	}
	return inst_;
}

void ImageOperations::loadimage(string path)
{
	myimg = imread(path);
}

void ImageOperations::imagedatastructure() const
{
	//define image windows
	namedWindow("Image 1");
	namedWindow("Image 2");
	namedWindow("Image 3");
	namedWindow("Image 4");
	namedWindow("Image 5");
	namedWindow("Image");

	//create a new image made of 240 rows and 320 columns
	Mat image1(240, 320,CV_8U, 100);

	imshow("Image", image1); //show the image
	//waitKey(0); //wait for a key pressed

	// re-allocate a new image 
	image1.create(200, 200,CV_8U);
	image1 = 200;

	imshow("Image", image1);
	//waitKey(0);

	//create a red color image 
	//channel order is BGR
	Mat image2(240, 320,CV_8UC3, Scalar(0, 0, 255));

	//or
	//Mat image2(Size(320,240),CV_8UC3);
	//image2=Scalar(0,0,255);

	imshow("Image", image2);
	//waitKey(0);

	//read an image 
	Mat image3 = myimg.clone();
	if (image3.empty())
		cout << "there is no picture found..." << endl;

	//all these images point to the same data block 
	Mat image4(image3);
	image1 = image3;

	// these images are now copies of the source image
	image3.copyTo(image2);
	Mat image5 = image3.clone();

	//tranceform the image for testing 
	flip(image3, image3, 1);

	//check which images have been affected by the processing 
	imshow("Image 3", image3);
	imshow("Image 1", image1);
	imshow("Image 2", image2);
	imshow("Image 4", image4);
	imshow("Image 5", image5);
	//waitKey(0);

	//get a gray-level image from a function 
	Mat gray = function();

	imshow("Image", gray);
	//waitKey(0);

	//read the image in gray scale
	image1 = imread("IMG_0427.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	image1.convertTo(image2,CV_32F, 1 / 255.0, 0.0);

	imshow("Image", image2);
	//waitKey(0);

	Ptr<IplImage> iplimage = cvLoadImage("logo.jpg", 1);
	Mat logoimg(iplimage, false);

	//define image ROI at image bottom-right
	Mat imageROI = image5(Rect(image5.cols - logoimg.cols, image5.rows - logoimg.rows, logoimg.cols, logoimg.rows));

	//insert logo

	//Mat mask(logoimg);//must in gray-level
	//logoimg.copyTo(imageROI,mask);

	logoimg.copyTo(imageROI);
	imshow("Image", image5);

	waitKey(0);
}

void ImageOperations::salt(int n)
{
	cout << i << j << endl;
	Mat image = myimg.clone();
	for (int k = 0; k < n; k++)
	{
		//rand() is the random number generator 
		i = rand() % image.cols;
		j = rand() % image.rows;

		if (image.type() == CV_8UC1)
		{
			//gray-level image 
			image.at<uchar>(j, i) = 255;
		}
		else if (image.type() == CV_8UC3)
		{
			//color image red green blue channels
			image.at<Vec3b>(j, i)[0] = 255; //vec3b---vevtor of three unsigned characters
			image.at<Vec3b>(j, i)[1] = 255;
			image.at<Vec3b>(j, i)[2] = 255;
		}
	}

	imshow("Image", image);
	waitKey(0);
}

void ImageOperations::colorReduce(int div) const
{
	Mat image = myimg.clone();
	int nl = image.rows;//number of lines 
	//total number of elements per line 
	int nc = image.cols * image.channels();
	if (image.isContinuous())
	{
		//then no padded pixels
		nc = nc * nl;
		nl = 1;
		cout << "This image is continous!!" << endl;
	}//this loop is executed only once 
	//in case of continous images
	for (int j = 0; j < nl; j++)
	{
		//get the adresse of row j
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++)
		{
			//process each pixel---
			data[i] = data[i] / div * div + div / 2;
			//end of pixel processing---
		}//end of line 
	}
	imshow("Image", image);
	waitKey(0);
}

void ImageOperations::colorReduceIterator(int div)
{
	//obtain iterator at initial position 
	MatIterator_<Vec3b> it = myimg.begin<Vec3b>();
	//obtain end position 
	MatIterator_<Vec3b> itend = myimg.end<Vec3b>();
	//loop over all pixel------------

	//for (; it != itend; ++it)
	//{
	//	//process each pixel-------
	//	(*it)[0] = (*it)[0] / div * div + div / 2;
	//	(*it)[1] = (*it)[1] / div * div + div / 2;
	//	(*it)[2] = (*it)[2] / div * div + div / 2;
	//	// end of pixel processing-------
	//}

	//or
	while (it != itend)
	{
		//process each pixel 
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
		//end of pixel processing 

		//++it;

		//or
		it += 5;
	}

	imshow("Image", myimg);
	waitKey(0);
}

void ImageOperations::sharpen()
{
	Mat result;
	//allocate if necessary
	result.create(myimg.size(), myimg.type());
	int nchannels = myimg.channels(); // get the number of channels 

	//for all rows (except first and last)
	for (int j = 1; j < myimg.rows - 1; j++)
	{
		const uchar* previous = myimg.ptr<const uchar>(j - 1); //previous row
		const uchar* current = myimg.ptr<const uchar>(j); //current row
		const uchar* next = myimg.ptr<const uchar>(j + 1); //next row
		uchar* output = result.ptr<uchar>(j); //output row
		for (int i = nchannels; i < (myimg.cols - 1) * nchannels; i++)
		{
			*output++ = saturate_cast<uchar>(5 * current[i] - current[i - nchannels] - current[i + nchannels] - previous[i] - next[i]);
		}
	}
	//set the unprocessed pixels to 0;
	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));
	imshow("Image", result);
	waitKey(0);
}

void ImageOperations::sharpen2D() const
{
	Mat result;
	//Construct kernel (all entries initializd to 0)
	Mat kernel(3, 3, CV_32F, Scalar(0));
	//assigns kernel values 
	kernel.at<float>(1, 1) = 10.0;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;

	//filter the image 
	filter2D(myimg, result, myimg.depth(), kernel);
	imshow("Image", result);
	waitKey(0);
}
//remaping an image by creating wave effects
void ImageOperations::wave() const
{
	// the map function 
	Mat inputimage=myimg.clone();
	Mat outputimage;
	Mat srcX(inputimage.rows,inputimage.cols,CV_32F);
	Mat srcY(inputimage.rows,inputimage.cols,CV_32F);
	//creating the mapping 
	for(int i=0;i<inputimage.rows;i++)
		for (int j=0;j<inputimage.cols ;j++)
		{
			//new location of pixel at (i,j)
			srcX.at<float>(i, j) = j; //remain the same column pixels originally on row i are now moved fllowing a sinusoid
			srcY.at<float>(i, j) = i + 5 * sin(j/10.0);

		}
	// applaying the mapping 
	remap(inputimage, outputimage, srcX, srcY, INTER_LINEAR);
	namedWindow("Result", CV_WINDOW_NORMAL);
	imshow("Result",outputimage);
	waitKey(0);
}

Mat ImageOperations::function()
{
	//creste imgae
	Mat ima(500, 500,CV_8U, 50);
	// return it 
	return ima;
}
