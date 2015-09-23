/*
 * BasicShapeDetection.cpp
 *
 *  Created on: 12 Sep 2015
 *      Author: cameron
 */

#include "BasicShapeDetection.h"

BasicShapeDetection::BasicShapeDetection(cv::VideoCapture &capture) : ImageProcessor::ImageProcessor(capture) {
	// TODO Auto-generated constructor stub
	methodType = "BasicShapeDetection";

}

BasicShapeDetection::~BasicShapeDetection() {
	// TODO Auto-generated destructor stub
}

std::vector<Region *>* BasicShapeDetection::processFrame(cv::Mat& frame) {
	//code taken from squares.cpp in opencv docs. Modified to suit.
	double thresh = 1;
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
			if( approx.size() == 4 &&
					fabs(cv::contourArea(cv::Mat(approx))) > 1000 &&
					cv::isContourConvex(cv::Mat(approx)) )
			{
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
					regionList->push_back(new Region(x, y, fabs(cv::contourArea(cv::Mat(approx)))));
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
