
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
    int lowH=161;
    int HighH=179;
    int lowS=0;
    int HighS=255;
    int lowV=0;
    int HighV=255;
    int posX_i=-1;
    int posY_i=-1;
    createTrackbar("LOW HUE", ctrl, &lowH, 179);
    createTrackbar("HIGH HUE", ctrl, &HighH, 179);
    createTrackbar("LOW SATURATION", ctrl, &lowS, 255);
    createTrackbar("HIGH SATURATION", ctrl, &HighS, 255);
    createTrackbar("LOW VALUE", ctrl, &lowV, 255);
    createTrackbar("HIGH VALUE", ctrl, &HighV, 255);
    Mat img,imgtemp;
    vid.read(imgtemp);
    Mat imgLines = Mat::zeros( imgtemp.size(), CV_8UC3 );
    while(1)
    {
    bool success=vid.read(img);
    if(!success)
    {
        cout<<"unable to capture the frames from WebCam ";
        break;
    }
        Mat image_HSV,img_thr;
        cvtColor(img, image_HSV,COLOR_BGR2HSV);
        inRange(image_HSV, Scalar(lowV,lowS,lowH), Scalar(HighH,HighS,HighV), img_thr);
        erode(img_thr, img_thr, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        dilate(img_thr, img_thr, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
         dilate(img_thr, img_thr, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
         erode(img_thr, img_thr, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        Moments moment= moments(img_thr);
        
        if(moment.m00>10000)
        {
        double posX_f=moment.m10/moment.m00;
        double posY_f=moment.m01/moment.m00;
            if(posX_i>=0&&posY_i>=0&&posX_f>=0&&posY_f>=0)
            line(imgLines, Point(posX_i,posY_i), Point(posX_f,posY_f),Scalar(0,0,200),2);
            posX_i=posX_f;
            posY_i=posY_f;
        }
        string win ="threshhold";
        namedWindow(win);
        imshow(win,img_thr);
        img=img + imgLines;
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
