/*
 * ImageProcessor.h
 *
 *  Created on: Apr 25, 2015
 *      Author: cameron
 */

#ifndef IMAGEPROCESSOR_H_
#define IMAGEPROCESSOR_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "Region.h"

void onMouse(int event, int x, int y, int, void*);

class Region;

class ImageProcessor {
protected:
	cv::VideoCapture *capture;
	int n = 0;
	char filename[200];
	std::string window_name = "video | q or esc to quit";
	std::map<int, Region*> baseline;
	std::map<int, Region*> calc;
	std::string methodType;
	cv::Vec3b black;
	long totalTime, minTime, maxTime;
	long foundObject, totalObjects, totalFrames;
	int numFrames;
	std::vector<Region*> *regionList;

public:
	ImageProcessor(cv::VideoCapture &capture);
	virtual ~ImageProcessor();
	void process(int numFrames);
	double distance(cv::Mat &frame, Region &var);
	double angle(cv::Mat &frame, Region &var);
	virtual std::vector<Region*> *processFrame(cv::Mat &frame)=0;
	void printCentre(int line, Region &val);
	void drawArrow(cv::Mat &frame, double angle, double dist);
	void drawFrame(cv::Mat &frame);
	void saveFrame(const cv::Mat& frame);
	void processKeys(cv::Mat &frame);
	void initialiseWindow();
	void loadBenchmark(std::string benchfile);
	int compareToBaseline();
	void printReport(std::string filename);
	void cleanRegionList();
};


bool compareBySize(const Region *a, const Region *b);

#endif /* IMAGEPROCESSOR_H_ */
