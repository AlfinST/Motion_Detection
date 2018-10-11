#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace cv;
using namespace std;

Mat src;
int thresh = 100;
int max_thresh = 255;

int main( int argc, char** argv )
{
  src = imread(argv[1], 1);
  string fn(argv[1]);

  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  vector<int> compression_params;
  compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
  compression_params.push_back(100);

  string outputDir="B/Cany/";
  string inputDir="B/Fil/";
  int frameNum=0;

    //read input data. ESC or 'q' for quitting
    int keyboard = 0;
    while( keyboard != 'q' && keyboard != 27 ){
        //update the background model
              int size=-1;
          frameNum=frameNum;
       // pMOG2->apply(frame, fgMaskMOG2);
      
      ////////////////////////////CANNNNNYYY!!!!//////////////////////
        
      Canny( src, canny_output, thresh, thresh*2, 3 );
      findContours( canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE ,Point(0, 0) );
      Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
      Mat back1=Mat::zeros( canny_output.size(), CV_8UC3 );



      Mat back=imread("C/"+to_string(static_cast<long long>(frameNum))+".jpg");
        
        
      for( int i = 0; i< contours.size(); i++ )
      {
       Scalar color = Scalar( 0,0,224 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
       //drawContours(back,contours, i, color, 2, 8, hierarchy, 0, Point() );

      }

      ///////////////////////////////STORE_IT!!!////////////////////
      
        string filePath = outputDir + to_string(static_cast<long long>(frameNum++))+ ".jpg";
        imwrite(filePath,drawing,compression_params);
        string filePath2 = inputDir + to_string(static_cast<long long>(frameNum-1))+ ".jpg";
        // imwrite(filePath2,back,compression_params);
        string filePath3 = "B/croppeed/" + to_string(static_cast<long long>(frameNum-1))+ ".jpg";
      
        /////////////////////////////////////////BOX_IT///////////////////////////////////

    //////////////////////////////////////////////////FILLED_BOX----------//////////////////////////////
    vector<vector<Point> > contours_poly( contours.size() );
     vector<Rect> boundRect( contours.size() ),boundRect2( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { 
       approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       //minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
     }

  for( int i = 0,area=0; i< contours.size(); i++,area=0 )
     {
       Scalar color = Scalar( 0, 255, 0 );
       //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       area=boundRect[i].width * boundRect[i].height;
       if(area >   ) //enter any number by default type 3000          
       /////////////MINIMUM_SIZE_OF_OBJECT_SET_HERE////////////////
       {
        rectangle( back1, boundRect[i].tl(), boundRect[i].br(), color, FILLED, 8, 0 );
       }
     }

        imwrite(filePath2,back  ,compression_params);
        imwrite(filePath3,back1 ,compression_params);
        
        ///////////////////////Box_The_Box/////////////////////
        
        Mat canny_output2;
        vector<vector<Point> > contours2;
        vector<Vec4i> hierarchy2;

        Canny( back1, canny_output2, thresh, thresh*2, 3 );
        findContours( canny_output2, contours2, hierarchy2, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE ,Point(0, 0) );
        Mat drawing2 = Mat::zeros( canny_output2.size(), CV_8UC3 );


         vector<vector<Point> > contours_poly2( contours.size() );

      for( int i = 0; i < contours2.size(); i++ )
      { 
       approxPolyDP( Mat(contours2[i]), contours_poly2[i], 3, true );
       boundRect2[i] = boundingRect( Mat(contours_poly2[i]) );
      }

      for( int i = 0; i< contours.size(); i++)
      {
       Scalar color = Scalar( 255, 0 , 0 );       
       rectangle( back, boundRect2[i].tl(), boundRect2[i].br(), color, 2, 8, 0 );
      }


      imwrite(filePath2,back ,compression_params);
      
      ////////////////////////Next_Image/////////////////////
        
      size_t index = fn.find_last_of("/");
      if(index == string::npos) {
          index = fn.find_last_of("\\");
      }
      size_t index2 = fn.find_last_of(".");
      string prefix = fn.substr(0,index+1);
      string suffix = fn.substr(index2);
      string frameNumberString = fn.substr(index+1, index2-index-1);
      istringstream iss(frameNumberString);
      int frameNumber = 0;
      iss >> frameNumber;
      ostringstream oss;
      oss << (frameNumber + 1);
      string nextFrameNumberString = oss.str();
      string nextFrameFilename = prefix + nextFrameNumberString + suffix;
        
      //read the next frame
        
      src = imread(nextFrameFilename);
      if(src.empty()){
          //error in opening the next image in the sequence
          cerr << "Unable to open image frame: " << nextFrameFilename << endl;
          exit(EXIT_FAILURE);
      ///////////////////////////////////////////////////////////////////////////////
      }
      
      //update the path of the current frame
      fn.assign(nextFrameFilename);
    }

  return(0);
}

