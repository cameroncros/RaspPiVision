/*
 * BasicShapeDetection.cpp
 *
 *  Created on: 12 Sep 2015
 *      Author: cameron
 */

#include "BasicShapeDetection.h"

float BasicShapeDetection::maximum( float a, float b, float c )
{
	float max = ( a < b ) ? b : a;
	return ( ( max < c ) ? c : max );
}

float BasicShapeDetection::minimum( float a, float b, float c )
{
	float max = ( a > b ) ? b : a;
	return ( ( max > c ) ? c : max );
}

void BasicShapeDetection::RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
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

BasicShapeDetection::BasicShapeDetection(cv::VideoCapture &capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "BasicShapeDetection";

}

BasicShapeDetection::~BasicShapeDetection() {
	// TODO Auto-generated destructor stub
}

std::vector<Region *>* BasicShapeDetection::processFrame(cv::Mat& frame) {
	//code taken from squares.cpp in opencv docs. Modified to suit.
	double N = 3;
	squares.clear();

	cv::Mat pyr, timg, gray0(frame.size(), CV_8U), gray;

	cvtColor(frame, gray0, CV_BGR2GRAY);

	//	// down-scale and upscale the image to filter out the noise
	//	cv::pyrDown(frame, pyr, cv::Size(frame.cols/2, frame.rows/2));
	//	cv::pyrUp(pyr, timg, frame.size());
	std::vector<std::vector<cv::Point> > contours;

	// find squares in every color plane of the image

	//	int ch[] = {c, 0};
	//	mixChannels(&timg, 1, &gray0, 1, ch, 1);

	// try several threshold levels
	for( int l = 0; l < N; l++ )
	{
		// hack: use Canny instead of zero threshold level.
		// Canny helps to catch squares with gradient shading
		//		if( l == 0 )
		//		{
		//			// apply Canny. Take the upper threshold from slider
		//			// and set the lower to 0 (which forces edges merging)
		//			cv::Canny(gray0, gray, 0, thresh, 5);
		//			// dilate canny output to remove potential
		//			// holes between edge segments
		//			cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
		//		}
		//		else
		//		{
		// apply threshold if l!=0:
		//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
		gray = gray0 >= (l+1)*255/N;
		//		}

		// find contours and store them all as a list
		cv::findContours(gray, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		std::vector<cv::Point> approx;

		// test each contour
		for( size_t i = 0; i < contours.size(); i++ )
		{
			// approximate contour with accuracy proportional
			// to the contour perimeter
			cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

			// square contours should have 4 vertices after approximation
			// relatively large area (to filter out noisy contours)
			// and be convex.
			// Note: absolute value of an area is used because
			// area may be positive or negative - in accordance with the
			// contour orientation

			if(	fabs(cv::contourArea(cv::Mat(approx))) > 1000 &&
					cv::isContourConvex(cv::Mat(approx)) )
			{
				if (approx.size() == 4) {
					double maxCosine = 0;

					for( int j = 2; j < 5; j++ )
					{
						// find the maximum cosine of the angle between joint edges
						double cosine = fabs(anglePoint(approx[j%4], approx[j-2], approx[j-1]));
						if (maxCosine < cosine) {
							maxCosine = cosine;
						}
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
					if( maxCosine < 0.3 ) {
						double x=0;
						double y=0;
						int count = 0;
						for (cv::Point pt : approx) {
							x += pt.x;
							y += pt.y;
							count++;
						}
						x /= count;
						y /= count;
						double size = sqrt(fabs(cv::contourArea(cv::Mat(approx))));
						Color col = getColor(frame, x, y, size);
						regionList->push_back(new Region(x, y, size, col, SQUARE));
					}
				}
				else if (approx.size() == 3) {
					bool isTri = true;

					for( int j = 2; j < 3; j++ )
					{
						// find the maximum cosine of the angle between joint edges
						double cosine = fabs(anglePoint(approx[j%3], approx[j-2], approx[j-1]));
						if (cosine > 0.6 || cosine < 0.4) {
							isTri = false;
							break;
						}
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence
					if( isTri ) {
						double x=0;
						double y=0;
						int count = 0;
						for (cv::Point pt : approx) {
							x += pt.x;
							y += pt.y;
							count++;
						}
						x /= count;
						y /= count;
						double size = sqrt(fabs(cv::contourArea(cv::Mat(approx))));
						Color col = getColor(frame, x, y, size);
						regionList->push_back(new Region(x, y, size, col, TRIANGLE));
						std::cout << "Found a triangle" << std::endl;
					}
				}
				else {
					double C = cv::arcLength(approx, true);
					double A = cv::contourArea(approx);
					double ratio = C*C/(4*M_PI*A);
					if (ratio < 1.1 && ratio > 0.9) {
						double x=0;
						double y=0;
						int count = 0;
						for (cv::Point pt : approx) {
							x += pt.x;
							y += pt.y;
							count++;
						}
						x /= count;
						y /= count;
						double size = sqrt(fabs(cv::contourArea(cv::Mat(approx))));
						Color col = getColor(frame, x, y, size);
						regionList->push_back(new Region(x, y, size, col, CIRCLE));
						std::cout << "Found a circle" << std::endl;
					}

				}

			}
		}
	}
	return regionList;
}

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double BasicShapeDetection::anglePoint( cv::Point pt1, cv::Point pt2, cv::Point pt0 )
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

Color BasicShapeDetection::getColor(cv::Mat &frame, int x, int y, int size) {
	long r = 0, b = 0, g = 0, total=0;
	int squareWidth = size/2;
	for (int i = y-(squareWidth/2); i < y+(squareWidth/2); i++) {
		if (i < 0) {
			continue;
		} else if (i > frame.cols) {
			break;
		}
		for (int j = x-(squareWidth/2); j < x+(squareWidth/2); j++) {
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
			frame.at<cv::Vec3b>(i, j)=BLACK;
		}
	}
	if (total == 0) {
		return UNKNOWN;
	}
	r /= total;
	b /= total;
	g /= total;

	float h, s, v;

	RGBtoHSV(((float)r)/255, ((float)g)/255, ((float)b)/255, &h, &s, &v);

	//h *= 255;
	s *= 255;
	v *= 255;

	std::cout << h << ":" << s << ":" << v << std::endl;

	if (s < 70) {
		return WHITE;
	}
	if (v < 70) {
		return BLACK;
	}

	if (h < 280 && h > 200) {
		return BLUE;
	}

	if (h < 360 && h > 320) {
		return RED;
	}

	if (h < 150 && h > 90) {
		return GREEN;
	}

	return UNKNOWN;
}


