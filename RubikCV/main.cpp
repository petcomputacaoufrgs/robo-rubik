#include <iostream>
#include <cstdio>
#include "opencv2/highgui/highgui.hpp"

#include "./include/CubeView.h"
#include "./include/CVCube.h"

using namespace std;
using namespace cv;

int main()
{

    CubeView camera;
    int key=0;
    calibrateColors(&camera, NULL);
    while(key!=27)
    {
        key =cv::waitKey(40);
        camera.updateFrame();
        if(key == 10)
        {
            camera.printColors();
        }
        else
        {
            camera.printRectangles();
        }
        camera.showImage();
    }

    return 0;
}
