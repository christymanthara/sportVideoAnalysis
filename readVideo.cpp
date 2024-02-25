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
	Mat img, imgHsv, rangeMask,rangeMask3C, final, finalBgr, finalGray, tmask1;
	
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

        // create mask using the color range defined
        inRange(imgHsv, lower_green, upper_green, rangeMask);



        namedWindow("HSV ImageMask", WINDOW_NORMAL);
		imshow("HSV ImageMask", rangeMask);

        cvtColor(rangeMask, rangeMask3C, COLOR_GRAY2BGR); 

        bitwise_and(img, rangeMask3C, final, rangeMask);
        namedWindow("Green Masked", WINDOW_NORMAL);
		imshow("Green Masked", final);

        // now we convert hsv to bgr to gray 

        cvtColor(final,finalBgr, COLOR_HSV2BGR); 
        namedWindow("Green Masked to BGR", WINDOW_NORMAL);
		imshow("Green Masked to BGR", finalBgr);

        cvtColor(finalBgr,finalGray, COLOR_BGR2GRAY);
        namedWindow("BGR to Gray", WINDOW_NORMAL);
		imshow("BGR to Gray", finalGray);

        // create the kernel for threshholding
        Mat kernel = getStructuringElement(MORPH_RECT, Size(13,13));

        threshold(finalGray, tmask1 , 127, 225, THRESH_BINARY_INV | THRESH_OTSU);

        morphologyEx(tmask1, tmask1, MORPH_CLOSE, kernel);
        namedWindow("Kernel Applied", WINDOW_NORMAL);
		imshow("Kernel Applied", tmask1);

		waitKey(1);
		//cap.release();
	}
}
		
	
	
	
 
