#ifndef CUBESQUARE_H
#define CUBESQUARE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

#define N_OF_COLORS 6

using namespace cv;

typedef struct CubeColor
{
    char colorCode;
    float labValue[3];
}CubeColor;

class CubeSquare
{
    public:
        //constructors
        CubeSquare();
        CubeSquare(cv::Point2i topLeft, cv::Size_<int> squareSize, cv::Mat* cubeImage);

        //destructor
        virtual ~CubeSquare();

        //methods
        char getColorCode();
        cv::Vec3b getBgrColor();
        void showRectangle();
        static void initColors();
        static void printBaseColors();
        static cv::Vec3f bgrToLab(cv::Vec3b bgrColor1);
        //members
        cv::Rect_<int> RegionOfInterest;
    protected:

        static CubeColor colors[N_OF_COLORS];

    private:
        //methods
        float colorDistance(cv::Vec3f labColor1, cv::Vec3f labColor2);
        static inline cv::Vec3f vec3fFromFloat3(float source[3]);
        //members
        cv::Mat* cubeImage;
};

#endif // CUBESQUARE_H
