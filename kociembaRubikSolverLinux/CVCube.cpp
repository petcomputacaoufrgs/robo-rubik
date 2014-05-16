#include "CVCube.h"

using namespace std;

void calibrateColors(CubeView* view, FILE* commands_file)
{
    printf("CALIBRATING...\n");
    CVCube cube;

    //ESTE TRECHO INICIALIZA cube COM TODAS AS CORES DO CUBO
    for(int k=0; k<N_OF_COLORS; k++)
    {
        ///DAQUI
        printf("GETTING SIDE N %d\n", k);
        printf("PRESS ENTER TO GET SIDE\n");
        int key = 0;

        do
        {
            key = cv::waitKey(40);

            view->updateFrame();
            //prints the areas representing each square on the side of the cube
            //view->printRectangles();
            //and shows the image
            view->showImage();
        }while(key!=10);

        ///ATE AQUI É A MUDANÇA DE LADO
        initialRotateCube();


        view->updateFrame();

        //gets the color values of each squeare on the cube
        for(int i=0; i< SIDESIZE; i++)
            for(int j=0; j<SIDESIZE; j++)
                cube.side[k].square[i][j].labValue= view->cubeSide[i][j].getLabColor();

    }

    //ESTE TRECHO PREENCHE colors COM AS CORES EXISTENTES NO CUBO
    cv::Vec3f colors[N_OF_COLORS];

    for(int i=0; i<N_OF_COLORS; i++)
        colors[i] = cube.side[i].square[1][1].labValue;


    //SALVAR AS CORES NO ARQUIVO
    ofstream file(COLOR_INIT_PATH, ios_base::trunc);

    if(file.is_open())
    {
        ostringstream color_stream;
        string color_string;

        for(int i=0; i<N_OF_COLORS; i++)
            color_stream << "{" << colors[i][0] << "," << colors[i][1] << "," << colors[i][2] << "}\n";
        color_string = color_stream.str();
        file.write(color_string.c_str(), color_string.size());
        file.close();
    }
}

void recognizeCube(CubeView* view, FILE* commands_file)
{
    CVCube cube;
    int key=0;
    for(int k=0; k<N_OF_COLORS; k++)
    {
        ///GET NEXT SIDE
        //gets the color values of each squeare on the cube
        printf("GET SIDE FOR CV %d\n", k);

        do
        {
            key = cv::waitKey(40);

            view->updateFrame();
            //prints the areas representing each square on the side of the cube
            view->printRectangles();
            //and shows the image
            view->showImage();
        }while(key!=10);

        initialRotateCube();
        key = 0;

        for(int i=0; i< SIDESIZE; i++)
            for(int j=0; j<SIDESIZE; j++)
                cube.side[k].square[i][j].colorCode = view->cubeSide[i][j].getColorCode();

        view->printColors();
    }

    getCubeString(cube);
    return;
}

string getCubeString(CVCube cube)
{
    return "CUBE STRING\n";
}
