#include <iostream>
#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/video/tracking.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <vector>
#include <sys\stat.h>

#include "AI.h"
#include "Clip.h"

//Namespaces
using namespace cv;
using namespace std;


AI::AI(std::string text_file)
{
    txt_file = text_file;
}

//Transitions
void AI::fade(Clip* clip1, Clip* clip2)
{
    std::string path = "D:\\Dataset\\";

    std::string imgpath1 = path + "4.2.01.tiff";
    std::string imgpath2 = path + "4.2.03.tiff";

    cv::Mat img1 = cv::imread(imgpath1, 1);
    cv::Mat img2 = cv::imread(imgpath2, 1);

    for (double i = 0; i <= 1; i += 0.001) {
        double alpha = i;
        double beta = 1 - alpha;
        cv::Mat output;
        cv::addWeighted(img1, alpha, img2, beta, 0, output);
        cv::imshow("Transition", output);
        cv::waitKey(1);
    }

    cv::destroyAllWindows();
}

void AI::blur(Clip* clip1, Clip* clip2)
{
    std::string path = "D:\\Dataset\\";
    // Load the first video clip
    cv::VideoCapture video1(path);
    if (!video1.isOpened()) {
        std::cerr << "Error: Could not open video1." << std::endl;
        return;
    }

    // Load the second video clip
    cv::VideoCapture video2(path);
    if (!video2.isOpened()) {
        std::cerr << "Error: Could not open video2." << std::endl;
        return;
    }

    // Get the frame dimensions (assumes both videos have the same dimensions)
    int frameWidth = static_cast<int>(video1.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(video1.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Create a VideoWriter to save the output video
    cv::VideoWriter outputVideo("output.mp4", cv::VideoWriter::fourcc('X', '2', '6', '4'), 30, cv::Size(frameWidth, frameHeight));

    // Variables for blending the frames
    double alpha = 0.0;  // Weight of the first frame
    cv::Mat frame1, frame2, result;

    while (true) {
        video1 >> frame1;
        video2 >> frame2;

        if (frame1.empty() || frame2.empty()) {
            break;
        }

        // Apply a blur effect to the frames
        cv::GaussianBlur(frame1, frame1, cv::Size(15, 15), 0);
        cv::GaussianBlur(frame2, frame2, cv::Size(15, 15), 0);

        // Blend the two frames using alpha
        cv::addWeighted(frame1, alpha, frame2, 1 - alpha, 0, result);

        // Write the blended frame to the output video
        outputVideo.write(result);

        alpha += 0.01;  // Increase alpha for the next frame transition
        if (alpha >= 1.0) {
            alpha = 1.0;
        }

        cv::imshow("Transition", result);
        if (cv::waitKey(30) == 27) {  // Press 'Esc' key to exit
            break;
        }
    }

    // Release video capture and writer
    video1.release();
    video2.release();
    outputVideo.release();
}