#include "../include/CubeSquare.h"
#include <cstdio>
#include <math.h>

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
    int nchannels = 3; //our image has 3 channels
    double channelSum[nchannels]; // each number will contain 1/channelValue, for each pixel in the image.

    for(int i = 0; i<nchannels; i++)
    {
        channelSum[i] = 0.0;
    }

    for (int row = this->RegionOfInterest.y; row < this->RegionOfInterest.y + this->RegionOfInterest.height; row++)
    {
        for(int col = this->RegionOfInterest.x; col < this->RegionOfInterest.x + this->RegionOfInterest.width; col++)
        {
            cv::Vec3b pixelValue = this->cubeImage->at<cv::Vec3b>(row,col);      //gets the color value of this pixel in the image
            for(int channel = 0; channel < nchannels; channel++)
            {
                    if(pixelValue[channel]!=0)
                        channelSum[channel] += (double) 1.0/             //here we update the sum of the color
                                                    (pixelValue[channel]); //we have to change the range of the color values for each channel by 1, to evade a division by zero.
            }
        }
    }

    int numberOfVisitedPixels = this->RegionOfInterest.height * this->RegionOfInterest.width;
    cv::Vec3b averageColor;

    for(int channel=0; channel<nchannels; channel++)   ///here, channel is less or equal then 3 because we want a color with exactly 3 channels
    {
        averageColor[channel] = round(numberOfVisitedPixels/channelSum[channel]);  //here, we calculate the harmonic average of each channel, deducting one from the total to reajust the color range
    }

    return averageColor;
}

static bool printAsLab(cv::Vec3b rgbColor1)
{
    cv::Mat color1 = cv::Mat();
}

