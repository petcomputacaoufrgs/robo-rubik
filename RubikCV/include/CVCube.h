#ifndef CVCUBE_H
#define CVCUBE_H

#include "../include/CubeView.h"
#include "../../kociembaRubikSolverLinux/SOLVER.H"

typedef struct CubeSide
{
    cv::Vec3f square[SIDESIZE][SIDESIZE];
}CubeSide;

typedef struct CVCube{
    CubeSide side[N_OF_COLORS];
}CalibrationCube;

void calibrateColors(CubeView* view, FILE* file);

#endif
