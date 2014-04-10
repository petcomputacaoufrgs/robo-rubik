#ifndef CUBESQUARE_H
#define CUBESQUARE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

class CubeSquare
{
    public:
        //constructors
        CubeSquare();
        CubeSquare(cv::Point2i topLeft, cv::Size_<int> squareSize, cv::Mat* cubeImage);

        //destructor
        virtual ~CubeSquare();

        //methods
        cv::Vec3b getColor();
        static double mean(int* inputArray,int arraySize);
        static bool printAsLab(cv::Vec3b rgbColor1);
        //members
        cv::Rect_<int> RegionOfInterest;
    protected:
    private:
        //members
        cv::Mat* cubeImage;
        //methods
        int saturate(cv::Vec3b color); //saturates the given color to the range 0 - 255, for each channel
};

#endif // CUBESQUARE_H
