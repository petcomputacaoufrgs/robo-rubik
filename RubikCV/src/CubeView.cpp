#include "../include/CubeView.h"

#include <iostream>

using namespace std;

CubeView::CubeView(int cameraID) : CameraView(cameraID)
{
    //ctor
    for(int row = 0; row < SIDESIZE; row++)
        for(int col =0; col < SIDESIZE; col++)
        {
            cv::Point2i topLeft = cv::Point_<int>((this->currentFrame->cols*(1+4*col)/12),
                                                  this->currentFrame->rows*(1+4*row)/12);
            cubeSide[row][col] = CubeSquare(topLeft,cv::Size_<int>(this->currentFrame->cols/6,this->currentFrame->rows/6),this->currentFrame);
        }
}

CubeView::CubeView() : CameraView()
{
    //ctor
    for(int row = 0; row < SIDESIZE; row++)
        for(int col =0; col < SIDESIZE; col++)
        {
            cv::Point2i topLeft = cv::Point_<int>((this->currentFrame->cols*(1+4*col)/12),
                                                  this->currentFrame->rows*(1+4*row)/12);
            cubeSide[row][col] = CubeSquare(topLeft,cv::Size_<int>(this->currentFrame->cols/6,this->currentFrame->rows/6),this->currentFrame);
        }
}

CubeView::~CubeView()
{
    //dtor
}

void CubeView::updateFrame()
{
    this->CameraView::updateFrame();

    for(int row = 0; row < SIDESIZE; row++)
        for(int col =0; col < SIDESIZE; col++)
        {
            cv::rectangle(*currentFrame, cubeSide[row][col].RegionOfInterest, cv::Scalar_<int>(0,0,255),1,8,0);
        }
}

void CubeView::printColors()
{
    for(int row = 0; row < SIDESIZE; row++)
    {
        for(int col =0; col < SIDESIZE; col++)
        {
            cv::Vec3b squareColor = cubeSide[row][col].getColor();
            cout << squareColor[0] << ';' << squareColor[1] <<';' << squareColor[2];
            cout<<"    ";
        }
        cout<<endl;
    }
}
