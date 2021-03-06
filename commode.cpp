//#include "opencv2/imgcodecs/imgcodecs.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void* );

int main( int argc, char** argv )
{

VideoCapture imageName(0);

  while(1)
	{
	//String imageName("bathroom.jpeg");
	  imageName>>src;
	  /*if (argc > 1)
	  {
	    imageName = argv[1];
	  }*/
	  //src = imread(imageName,1);

	  if (src.empty())
	  {
	    cerr << "No image supplied ..." << endl;
	    return -1;
	  }

	  cvtColor( src, src_gray, COLOR_BGR2GRAY );
	  blur( src_gray, src_gray, Size(3,3) );

	  const char* source_window = "Source";
	  namedWindow( source_window, WINDOW_AUTOSIZE);
	  imshow( source_window, src );

	  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
	  thresh_callback( 0, 0 );

	  char ch=waitKey(1000);
	  if(ch==27||ch=='q')
		break;
	}
  return(0);
}

void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  vector<Point> approx;

  Canny( src_gray, canny_output, thresh, thresh*2, 3 );

  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );


    if(contours.size())
    {
      double maxarea = contourArea(contours[0]);
      double area;
      int maxindex=0;
      for(int i=1; i<contours.size(); i++)
      {
        area = contourArea(contours[i]);
        if(area>maxarea)
        {
          maxarea = area;
          maxindex = i;
        }
      }
      /*approxPolyDP(Mat(contours[maxindex]), approx, arcLength(Mat(contours[maxindex]), true)*0.02, true );
      if( fabs(contourArea(contours[maxindex])) <0.1 || !isContourConvex(approx))
      {
        flag = 0;
      }
      else  if( approx.size() >7)
            {
              float radius;
              
              minEnclosingCircle(contours[maxindex], centre, radius);
              circle(src,centre,radius,Scalar(0,255,0),2);
  
              flag = 1;
            }*/

  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  vector<Point> contours_poly;
  Point2f center;
  float radius;

  //for( size_t i = 0; i< contours.size(); i++ )
     {
       approxPolyDP( Mat(contours[maxindex]), contours_poly, 3, true );
       minEnclosingCircle( (Mat)contours_poly, center, radius );
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)maxindex, color, 2, 8, hierarchy, 0, Point() );
       circle( drawing, center, (int)radius, color, 2, 8, 0 );
     }
	
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );

  }

}