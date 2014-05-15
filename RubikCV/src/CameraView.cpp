#include "../include/CameraView.h"

#include <iostream>

using namespace std;
/*
CameraView::CameraView()  ///MOCK CONSTRUCTOR
{
    this->currentFrame = new cv::Mat();
    *(this->currentFrame) = cv::imread("/home/crmdias/Desktop/PET/roborubik/RubikCV/image.jpg",CV_LOAD_IMAGE_COLOR);
    namedWindow("CameraView",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
}
*/

CameraView::CameraView()
{
    ///ctor

    this->currentFrame = new cv::Mat();

    this->camera = cv::VideoCapture(CameraView::StandardCamera);
    this->isOpened = this->camera.isOpened();

    if(!this->isOpened)
        cout<<"erro ao abrir câmera"<<endl;
    else
        this->updateFrame();

     cout<<"depth : " << this->currentFrame->depth() << "channels : " << this->currentFrame->channels() <<endl;
     namedWindow("CameraView",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
}


CameraView::CameraView(int cameraID)
{
    ///ctor

    this->camera = cv::VideoCapture(cameraID);

    this->isOpened = this->camera.isOpened();

    if(!this->isOpened)
        cout<<"erro ao abrir câmera"<<endl;
    else
        this->updateFrame();

    namedWindow("CameraView",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
}

CameraView::~CameraView()
{
    this->camera.release();
    //dtor
}
/*
void CameraView::updateFrame()  ///MOCK UPDATE
{
    *(this->currentFrame) = cv::imread("/home/crmdias/Desktop/PET/roborubik/RubikCV/image.jpg",CV_LOAD_IMAGE_COLOR);
}
*/


void CameraView::updateFrame()
{
    if(isOpened)
    {
        bool captureSuccess = this->camera.read(*(this->currentFrame));

        if(!captureSuccess)
            cout<<"erro ao tirar foto"<<endl;
    }
    imshow("CameraView", *(this->currentFrame));
}


void CameraView::showImage()
{
    imshow("CameraView", *(this->currentFrame));
}
