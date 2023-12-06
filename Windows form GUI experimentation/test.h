#pragma once
#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#ifndef CLIP_H
#define CLIP_H

class test {
public:
	test(double start_time, double end_time, std::string clip_name, int& clip_num); //constructor when user has a start and end time
	test(std::string clip_name, int& clip_num, double max_length = 8, double min_length = 3); //automatically start and end time with ai (random or facial recognition). Max length of video in seconds. Default 6

	//Methods
	void WriteTo(cv::VideoWriter output);//writes the object frames 
	void FacialRecognition(int& start);
	void Display();
	void setDuration(float start, float end);
	void Create(double max_length = 8, double min_length = 3);
	bool FindNotBlurry(double min_length = 3);

	//Motion detection
	void motionDetect();

	//Get functions
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	double getFPS() const { return fps; }

	int id;
	clip* next;
	clip* prev;


private:
	double start_timestamp = 0; //starting frame
	double end_timestamp = 0; //end frame
	std::string video_path; //path to the clip

	int width;
	int height;
	double fps;
	cv::VideoWriter slice; //spice represents the edited clip from the clip_name.mp4 that is created as a result of this class.
};

#endif // HEADER_FILE_NAME_H