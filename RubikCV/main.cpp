#include <iostream>
#include <cstdio>
#include "opencv2/highgui/highgui.hpp"

#include "./include/CubeView.h"

using namespace std;
using namespace cv;

int main()
{

     CubeView camera;
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    int key=0;
    while(key!=27)
    {
        camera.updateFrame();
        key = cv::waitKey(40);
        if(key != -1)
            key = key % 256;
        //printf("%d\n", key);
        if(key == 'a')
        {
            camera.printColors();
        }
        else
        {
            camera.printRectangles();
        }

        imshow("MyVideo", *(camera.currentFrame)); //show the frame in "MyVideo" window
    }

    return 0;
}
