
#include<iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    VideoCapture vid(0);
    if(!vid.isOpened())
    {
        cout<<"Web Cam opening is failed";
        return -1;
    }
    string ctrl="Control";
    namedWindow(ctrl,CV_WINDOW_AUTOSIZE);
    int RlowH=161;
    int RHighH=179;
    int RlowS=150;
    int RHighS=255;
    int RlowV=60;
    int RHighV=255;
    int RposX_i=-1;
    int RposY_i=-1;
    int BlowH=110;
    int BHighH=130;
    int BlowS=50;
    int BHighS=255;
    int BlowV=50;
    int BHighV=255;
    int BposX_i=-1;
    int BposY_i=-1;
    Mat img,imgtemp;
    vid.read(imgtemp);
    Mat imgLines1= Mat::zeros( imgtemp.size(), CV_8UC3 );
    Mat imgLines2= Mat::zeros( imgtemp.size(), CV_8UC3 );
    while(1)
    {
    bool success=vid.read(img);
    if(!success)
    {
        cout<<"unable to capture the frames from WebCam ";
        break;
    }
        Mat image_HSV,img_thr1,img_thr2;
        cvtColor(img, image_HSV,COLOR_BGR2HSV);
        inRange(image_HSV, Scalar(RlowV,RlowS,RlowH), Scalar(RHighH,RHighS,RHighV), img_thr1);
        erode(img_thr1, img_thr1, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        dilate(img_thr1, img_thr1, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
         dilate(img_thr1, img_thr1, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
         erode(img_thr1, img_thr1, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        Moments momentR= moments(img_thr1);
               inRange(image_HSV, Scalar(BlowV,BlowS,BlowH), Scalar(BHighH,BHighS,BHighV), img_thr2);
               erode(img_thr2, img_thr2, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
               dilate(img_thr2, img_thr2, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
                dilate(img_thr2, img_thr2, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
                erode(img_thr2, img_thr2, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
               Moments momentB= moments(img_thr2);
        
        if(momentR.m00>10000)
        {
        double RposX_f=momentR.m10/momentR.m00;
        double RposY_f=momentR.m01/momentR.m00;
            if(RposX_i>=0&&RposY_i>=0&&RposX_f>=0&&RposY_f>=0)
            line(imgLines1, Point(RposX_i,RposY_i), Point(RposX_f,RposY_f),Scalar(0,0,200),2);
           RposX_i=RposX_f;
            RposY_i=RposY_f;
        }
        if(momentB.m00>10000)
              {
              double BposX_f=momentB.m10/momentB.m00;
              double BposY_f=momentB.m01/momentB.m00;
                  if(BposX_i>=0&&BposY_i>=0&&BposX_f>=0&&BposY_f>=0)
                  line(imgLines2, Point(BposX_i,BposY_i), Point(BposX_f,BposY_f),Scalar(200,0,0),2);
                 BposX_i=BposX_f;
                  BposY_i=BposY_f;
              }
        string win ="threshhold";
        namedWindow(win);
        img_thr1=img_thr1+img_thr2;
        imshow(win,img_thr1);
        img=img+ imgLines1+imgLines2;
        string original ="original";
        namedWindow(original);
        imshow(original,img);
        if(waitKey(10)==27)
        {
            cout<<"user exited window";
            break;
        }
    }
    return 0;
}
