#include <iostream>
#include "opencv2/highgui/highgui.hpp"

#include "include/CubeView.h"

using namespace std;
using namespace cv;

int main()
{
    cout << "Hello world!" << endl;
    CubeView camera;
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    int key;
    while(1)
    {
        camera.updateFrame();
        imshow("MyVideo", *(camera.currentFrame)); //show the frame in "MyVideo" window
        key =cv::waitKey(40);
        if(key == 27)
            camera.printColors();
    }

    return 0;
}
