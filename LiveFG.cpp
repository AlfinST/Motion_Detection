#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp> 

#include "string"
#include "exception"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void extract_frames()
{	
	try{

		//open the video file
  		VideoCapture cap(/* Enter the source  online/camera here */);  // EXAMPLE : "http://103.20.189.107:80/mjpg/video.mjpg?COUNTER"
  		if(!cap.isOpened())  // check if we succeeded
  			CV_Error( -2 ,"Can not open Video file");
	    int frameNumber=0,fc=100;
  		vector<int> compression_params;
  		compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
		compression_params.push_back(100);
			
  		string outputDir="C/";
  		for(int frameNum = 0; frameNum < fc;frameNum++)
  		    {
  			   Mat frame;
  			   cap >> frame; 
		       string filePath = outputDir + to_string(static_cast<long long>(frameNum))+ ".jpg";
	  		   imwrite(filePath,frame,compression_params);
  		    }
  		}catch( cv::Exception& e )
  		{
    		cerr << e.msg << endl;
    		exit(1);
  		}
	
}


int main( int argc, char** argv )
{
	//to extract
	extract_frames();
	cout<<"Frames Stored\n\n";
	return 0;
}
