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
  		VideoCapture cap("http://188.192.97.168:80/mjpg/video.mjpg?COUNTER");//rtmp://185.55.24.19:1935/live/66-20180704052946869406.stream"); // open the video file
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
	cout<<"\nFrames Stored\n";
	return 0;
}
