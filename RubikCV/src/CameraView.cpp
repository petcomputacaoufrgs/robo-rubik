#include "../include/CameraView.h"

#include <iostream>

using namespace std;

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
}

CameraView::~CameraView()
{
    this->camera.release();
    //dtor
}

void CameraView::updateFrame()
{
    if(isOpened)
    {
        bool captureSuccess = this->camera.read(*(this->currentFrame));

        if(!captureSuccess)
            cout<<"erro ao tirar foto"<<endl;
    }
}
