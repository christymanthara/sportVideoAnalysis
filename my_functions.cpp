//Author: Christy Jo Manthara
//reg no: 2080644
//christyjo.manthara@studenti.unipd.it   /    metalliccj@gmail.com  / christyj150@gmail.com

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;



void getContours(Mat imgDil, Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    string objectType = "trial";
    

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


    // drawContours(img, contours, -1, Scalar(255,0,255),2);
    cout<<contours.size();
    
    


    for(int i = 0; i< contours.size(); i++)
    {   
        

        int area = contourArea(contours[i]);
        cout<< area<<endl;

        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());

        float peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
        // vector<vector<Point>> conPoly(contours.size());
        drawContours(img, conPoly, i, Scalar(255,0,255),2);
        cout<< conPoly[i].size()<< endl;
        
        
        boundRect[i] = boundingRect(conPoly[i]);
        rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,255),5);
        putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 0.75, Scalar(0,69, 255), 2);
    }

}

void checkGreyScale(Mat img)
{

    if (img.type() == CV_8UC1) {
        cout << "Image is grayscale (CV_8UC1)" << endl;
    } else {
        cout << "Image is not grayscale" << endl;
    }

}