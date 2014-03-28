#include "../include/CubeSquare.h"

CubeSquare::CubeSquare(cv::Point2i topLeft, cv::Size_<int> squareSize, cv::Mat* cubeImage)
{
    //ctor
     this->RegionOfInterest = cv::Rect_<int>(topLeft,  ///creates a square which is defined by the topLeft point
                                                     squareSize); ///and has a size of squareSize
    this->cubeImage = cubeImage;
}

CubeSquare::CubeSquare()
{
    //dtor
}

CubeSquare::~CubeSquare()
{
    //dtor
}

cv::Vec3b CubeSquare::getColor()
{
    //to get the color, we will calculate the harmonic mean of the color values in this region
    int nchannels = this->cubeImage->channels();   //the number of color channels in the cubeImage.

    double channelSum[nchannels]; // each number will contain 1/channelValue, for each pixel in the image.

    for(int i=0; i<nchannels; i++)
        channelSum[i] = 0;          //initializes each sum as 0

    for (int row = 0; row < this->RegionOfInterest.y + this->RegionOfInterest.height; row++)
    {
        uchar* currentRow = this->cubeImage->ptr(row);     //gets a pointer to the curent row in the image

        for(int col = 0; col < this->RegionOfInterest.x + this->RegionOfInterest.width; col++)
        {
           cv::Vec3b colorValue = currentRow[col];       //gets the color value of this pixel in the image

           for(int channel = 0; channel < nchannels; channel++)
           {
                    channelSum[channel] = 1/                            //here we update the sum of the color
                                            (colorValue[channel]+1);    //but we have to change the range of the color values for each channel by 1, to evade a division by zero.
           }
        }
    }
    int numberOfVisitedPixels = this->RegionOfInterest.height * this->RegionOfInterest.width;
    cv::Vec3b averageColor;

    for(int channel=0; channel<3; channel++)   ///here, channel is less or equal then 3 because we want a color with exactly 3 channels
    {
        averageColor[channel] = (int) (numberOfVisitedPixels/channelSum[channel]) - 1;  //here, we calculate the harmonic average of each channel, deducting one from the total to reajust the color range
    }

    return averageColor;
}
