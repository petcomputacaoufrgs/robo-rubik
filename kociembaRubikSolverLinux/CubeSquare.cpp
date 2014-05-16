#include "CubeSquare.h"
#include <cstdio>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>

#define MAX_DISTANCE 256

#define LAB_RED     {53.23288178584245,80.10930952982204,67.22006831026425}
#define LAB_GREEN   {87.73703347354422,-86.18463649762525,83.18116474777854}
#define LAB_BLUE    {32.302586667249486,79.19666178930935,-107.86368104495168}
#define LAB_YELLOW  {97.13824698129729,-21.555908334832285,94.48248544644461}
#define LAB_WHITE   {100,0.00526049995830391,-0.010408184525267927}
#define LAB_ORANGE  {74.93219484533535,23.936049070113096,78.95630717524574}

using namespace std;

CubeColor CubeSquare::colors[N_OF_COLORS] = {
                                            {'R',LAB_RED},
                                            {'G',LAB_GREEN},
                                            {'B',LAB_BLUE},
                                            {'Y',LAB_YELLOW},
                                            {'W',LAB_WHITE},
                                            {'O',LAB_ORANGE}};

CubeSquare::CubeSquare(cv::Point2i topLeft, cv::Size_<int> squareSize, cv::Mat* cubeImage)
{
    //ctor
    this->RegionOfInterest = cv::Rect_<int>(topLeft,  ///creates a square which is defined by the topLeft point
                                            squareSize); ///and has a size of squareSize
    this->cubeImage = cubeImage;


}

void CubeSquare::initColors()
{
    ifstream colorInit(COLOR_INIT_PATH);

    if(colorInit.is_open())
    {
        string line;
        string number;
        int color_index =0;
        for(int color_index = 0; color_index <N_OF_COLORS && getline(colorInit, line); color_index++)
        {
            //READ THE FIRST NUMBER
            int index_begin = line.find_first_of("{");
            int index_end = line.find_first_of(",");

            number.assign(line,index_begin+1,index_end-index_begin-1);
            colors[color_index].labValue[0] = atof(number.c_str());

            //ASSINGNS THE REST OF THE STRING TO LINE
            line.assign(line,index_end, line.size()-index_end);

            //READS THE SECOND
            index_begin = 0;
            index_end = line.find_first_of(",");

            number.assign(line,index_begin,index_end-index_begin-1);
            colors[color_index].labValue[1] = atof(number.c_str());

            //ASSINGNS THE REST OF THE STRING TO LINE
            line.assign(line,index_end+1, line.size()-index_end);

            //READS THE THIRD
            index_begin = 0;
            index_end = line.find_first_of("}");

            number.assign(line,index_begin,index_end-index_begin-1);
            colors[color_index].labValue[1] = atof(number.c_str());
        }
    }
    colorInit.close();
}

void CubeSquare::printBaseColors()
{
    for(int i=0; i< N_OF_COLORS; i++)
    {
        for(int j=0; j< 3; j++)
            printf("color: %f    ", colors[i].labValue[j]);
        printf("\n");
    }
}

CubeSquare::CubeSquare()
{
    this->RegionOfInterest = cv::Rect_<int>(cv::Point2i(0,0),cv::Size_<int>(0,0));
    this->cubeImage = new cv::Mat();
    //ctor
}

CubeSquare::~CubeSquare()
{
    //dtors
}

/*returns the colorCode of the color in colors array that is the most similar to the color of this square*/
char CubeSquare::getColorCode()
{
    cv::Vec3b bgrColor = this->getBgrColor();
    cv::Vec3f labColor = CubeSquare::bgrToLab(this->getBgrColor());   //labColor contains this CubeSquare color in lab color space
    int closestColorIndex = 0;        //this will contain the index of the most similar color
    float minDistance = MAX_DISTANCE;               //will contain the minimum distance between this square's color and all the colors in the colors array
    float distance;

    for(int i=0; i < N_OF_COLORS; i++)
    {
        distance = colorDistance(labColor,colors[i].labValue);
        if(distance < minDistance)
        {
            minDistance = distance;
            closestColorIndex = i;
        }
    }

    return colors[closestColorIndex].colorCode;
}

cv::Vec3b CubeSquare::getBgrColor()
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
    cv::Vec3b averageColor2;

    for(int channel=0; channel<nchannels; channel++)   ///here, channel is less or equal then 3 because we want a color with exactly 3 channels
    {
        averageColor[channel] = round(numberOfVisitedPixels/channelSum[channel]);  //here, we calculate the harmonic average of each channel, deducting one from the total to reajust the color range
    }
    return averageColor;
}

cv::Vec3f CubeSquare::bgrToLab(cv::Vec3b bgrColor1)
{
    //aux will contain the bgr color in the 0,0 position
    cv::Mat aux = cv::Mat(1,1,CV_8UC3);

    aux.at<cv::Vec3b>(0,0) = bgrColor1;

    //labColorImage will contain the result of the conversion of aux to L*a*b* color space
    cv::Mat labColorImage = cv::Mat(1,1,CV_8UC3);
    //here we convert to L*a*b*
    cvtColor(aux, labColorImage, CV_BGR2Lab);

    cv::Vec3f labColor = labColorImage.at<cv::Vec3b>(0,0);

    //this snipped changes the range from 0-255 (opencv standard) to L = 0 - 100
    labColor[0] =(float) labColor[0]*100/255;
    // a and b = -128 - 128
    labColor[1] = (float) labColor[1]*256/255 - 128;

    labColor[2] = (float) labColor[2]*256/255 - 128;

    return labColor;
}

float CubeSquare::colorDistance(cv::Vec3f color1, cv::Vec3f color2)
{
    return sqrt((double) (color1[0]-color2[0]) * (color1[0]-color2[0]) +
                            (color1[1]-color2[1]) * (color1[1]-color2[1]) +
                                (color1[2]-color2[2]) * (color1[2]-color2[2]));
}

void CubeSquare::showRectangle()
{
    cv::rectangle(*cubeImage, this->RegionOfInterest, cv::Scalar_<int>(0,255,0),1,8,0);
}

inline cv::Vec3f CubeSquare::vec3fFromFloat3(float source[3])
{
    cv::Vec3f destination;

    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];

    return destination;
}

cv::Vec3f CubeSquare::getLabColor()
{
    return CubeSquare::bgrToLab(this->getBgrColor());
}
