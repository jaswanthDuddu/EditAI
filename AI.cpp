#include <iostream>
#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
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

void setPacing(string value)
{
    pacing.push_back(value);
}

void setTransitions(string value)
{
    transitions.push_back(value);
}

void setColorCorrection(string value)
{
    color_correction.push_back(value);
}

void setEffects(string value)
{
    effects.push_back(value);
}


string findColorCorrection()
{
    string color;

    std::vector<std::string> warmColorWords = {
        "fiery", "vibrant", "lively", "rich", "sunny",
        "glowing", "radiant", "warm", "earthy", "inviting",
        "golden", "amber", "rusty", "cozy", "tropical",
        "blazing", "intense", "hearty", "warm", "balmy"
    };

    std::vector<std::string> coldColorWords  = {
        "icy", "frosty", "chilly", "crisp", "azure",
        "cerulean", "cool", "refreshing", "breezy", "wintry",
        "polar", "frozen", "glacial", "frigid", "calm",
        "tranquil", "serene", "aquatic", "steel", "cobalt"
    };

    //Finds if clips should have a warm color corrction
    for (int i = 0; i < warmColorWords.size(); i++)
    {
        for (int z = 0; z < warmColorWords.size(); z++)
        {
            if (warmColorWords[i] = color_correction[z])
            {
                color = "warm";
                return color;
            }
        }
    }

    //Finds if clips should have a cold color correction
    for (int i = 0; i < coldColorWords.size(); i++)
    {
        for (int z = 0; z < coldColorWords.size(); z++)
        {
            if (coldColorWords[i] = color_correction[z])
            {
                color = "cold";
                return color;
            }
        }
    }


    return color;
}

string findTransition()
{
    string transition = "none";

    //Database to identify OpenAI's reponse
    vector<std::string> wipe_keywords = {
        "swift", "quick", "speedy", "rapid", "hasty",
        "brisk", "fleet", "nimble", "prompt", "expeditious",
        "agile", "lively", "zippy", "spry", "accelerated",
        "hurried", "energetic", "speeding", "fleet-footed", "whirlwind"
    };


    vector<std::string> fade_keywords = {
        "calm", "easy", "relaxed", "leisurely", "mellow",
        "placid", "serene", "soft", "smooth", "unhurried",
        "deliberate", "pliable", "gentle", "tender", "patient",
        "easygoing", "gradual", "peaceful", "tranquil", "sluggish"
    };

    //Finds if clips should wipe if the input is fast
    for (int i = 0; i < wipe_keywords.size(); i++)
    {
        for (int z = 0; z < wipe_keywords.size(); z++)
        {
            if (wipe_keywords[i] = transitions[z])
            {
                transition = "wipe";
                return transition;
            }
        }
    }

    //Finds if clips should fade if the input is slow
    for (int i = 0; i < fade_keywords.size(); i++)
    {
        for (int z = 0; z < fade_keywords.size(); z++)
        {
            if (fade_keywords[i] = transitions[z])
            {
                transition = "fade";
                return transition;
            }
        }
    }

    return transition;
}

AI.findTransition();
string pacing = AI.findPacing();
string color_correction = AI.findColorCorrection();
string effects = AI.findEffects();

/// STORES TRANSITION/EFFECT INFORMATION ///

void AI::fade(Clip* clip1, Clip* clip2)
{
    /*
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
    */
}

void AI::blur(Clip* clip1, Clip* clip2)
{
    /*
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
    */
}

void AI::wipe(cv::VideoCapture& inputVideo1, cv::VideoCapture& inputVideo2, cv::VideoWriter& outputVideo) {
    /*
    if (!inputVideo1.isOpened() || !inputVideo2.isOpened()) {
        std::cerr << "Error: Could not open input videos." << std::endl;
        return;
    }

    int frame_width = static_cast<int>(inputVideo1.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(inputVideo1.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = inputVideo1.get(cv::CAP_PROP_FPS);

    cv::Size frame_size(frame_width, frame_height);
    
    while (true) {
        cv::Mat frame1, frame2;
        inputVideo1 >> frame1;
        inputVideo2 >> frame2;

        if (frame1.empty() || frame2.empty()) {
            break;
        }

        // Calculate the wipe transition effect by gradually revealing frame2 over frame1
        double alpha = 0.0; // Transition factor
        while (alpha <= 1.0) {
            cv::Mat combined_frame;
            cv::addWeighted(frame1, 1.0 - alpha, frame2, alpha, 0.0, combined_frame);
            outputVideo.write(combined_frame);
            alpha += 0.02; //adjust the transition speed by changing this value
        }

        // Write the final frame from inputVideo2 (frame2) to outputVideo
        outputVideo.write(frame2);
    }

    inputVideo1.release();
    inputVideo2.release();
    outputVideo.release();
    */
}



//Effects
void slowMotion(cv::VideoCapture& inputVideo, cv::VideoWriter& outputVideo, double slowFactor) {
    /*
    if (!inputVideo.isOpened()) {
        std::cerr << "Error: Could not open input video." << std::endl;
        return;
    }

    int frame_width = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = inputVideo.get(cv::CAP_PROP_FPS);

    cv::Size frame_size(frame_width, frame_height);
    
    while (true) {
        cv::Mat frame;
        inputVideo >> frame;

        if (frame.empty()) {
            break;
        }

        // Writes the same frame multiple times to create the slow-motion effect
        for (int i = 0; i < slowFactor; i++) {
            outputVideo.write(frame);
        }
    }

    inputVideo.release();
    outputVideo.release();
    */
}
