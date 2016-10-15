#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


class ColorDetector
{
public:
	ColorDetector();

	ColorDetector(uchar blue, uchar green, uchar red, int mxDist = 100) : maxDist(mxDist)
	{
		setTargetColor(blue, green, red);
	}

	~ColorDetector();
	static Mat loadImage(string path);
	static ColorDetector* getInstance();
	void process(const Mat& image);
	void opencv_process(const Mat& image) const;
	void setTargetColor(uchar blue, uchar green, uchar red);

	Vec3b getTargetColor() const
	{
		return target;
	}

	void setColorDistanceThreshold(int distance)
	{
		if (distance < 0)
			distance = 0;
		maxDist = distance;
	}

	int getColorDistanceThreshold() const
	{
		return maxDist;
	}

	int getDistanceToTargetColor(const Vec3b& color) const
	{
		return getColorDistance(color, target);
	}

	int getColorDistance(const Vec3b& color1, const Vec3b& color2) const
	{
		return abs(color1[0] - color2[0]) + abs(color1[1] - color2[1]) + abs(color1[2] - color2[2]);
	}
	Mat operator()(const cv::Mat &image) const
	{

		Mat input;
		input = image;
		Mat output;
		// compute absolute difference with target color
		absdiff(input, cv::Scalar(target), output);
		// split the channels into 3 images
		vector<cv::Mat> images;
		split(output, images);
		// add the 3 channels (saturation might occurs here)
		output = images[0] + images[1] + images[2];
		// apply threshold
		threshold(output,  // input image
			output,  // output image
			maxDist, // threshold (must be < 256)
			255,     // max value
			THRESH_BINARY_INV); // thresholding type

		return output;
	}

private:
	static ColorDetector* init_;
	Vec3b target;
	Mat result;
	int maxDist;
};

