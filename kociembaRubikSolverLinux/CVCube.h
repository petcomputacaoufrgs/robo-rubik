#ifndef CVCUBE_H
#define CVCUBE_H

#include "CubeView.h"
//#include "SOLVER.H"
#include <stdio.h>
#include <iostream>     // std::cout, std::ostream, std::ios
#include <fstream>      // std::filebuf

void initialRotateCube();
typedef struct CubeSide
{
    CubeColor square[SIDESIZE][SIDESIZE];
}CubeSide;

typedef struct CVCube{
    CubeSide side[N_OF_COLORS];
}CalibrationCube;

void calibrateColors(CubeView* view, FILE* file);
void recognizeCube(CubeView* view, FILE* commands_file);
string getCubeString(CVCube cube);
#endif
