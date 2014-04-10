#ifndef CUBEVIEW_H
#define CUBEVIEW_H

#include "opencv2/highgui/highgui.hpp"

#include "../include/CameraView.h"
#include "../include/CubeSquare.h"

#define SIDESIZE 3     ///size of a cube side, in squares


class CubeView : public CameraView
{
    public:
        //constructors
        CubeView();
        CubeView(int cameraID);

        //destructor
        virtual ~CubeView();

        //methods
        cv::Mat getCubeView();
        void printColors();
        void updateFrame();
        void printRectangles();
    protected:
    private:
      CubeSquare cubeSide[SIDESIZE][SIDESIZE];   ///represents a side of the cube, where the first index is the index of the row and the second of the line of the square in the cube

};

#endif // CUBEVIEW_H
