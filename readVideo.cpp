//Author: Christy Jo Manthara
//reg no: 2080644
//christyjo.manthara@studenti.unipd.it   /    metalliccj@gmail.com  / christyj150@gmail.com

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "my_functions.cpp"

using namespace std;
using namespace cv;

///Importing video 




int main()
{
	
	string path = "Resources/cutvideo.mp4";
	VideoCapture cap(path);
	Mat img, imgsaved, imgHsv, rangeMask,rangeMask3C, final, finalBgr, finalGray, tmask1, cfinal, cimg, invertedMask;
	vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Rect> boundRect( contours.size() );
    //converting the video to image frames and displaying them
	while(true) {
	
	
		cap.read(img); //passing the video to the img variable
		// resize(img, img, Size(img.cols/2, img.rows/2)); // resized the video to smaller resolutions
		
        imgsaved = img;

        
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
//__________________________________________________________________________________________________---------------------------------------------------
        //the section for detecting the field
        // create  a black colored image with the same size and type of the input image
        // Mat bnw = zeros(img.size(),img.type()); 
        
        
        // applying canny edge detector to remove the lines on the field and other straight lines in the frames.
        // Canny(rangeMask, rangeMask, 50, 200, 3);
        // //creating a new image with the output of the canny detector
        // cvtColor(rangeMask, cimg, COLOR_GRAY2BGR);

        // namedWindow("Canny", WINDOW_NORMAL);
		// imshow("Canny", rangeMask);
        

        // vector<Vec4i> linesP; // will hold the results of the detection
        // HoughLinesP(rangeMask, linesP, 1, CV_PI/180, 150, 0, 50 ); 


        // for( size_t i = 0; i < linesP.size(); i++ )
        // {
        //     Vec4i l = linesP[i];
        //     line( cimg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255), 2, LINE_AA);
        // }

        // imshow("Detected Lines (in red) - Probabilistic Line Transform", cimg);


        // Mat invertedMask;
        // bitwise_not(cimg, invertedMask);

        // checkGreyScale(rangeMask);

        //------------------------------------------------------------------------------------------------------------
        // img.copyTo(rangeMask, invertedMask);
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
        Mat kernel = getStructuringElement(MORPH_RECT, Size(11,11));

        threshold(finalGray, tmask1 , 127, 225, THRESH_BINARY_INV | THRESH_OTSU);

        morphologyEx(tmask1, tmask1, MORPH_CLOSE, kernel);
        namedWindow("Kernel Applied", WINDOW_NORMAL);
		imshow("Kernel Applied", tmask1);




        // we are going to find the players with contours after we find contour we check only those where the height is greater than the width  
        // we use the getcontours method written earlier for this purpose
        
        // we use the find contours

        findContours(tmask1, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
         //return the number of contours
        //  cout<<contours.size();
         vector<vector<Point> > contours_poly( contours.size() );

        // Rect r = cv::boundingRect(contours[0]);

        //find the bounding rectangles of each contours in the image
        for(int i = 0; i<contours.size(); i++) // the sizes of the contours range from 0 to n-1
        {   float width = boundingRect(contours[i]).width;
            float height = boundingRect(contours[i]).height;
            // now we check if the width is less than the height
            if(height > 1.1*width)
            {
            rectangle(imgsaved, boundingRect(contours[i]), Scalar(255,0,0),5);
            }
        }

        namedWindow("trial", WINDOW_NORMAL);
		imshow("trial", imgsaved);
        	

		waitKey(1);
		//cap.release();
	}
}
		
	
	
	
 
