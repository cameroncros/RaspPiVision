/*
 * HoughCircleDetection.cpp
 *
 *  Created on: 7 Sep 2015
 *      Author: cameron
 */

#include "HoughCircleDetection.h"

int HoughCircleDetection::maximum( int a, int b, int c )
{
   int max = ( a < b ) ? b : a;
   return ( ( max < c ) ? c : max );
}

int HoughCircleDetection::minimum( int a, int b, int c )
{
   int max = ( a > b ) ? b : a;
   return ( ( max > c ) ? c : max );
}

void HoughCircleDetection::RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;
	min = minimum( r, g, b );
	max = maximum( r, g, b );
	*v = max;				// v
	delta = max - min;
	if( max != 0 )
		*s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		*s = 0;
		*h = -1;
		return;
	}
	if( r == max )
		*h = ( g - b ) / delta;		// between yellow & magenta
	else if( g == max )
		*h = 2 + ( b - r ) / delta;	// between cyan & yellow
	else
		*h = 4 + ( r - g ) / delta;	// between magenta & cyan
	*h *= 60;				// degrees
	if( *h < 0 )
		*h += 360;
}

HoughCircleDetection::HoughCircleDetection(cv::VideoCapture &capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "HoughCircleDetection";

}

HoughCircleDetection::~HoughCircleDetection() {
	// TODO Auto-generated destructor stub
}

std::vector<Region *>*  HoughCircleDetection::processFrame(cv::Mat& frame) {
	//code taken from http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html
	cv::Mat newFrame;
	cvtColor(frame, newFrame, CV_BGR2GRAY);
	GaussianBlur(newFrame, newFrame, cv::Size(9, 9), 2, 2);
	cv::vector<cv::Vec3f> circles;
	HoughCircles(newFrame, circles, CV_HOUGH_GRADIENT, 1, frame.rows/8, 40, 40, 0, 0 );

	for (unsigned int i = 0; i < circles.size(); i++) {
		Color col = getColor(frame, circles[i][0], circles[i][1], circles[i][2]);
		regionList->push_back(new Region(circles[i][0], circles[i][1], circles[i][2], col));
	}
	return regionList;
}

//get average pixel colors in a square that is half the size;
Color HoughCircleDetection::getColor(cv::Mat frame, int x, int y, int size) {
	long r = 0, b = 0, g = 0, total=0;
	int squareWidth = size/2;
	for (int i = x-(squareWidth/2); i < x+(squareWidth/2); i++) {
		if (i < 0) {
			continue;
		} else if (i > frame.cols) {
			break;
		}
		for (int j = y-(squareWidth/2); j < y+(squareWidth/2); j++) {
			if (j < 0) {
				continue;
			} else if (j > frame.rows) {
				break;
			}
			total++;
			cv::Vec3b val = frame.at<cv::Vec3b>(i, j);
			r += val[RED];
			b += val[BLUE];
			g += val[GREEN];
		}
	}
	r /= total;
	b /= total;
	g /= total;

	float h, s, v;

	RGBtoHSV(((float)r)/255, ((float)g)/255, ((float)b)/255, &h, &s, &v);

	h *= 255;
	s *= 255;
	v *= 255;


	if (s < 70) {
		return WHITE;
	}
	if (v < 70) {
		return BLACK;
	}

	if (h < 280 && h > 200) {
		return BLUE;
	}

	return UNKNOWN;
}
