#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;
VideoCapture vid("/Users/Divyansh Rastogi/Desktop/data structures in c /chapter 2.mp4");
Mat img;
void playframe(int max,void*)
{
    vid.set(CV_CAP_PROP_POS_FRAMES, max);
    while(1)
    {
        vid.read(img);
        namedWindow("video");
        imshow("video",img);
        if(waitKey(10)==27)
        {
            cout<<"video exited";
            break;
        }
        
        
    }
}
int main()
{
    if(!vid.isOpened())
    {
        cout<<"vieo loaded sucessfully";
        return -1;
    }
    double frame_n=vid.get(CV_CAP_PROP_FRAME_COUNT);
    int max=0;
    string win="video";
    namedWindow(win,WINDOW_NORMAL);
    createTrackbar("TRACKBAR", win, &max, frame_n,playframe);
    setTrackbarPos("TRACKBAR",win,max);
    playframe(max,0);
    return 0;
}
