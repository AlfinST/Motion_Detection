#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{	
	
	//namedWindow( " window2", cv::WINDOW_KEEPRATIO );

	String FilePA,FilePB;
	FilePB="B/Fil/";
	FilePA="C/";

	Mat A,B;
			Mat A1,B2;
	A = imread(FilePA+"0.jpg");
	B = imread(FilePB+"0.jpg");
 namedWindow("Display_window1",cv::WINDOW_KEEPRATIO);
  namedWindow("window2",cv::WINDOW_KEEPRATIO);
 imshow("Display_window1", B);
    imshow("window2", B);
    if(A.empty()){
        //error in opening the first image
        cerr << "Unable to open first image A: " << FilePA << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Got A\n";
        if(B.empty()){
        //error in opening the first image
        cerr << "Unable to open first image B: " << FilePB << endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Got B\n";
	int key=0;
	int op=0;
	int frameNumber = 0;
	while(key==0)
	{	

		cout<<"InLoop";

		string nextFrameFilename1 = "C/" + to_string(static_cast<long long>(frameNumber++))+ ".jpg";
		//cout<<frameNumber<<endl;

		string nextFrameFilename2 = "B/Fil/" + to_string(static_cast<long long>(frameNumber-1))+ ".jpg";

         cout<<nextFrameFilename1<<endl;
         cout<<nextFrameFilename2<<endl;

		A1=imread(nextFrameFilename1);
       
       if(A1.empty()){
        //error in opening the first image
        cerr << "Unable to open  image A: " << nextFrameFilename1 << endl;
        exit(EXIT_FAILURE);
    }

    	imshow("Display_window1", A1);
    //   
       	//cout<<"Showed After\n";
       	         waitKey(1);
    
        B2=imread(nextFrameFilename2);
        if(B2.empty()){
        //error in opening the first image
        cerr << "Unable to open  image B: " << nextFrameFilename2 << endl;
        exit(EXIT_FAILURE);
    }
    imshow("window2", B2);
    for(int i=0;i<50000000;i++);
 	}
}