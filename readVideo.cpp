//Author: Christy Jo Manthara
//reg no: 2080644
//christyjo.manthara@studenti.unipd.it   /    metalliccj@gmail.com  / christyj150@gmail.com

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



        //convert each frame to hsv format
        cvtColor(img, imgHsv, COLOR_BGR2HSV); 
        namedWindow("HSV Image", WINDOW_NORMAL);
		imshow("HSV Image", imgHsv);


        //to identify the ground/playing field we are going to detect the green color
        // now we define the color ranges for green

        // Define color ranges
        Scalar lower_green(40, 40, 40);
        Scalar upper_green(70, 255, 255); 


		waitKey(1);
		//cap.release();
	}
}
		
	
	
	
 
