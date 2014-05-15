#include "../include/CubeView.h"

#include <cstdio>


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
}

void CubeView::initColors()
{
    CubeSquare::initColors();
}

void CubeView::printRectangles()
{

    for(int row = 0; row < SIDESIZE; row++)
        for(int col =0; col < SIDESIZE; col++)
        {
            cubeSide[row][col].showRectangle();
        }
}

void CubeView::printColors()
{
    for(int row = 0; row < SIDESIZE; row++)
    {
        for(int col =0; col < SIDESIZE; col++)
        {
            cv::Vec3b bgr = cubeSide[row][col].getBgrColor();
            cv::Vec3f lab = CubeSquare::bgrToLab(bgr);
            printf("bgrColor: %d  , %d  ,  %d\n", bgr[0], bgr[1], bgr[2]);
            printf("labColor: %f  , %f  ,  %f\n", lab[0], lab[1], lab[2]);
            printf("colorCode: %c    ", cubeSide[row][col].getColorCode());
            printf("\n");
        }
        printf("----------");
    }
    printf("==========");
}
