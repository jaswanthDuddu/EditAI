#include "pch.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

#include <math.h>
#include <cmath>

#include "clip.h"

using namespace cv; //prevents writing cv::imread
using namespace std;

using namespace System;

#include "Form1.h"

using namespace System::Windows::Forms;


//////////  VIDEO  //////////
/*
Using a linked list to store video clips
	- Dynamic memory allocation so memory can be added or removed during runtime. The size of the data structure changes frequently.
	- Efficient insertion and deletion operations are more efficient than other data structures.
	- Relatively simple and efficient.
*/


[STAThread]
int main()
{
	//Running windows form
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinFormsProject::Form1());

	/*
	int clip_num = 0;

	///// USING FACIAL DETECTION TO DETERMINE START AND STOP TIMES /////

	
	clip* clip1 = new clip("mount.mp4", clip_num); //instantiates object of bateman, with the corresponding parameters
	clip* clip2 = new clip("ride1.mp4", clip_num);
	clip* clip3 = new clip("ride2.mp4", clip_num);

	clip1->next = clip2;
	clip2->next = clip3;
	clip3->next = nullptr;

	clip* curr = clip1;
	while (curr != nullptr)
	{
		cout << curr->id << endl << endl;
		curr = curr->next;
	}
	*/
	/*
	cv::VideoWriter output("PC.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), clip1.getFPS(), cv::Size(clip1.getWidth(), clip1.getHeight()));  // Create the video writer

	clip1.WriteTo(output); //Writes to the VideoWriter file
	output.release();  // Release the video writer
	cv::destroyAllWindows();  // Close all windows
	*/
	return 0;
}