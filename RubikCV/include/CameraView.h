#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class CameraView
{
    public:
        //constants
        static const int StandardCamera = 0;

        //constructors
        CameraView();
        CameraView(int cameraID);

        //destructors
        virtual ~CameraView();

        //methods
        virtual void updateFrame();
        void showImage();
        //members
        cv::Mat* currentFrame;
    protected:
    private:
        VideoCapture camera;
        int isOpened;
};

#endif // CAMERAVIEW_H
