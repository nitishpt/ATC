#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

char window_name[30] = "HSV Segemtation";
 Mat src;
 Mat src1;
 Mat src1_gray;
 Mat hsv;
 Mat hsv1;
 Mat imgthreshold;
 Mat imgthreshold1;

 vector<double> v;
 vector<int> vec;

ofstream fout;    //  /dev/ttyACM2

int flag=0;
int flag1=0;
Point2f centre(-1,-1);


double commode()
{
  vector<vector<Point> > contour;
  vector<Vec4i> hierarchy;
  vector<Point> approx;
  findContours(imgthreshold1, contour, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0,0));
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
    if( fabs(contourArea(contour[maxindex])) <10000)
    {
      flag1 = 0;
    }
    else  if( approx.size() >1)
          {
            float radius;
            
            minEnclosingCircle(contour[maxindex], centre, radius);
            circle(src,centre,radius,Scalar(0,0,255),2);

            flag1 = 1;
          }
  }
  else
  {
    flag1=0;
  }

  if(flag1==1)
  {
    return centre.x;
  }
  else
  {
    return -1;
  } 

}


int main()
{
  int maxH, minH;
  int maxH1,minH1;
  int maxS, minS;
  int maxS1, minS1;
  int maxV, minV;
  int maxV1, minV1;
  int count = 0;

  VideoCapture cam(0);
  // VideoCapture cam1(1); 
  // cam.set(CV_CAP_PROP_FRAME_WIDTH,200);
  // cam.set(CV_CAP_PROP_FRAME_HEIGHT,200);
  char key;

  minH = 97;
  maxH = 123;
  minS = 21;
  maxS = 62;
  minV = 75;
  maxV = 255;

  minH1 = 95;
  maxH1 = 112;
  minS1 = 34;
  maxS1 = 121;
  minV1 = 92;
  maxV1 = 228; 

  Mat imgTmp;
  Mat imgTmp1;
  cam.read(imgTmp);
  // cam1.read(imgTmp1); 

  while(1) 
  {
  
    cam.read(src);
    // cam1.read(src1);
    src1=src;
    src1_gray=src1;
    cvtColor(src,hsv,CV_BGR2HSV);
    cvtColor(src1,hsv1,CV_BGR2HSV);
    cvtColor(src1_gray,src1_gray,COLOR_BGR2GRAY);
    blur( src1_gray, src1_gray, Size(3,3) );


 
    inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), imgthreshold); 
    medianBlur(imgthreshold, imgthreshold, 11);

    inRange(hsv1, Scalar(minH1, minS1, minV1), Scalar(maxH1, maxS1, maxV1), imgthreshold1); 
    medianBlur(imgthreshold1, imgthreshold1, 11);
    
    bitwise_not(imgthreshold, imgthreshold);
    imshow("thresh",imgthreshold);
    imshow("thresh1",imgthreshold1);

    double com = commode();

    v.push_back(com);

    if(v.size()==10)
    {
      double avg=0;

      for(int i=0;i<10;i++)
      {
        avg+=v[i];
      }
      avg/=10.0;
      v.clear();

      if(com!=-1&&com<=(src.cols/2)+0.1*src.cols&&com>=(src.cols/2)-0.1*src.cols)
      {
        char t1 = '5';
        fout.open("/dev/ttyACM2");
        cerr<<t1<<endl;
        fout<<t1;
        fout.close();
      }
    }

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
      if( fabs(contourArea(contour[maxindex])) <1000)
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
    {
      vec.push_back(1);
    }
    else
    {
      vec.push_back(0);
    }

    if(vec.size()==10)
    {
      int tmp=0;
      for(int i=0;i<10;i++)
      {
        if(vec[i]==1)
          tmp++;
      }
      if(tmp>=5)
      {
        char t1='1';
        fout.open("/dev/ttyACM2");
        cerr << t1 <<endl;
        fout<<t1;
        fout.close();
      }
      else
      {
        char t1='0';
        fout.open("/dev/ttyACM2");
        cerr << t1 <<endl;
        fout<<t1;
        fout.close();
      }
      vec.clear();
    }
  
    imshow("Original",src ); //show the original image

    int c = waitKey(10);
    if( (char)c == 27 || (char)c == 'q' ) { break; } // escape
  } 
  
  return 0; 
}

