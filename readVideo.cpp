#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

///Importing video 

int main()
{
	
	string path = "Resources/sport1.mp4";
	VideoCapture cap(path);
	Mat img, imgHsv;
	
    //converting the video to image frames and displaying them
	while(true) {
	
	
		cap.read(img); //passing the video to the img variable
		resize(img, img, Size(img.cols/2, img.rows/2)); // resized the video to smaller resolutions
		
		//resizeWindow("image", width, height);  
		namedWindow("Image", WINDOW_NORMAL);
		imshow("Image", img);
		waitKey(1);
		//cap.release();
	}
}
		
	
	
	
 
