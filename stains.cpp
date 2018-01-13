#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

char t1, t2='\0';

char window_name[30] = "HSV Segemtation";
 Mat src;
 Mat Frame;
 Mat hsv2;
 Mat imgthreshold;
 char c='\0';
 int count5=0; 
 int arr[10]={0,0,0,0,0,0,0,0,0,0};
ofstream fout;		//  /dev/ttyACM2

int flag=0;
Point2f centre(-1,-1);


int main()
{
  int maxH, minH; 
  int maxS, minS; 
  int maxV, minV; 
  int count = 0;

  VideoCapture cam(1); 
  // cam.set(CV_CAP_PROP_FRAME_WIDTH,200);
  // cam.set(CV_CAP_PROP_FRAME_HEIGHT,200);
  char key;

  minH = 85;
  maxH = 120;
  minS = 60;
  maxS = 176;
  minV = 13;
  maxV = 202;

  Mat imgTmp;
  cam.read(imgTmp); 

  while(1) 
  {
  
    cam.read(src); 
    cvtColor(src,hsv2,CV_BGR2HSV);
 
    inRange(hsv2, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), imgthreshold); 
    medianBlur(imgthreshold, imgthreshold, 11);
  	
	// bitwise_not(imgthreshold, imgthreshold);
	imshow("thresh",imgthreshold);

    vector<vector<Point> > contour;
    vector<Vec4i> hierarchy;
    vector<Point> approx;
    findContours(imgthreshold, contour, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0,0));
    if(contour.size())
    {
      double maxarea = contourArea(contour[0]);
      double area;
      int maxindex=0;
      for(int i=1; i<contour.size(); i++)
      {
        area = contourArea(contour[i]);
        if(area>maxarea)
        {
          maxarea = area;
          maxindex = i;
        }
      }
      approxPolyDP(Mat(contour[maxindex]), approx, arcLength(Mat(contour[maxindex]), true)*0.02, true );
      if( fabs(contourArea(contour[maxindex])) <0.1)
      {
        flag = 0;
      }
      else  if( approx.size() >1)
            {
              float radius;
              
              minEnclosingCircle(contour[maxindex], centre, radius);
              circle(src,centre,radius,Scalar(0,255,0),2);
  
              flag = 1;
            }
    }
    else
    {
      flag=0;
    }

    if(flag)
    	cout<<'1'<<endl;
    else
    	cout<<'0'<<endl;
  
    imshow("Original",src ); //show the original image

    int c = waitKey(10);
    if( (char)c == 27 || (char)c == 'q' ) { break; } // escape
  } 
  
  return 0; 
}

