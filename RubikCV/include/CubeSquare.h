#ifndef CUBESQUARE_H
#define CUBESQUARE_H

#include "opencv2/highgui/highgui.hpp"

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

        //members
        cv::Rect_<int> RegionOfInterest;
    protected:
    private:
        //members
        cv::Mat* cubeImage;
};

#endif // CUBESQUARE_H
