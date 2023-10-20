#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#ifndef TEST_H
#define TEST_H

class Clip {
public:
    // Constructor
    Clip(std::string clip_name, int& clip_num, std::string path, double max_length = 8, double min_length = 4);

    // Video Processing Methods
    void WriteTo(cv::VideoWriter output);
    void FacialRecognition(int& start);
    void Display();
    void Create(double max_length = 8, double min_length = 4);
    bool FindNotBlurry(double video_length = 4);

    // Set Functions
    void setStart(float start);
    void setEnd(float end);

    // Get Functions
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getFPS() const { return fps; }
    double getLength() const { return video_length; }

    int id;
    Clip* next;
    Clip* prev;

private:
    // Member Variables
    double video_length;
    double start_timestamp = 0;
    double end_timestamp = 0;
    std::string video_path;
    int width;
    int height;
    double fps;
    cv::VideoWriter slice;
};

#endif // HEADER_FILE_NAME_H